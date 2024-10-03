#include "audiomidi.h"
#include <QtCore/qthread.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <signal.h>
#include <map>

#include "libs/rtaudio/RtAudio.h"
#include "libs/rtmidi/RtMidi.h"

#include <chrono>
#include <thread>

int SAMPLE_RATE = 44100;
int N_CHANNELS = 2;
auto AUDIO_PRIORITY = QThread::HighestPriority;
int VOICES_MAX= 16;


// release time dictionary:  Thread, (isReleased, release time)
std::map<QThread *, std::pair< std::atomic<bool>, std::atomic<double> >> relTimeDic;
std::map<int, QThread *> noteThreadDic;

Audiomidi::VoiceManager voiceManager{};

int freqToMidi(double freq){
    return (int) ( ( 12 * log(freq / 220.0) / log(2.0) ) + 57.01 );
}
double midiToFreq (int n){
    return 440 * std::pow(2, (n - 69.0)/12.0);
}

// Two-channel sawtooth wave generator.
int saw( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
        double streamTime, RtAudioStreamStatus status, void *userData )
{
    unsigned int i, j;
    double *buffer = (double *) outputBuffer;
    double *lastValues = (double *) userData;

    if ( status )
        std::cout << "Stream underflow detected!" << std::endl;

    // Write interleaved audio data.
    for ( i=0; i<nBufferFrames; i++ ) {
        for ( j=0; j<2; j++ ) {
            *buffer++ = lastValues[j];

            //lastValues[j] += 0.005 * (j+1+(j*0.1));
            lastValues[j] += 0.005;
            if ( lastValues[j] >= 1.0 ) lastValues[j] -= 2.0;
        }
    }



    return 0;
}

int sine( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
        double streamTime, RtAudioStreamStatus status, void *userData )
{
    unsigned int i, j;
    double *buffer = (double *) outputBuffer;
    double *lastValues = (double *) userData;
    double freq = lastValues[2];

    double amp = 0.5;
    double a = 0.01;
    double h = 1;
    double r = 0.5;

    ///std::cout << noteThreadDic.find(freqToMidi(freq))->second << std::endl;
    //if (relTimeDic.find(QThread::currentThread()) == relTimeDic.end())
    //    std::cout << "Not found" << std::endl;
    bool isReleased = false;// relTimeDic.find(QThread::currentThread())->second.first.load();

    //std::cout << isReleased << std::endl;


    if ( status )
        std::cout << "Stream underflow detected!" << std::endl;

    // Write interleaved audio data.
    for ( i=0; i<nBufferFrames; i++ ) {
        for ( j=0; j<N_CHANNELS; j++ ) {
            *buffer++ = lastValues[j];

            double t = streamTime + (double)i/SAMPLE_RATE;

            if (t <= a)
                lastValues[j] = amp * std::sin(2 * M_PI * freq * t) * t/a; // t/a is 1 when t == a
            else if (t <= a + h)
                lastValues[j] = amp * std::sin(2 * M_PI * freq * t); // hold
            else if (!isReleased){
                lastValues[j] = amp * std::sin(2 * M_PI * freq * t); // sustain
            }
            else if (isReleased){
                auto relTime = relTimeDic.find(QThread::currentThread())->second.second.load();
                auto mul = ((relTime - t) / r + 1);
                if (mul < 0) mul = 0;
                lastValues[j] = amp * std::sin(2 * M_PI * freq * t) * mul; // release
            }
            else
                lastValues[j] = 0;
        }
    }

    return 0;
}

int audioFun(const double freq, const int voiceID)
{
    RtAudio dac;
    std::vector<unsigned int> deviceIds = dac.getDeviceIds();
    if ( deviceIds.size() < 1 ) {
        std::cout << "\nNo audio devices found!\n";
        exit( 0 );
    }

    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = N_CHANNELS;
    parameters.firstChannel = 0;
    unsigned int sampleRate = SAMPLE_RATE;
    unsigned int bufferFrames = 256; // 256 sample frames
    double data[4] = {0, 0, freq, (double)voiceID};

    if ( dac.openStream( &parameters, NULL, RTAUDIO_FLOAT64, sampleRate,
                       &bufferFrames, &sine, (void *)&data ) ) {
        std::cout << '\n' << dac.getErrorText() << '\n' << std::endl;
        exit( 0 ); // problem with device settings
    }

    // Stream is open ... now start it.
    if ( dac.startStream() ) {
        std::cout << dac.getErrorText() << std::endl;
        goto cleanup;
    }

    char input;
    std::cout << "\nPlaying \n" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    // Block released ... stop the stream
    if ( dac.isStreamRunning() )
        dac.stopStream();  // or could call dac.abortStream();

cleanup:
    if ( dac.isStreamOpen() ) dac.closeStream();

    return 0;
}


bool done;
static void finish(int ignore){ done = true; }

int midiFun (QThread * audioThread){
    RtMidiIn *midiin = new RtMidiIn();
    std::vector<unsigned char> message;
    int nBytes, i;
    double stamp;

    // Check available ports.
    unsigned int nPorts = midiin->getPortCount();
    if ( nPorts == 0 ) {
        std::cout << "No ports available!\n";
        goto cleanup;
    }
    midiin->openPort( 0 );

    // Don't ignore sysex, timing, or active sensing messages.
    midiin->ignoreTypes( false, false, false );

    // Install an interrupt handler function.
    done = false;
    (void) signal(SIGINT, finish);

    // Periodically check input queue.
    while ( !done ) {
        stamp = midiin->getMessage( &message );
        nBytes = message.size();

        if (nBytes >2){
            if ( (int)message[0] == 144 ){
                // Note On
                auto n = (int)message[1];
                auto freq = midiToFreq(n);

                auto myThread = audioThread->create(audioFun, freq);
                myThread->start(AUDIO_PRIORITY);

                auto currentTimeSec = QTime::currentTime().msec()/1000.0 + QTime::currentTime().second();

                std::cout << "inserting" << std::endl;
                relTimeDic.insert(std::make_pair(myThread, std::make_pair(false, currentTimeSec)));
                voiceManager.addVoice(myThread);

                std::cout << myThread << std::endl;
            }
            else if ( (int)message[0] == 128 ){
                // Note Off
                auto n = (int)message[1];
                QThread* thread = noteThreadDic.find(n)->second;

                if (relTimeDic.find(thread) != relTimeDic.end()){

                    auto currentTimeSec = QTime::currentTime().msec()/1000.0 + QTime::currentTime().second();
                    auto relTime = currentTimeSec - relTimeDic.find(thread)->second.second.load();

                    relTimeDic.find(thread)->second.first.store(true); //was released
                    relTimeDic.find(thread)->second.second.store(relTime); // release time
                }
            }
        }

        for ( i=0; i<nBytes; i++ ){
            std::cout << "Byte " << i << " = " << (int)message[i] << ", ";

        }
        if ( nBytes > 0 )
            std::cout << "stamp = " << stamp << std::endl;

        // Sleep for 10 milliseconds ... platform-dependent.
        //std::this_thread::sleep_for(std::chrono::milliseconds( 10 ));
        QThread::msleep(10);
    }

// Clean up
cleanup:
    delete midiin;

    return 0;
}


struct Audiomidi::VoiceManager{
    VoiceManager(QThread * audioThreadArg){
        nextVoiceID = 0;
        nVoices = 0;
        audioThread = audioThreadArg;
        for (int i=0;i<VOICES_MAX;i++){
            voiceThreadDic.insert(std::make_pair(i, nullptr));
        }
    };
public:
    int nVoices;
    int nextVoiceID;
    QThread * audioThread;
    std::map<int, QThread *> voiceThreadDic;

    int newVoice(double freq){
        if (nextVoiceID == -1)
            return -1;

        int idToReturn = nextVoiceID;
        auto newThread = audioThread.create(audioFun, freq);
        voiceThreadDic.find(nextVoiceID)->second = audioThread;
        updateVars();
        return nextVoiceID;
    }
    int removeVoice(int voiceID){
        if (voiceThreadDic.find(voiceID) == voiceThreadDic.end())
            return -1;

        voiceThreadDic.find(voiceID)->second = nullptr;
        return 0;
    }

    void updateVars(){
        updateNextVoiceID();
        updateNVoices();
    }

    void updateNextVoiceID(){
        for (int i=0;i<VOICES_MAX;i++){
            if (voiceThreadDic.find(i)->second == nullptr){
                nextVoiceID = i;
                return;
            }
        }
        nextVoiceID = -1;
    }
    void updateNVoices(){
        nVoices = 0;
        for (int i=0;i<VOICES_MAX;i++){
            if (voiceThreadDic.find(i)->second != nullptr){
                nVoices++;
            }
        }
    }
};

Audiomidi::Audiomidi(QObject *parent)
    : QObject{parent}
{
    auto myThread = midiThread.create(midiFun, &audioThread);
    myThread->start(QThread::HighPriority);
}

void Audiomidi::handleButtonClick(const double freq){
    auto myThread = voiceManager.newVoice();
    myThread->start(AUDIO_PRIORITY);
}
