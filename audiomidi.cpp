#include "audiomidi.h"
#include <QtCore/qthread.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "libs/rtaudio/RtAudio.h"

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
    double freq = 440;

    if ( status )
        std::cout << "Stream underflow detected!" << std::endl;

    // Write interleaved audio data.
    for ( i=0; i<nBufferFrames; i++ ) {
        for ( j=0; j<N_CHANNELS; j++ ) {
            *buffer++ = lastValues[j];

            lastValues[j] = 0.5 * std::sin(2 * M_PI * freq * (streamTime + (double)i/SAMPLE_RATE));
        }
    }
    std::cout << lastValues[0] << std::endl;

    return 0;
}

int fun()
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
    double data[2] = {0, 0};

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
    std::cout << "\nPlaying ... press <enter> to quit.\n" << std::endl;
    while(true){}

    // Block released ... stop the stream
    if ( dac.isStreamRunning() )
        dac.stopStream();  // or could call dac.abortStream();

cleanup:
    if ( dac.isStreamOpen() ) dac.closeStream();

    return 0;
}

Audiomidi::Audiomidi(QObject *parent)
    : QObject{parent}
{
}

void Audiomidi::handleButtonClick(){
    QThread thread{};
    auto myThread = thread.create(fun);

    myThread->start(QThread::TimeCriticalPriority);
}
