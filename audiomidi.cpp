#include "audiomidi.h"
#include <QtCore/qthread.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <signal.h>
#include <map>

#include "libs/rtaudio/RtAudio.h"
#include "libs/rtmidi/RtMidi.h"
#include "libs/QMidi/src/QMidiFile.h"

int SAMPLE_RATE = 48000;
int N_CHANNELS = 2;
auto AUDIO_PRIORITY = QThread::HighestPriority;


std::map<QThread *, std::pair<std::atomic<bool>, std::atomic<double>>> relTimeDic;
std::map<int, QThread *> noteThreadDic;

int freqToMidi(double freq){
    return (int) ( ( 12 * log(freq / 220.0) / log(2.0) ) + 57.01 );
}
double midiToFreq (int n){
    return 440 * std::pow(2, (n - 69.0)/12.0);
}

struct UserData{ // data structure passed to RtCallback
    UserData(){}
    double channelData[2] = {0, 0};
    double freq = 0;
    QThread * thread = nullptr;
    bool isReleased = false;
};

int sine( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
        double streamTime, RtAudioStreamStatus status,  void * userDataArg )
{
    unsigned int i, j;
    double *buffer = (double *) outputBuffer;
    UserData *userData = (UserData *) userDataArg;
    double freq = userData->freq;

    double amp = 0.5;
    double a = 0.005;
    double h = 0;
    double r = 0.3;


    bool isNoteReleased = true;
    double relStartTime = -1;
    if (relTimeDic.find(userData->thread) == relTimeDic.end() ){
        std::cout << "Not finding the thread (this is not supposed to happen)" << std::endl;
    }
    else{
        isNoteReleased = relTimeDic.find(userData->thread)->second.first.load();
        relStartTime = relTimeDic.find(userData->thread)->second.second.load();
    }
    if (relStartTime < a + h)
        relStartTime = a + h;

    if ( status )
        std::cout << "Stream underflow detected!" << std::endl;

    // Write interleaved audio data.
    for ( i=0; i<nBufferFrames; i++ ) {
        for ( j=0; j<N_CHANNELS; j++ ) {
            *buffer++ = userData->channelData[j];

            double t = streamTime + (double)i/SAMPLE_RATE;

            if (t <= a)
                userData->channelData[j] = amp * std::sin(2 * M_PI * freq * t) * t/a; // t/a is 1 when t == a
            else if (t <= a + h || !isNoteReleased)
                userData->channelData[j] = amp * std::sin(2 * M_PI * freq * t); // hold/sustain
            else if (isNoteReleased && t <= relStartTime + r){
                userData->channelData[j] = amp * std::sin(2 * M_PI * freq * t) * ((relStartTime - t) / r + 1); // 1 when t == a + h, 0 when t == a + h + r
            }
            else{
                userData->channelData[j] = 0;  // 0 when t > a + t + r
                userData->isReleased = true;

            }
        }
    }

    return 0;
}

int audioFun(const double freq)
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

    UserData data{};
    data.freq = freq;
    data.thread = QThread::currentThread();

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

    std::cout << "\nPlaying \n" << std::endl;
    while (!data.isReleased)
        QThread::msleep(2000);
    std::cout << "releasing thread" << std::endl;

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

                auto newThread = audioThread->create(audioFun, freq);
                auto currentTimeSec = QTime::currentTime().msec()/1000.0 + QTime::currentTime().second();
                relTimeDic.insert(std::make_pair(newThread, std::make_pair(false, currentTimeSec)));
                noteThreadDic.insert(std::pair(n, newThread));
                newThread->start(AUDIO_PRIORITY);
            }
            else if ( (int)message[0] == 128 ){
                // Note Off
                auto n = (int)message[1];
                QThread* thread = noteThreadDic.find(n)->second;

                auto currentTimeSec = QTime::currentTime().msec()/1000.0 + QTime::currentTime().second();
                auto relStartTime = currentTimeSec - relTimeDic.find(thread)->second.second.load();

                relTimeDic.find(thread)->second.first.store(true);
                relTimeDic.find(thread)->second.second.store(relStartTime);

                noteThreadDic.erase(n);
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


Audiomidi::Audiomidi(QObject *parent)
    : QObject{parent}
{
    auto myThread = midiThread.create(midiFun, &audioThread);
    myThread->start(QThread::HighPriority);
}
