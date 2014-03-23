//
//  AudioInputSource.h
//  ScoreFollowingGUI
//
//  Created by Minwei Gu on 3/18/14.
//
//

#ifndef __ScoreFollowingGUI__AudioInputSource__
#define __ScoreFollowingGUI__AudioInputSource__

#include <iostream>
#include "JuceHeader.h"
#include "ViolinClassification.h"
#include "Follower.h"


#define LIVE_INPUT 0
#define FILE_INPUT 1

#define RECORDSIZE 44544

class AudioInputSource : public AudioIODeviceCallback
{
public:
    AudioInputSource(AudioDeviceManager& deviceManager, int choice);
    ~AudioInputSource();
    void audioDeviceIOCallback(const float** inputChannelData,
							   int totalNumInputChannels,
							   float** outputChannelData,
							   int totalNumOutputChannels,
							   int numSamples);
    void audioDeviceAboutToStart (AudioIODevice* device);
    void audioDeviceStopped();
    void setFile(File audioFile);
    void filePlayingControl();
    bool setToggle();
    int getCurrentPitch() const;
    void violinTracking(float* data);
    
    
    
    
private:
    
    AudioDeviceManager& deviceManager;
    AudioSourcePlayer audioSourcePlayer;
    AudioFormatReaderSource* fileSource;
    AudioTransportSource transportSource;
    AudioFormatManager formatManager;
    TimeSliceThread playingThread;
    
    AudioSampleBuffer sampleBuffer = AudioSampleBuffer(1,RECORDSIZE); //the buffer is for store;
    AudioSampleBuffer calculateBuffer = AudioSampleBuffer(1,RECORDSIZE); //the buffer is throwing to the pitchtail
    AudioSampleBuffer tempBuffer = AudioSampleBuffer(1,RECORDSIZE); // this buffer is for sliding buffer window
    ViolinClassification* vc;

    
    int choice;
    bool inputToggle;
    bool bufferReady;
    int bufferIndex;
    bool ok;
    
};



#endif /* defined(__ScoreFollowingGUI__AudioInputSource__) */
