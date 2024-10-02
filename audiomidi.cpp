#include "audiomidi.h"
#include <QtCore/qthread.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <signal.h>

#include "libs/rtaudio/RtAudio.h"
#include "libs/rtmidi/RtMidi.h"

#include <chrono>
#include <thread>


int SAMPLE_RATE = 44100;
int N_CHANNELS = 2;


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
            else if (t <= a + h + r)
                lastValues[j] = amp * std::sin(2 * M_PI * freq * t) * ((a + h - t) / r + 1); // 1 when t == a + h, 0 when t == a + h + r
            else
                lastValues[j] = 0;  // 0 when t > a + t + r
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
    double data[3] = {0, 0, freq};

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

int midiFun (QThread * thread){
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
    std::cout << "Reading MIDI from port ... quit with Ctrl-C.\n";
    while ( !done ) {
        stamp = midiin->getMessage( &message );
        nBytes = message.size();
        for ( i=0; i<nBytes; i++ ){
            std::cout << "Byte " << i << " = " << (int)message[i] << ", ";

            if (i == 0 && (int)message[i] == 144){
                // Note On
                auto freq = 440 * std::pow(2, ( - 69)/12)
                thread->create(audioFun, 550)->start(QThread::HighPriority);
            }
            else if (i == 1 && (int)message[i] == 128){
                // Note Off
            }
        }
        if ( nBytes > 0 )
            std::cout << "stamp = " << stamp << std::endl;

        // Sleep for 10 milliseconds ... platform-dependent.
        std::this_thread::sleep_for(std::chrono::milliseconds( 10 ));
    }

// Clean up
cleanup:
    delete midiin;

    return 0;
}


Audiomidi::Audiomidi(QObject *parent)
    : QObject{parent}
{
    auto myThread = thread.create(midiFun, &thread);
    myThread->start(QThread::HighPriority);
}

void Audiomidi::handleButtonClick(const double freq){
    auto myThread = thread.create(audioFun, freq);
    myThread->start(QThread::HighPriority);
}
