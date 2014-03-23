//
//  AudioInputSource.cpp
//  ScoreFollowingGUI
//
//  Created by Minwei Gu on 3/18/14.
//
//

#include "AudioInputSource.h"

AudioInputSource::AudioInputSource(AudioDeviceManager& deviceManager_, int choice_):deviceManager(deviceManager_), playingThread("audio Input source"),choice(choice_)
{
    if (choice == FILE_INPUT)
    {
        formatManager.registerBasicFormats();
        audioSourcePlayer.setSource(&transportSource);
    }
    deviceManager.addAudioCallback(this);
    playingThread.startThread();
    bufferReady = false;
    
    vc = new ViolinClassification();
    bufferIndex = 0;
    ok = true;
    inputToggle=0;
}


AudioInputSource::~AudioInputSource()
{
    deviceManager.removeAudioCallback(this);
    if(choice == FILE_INPUT)
    {
        transportSource.setSource(0);
        deleteAndZero(fileSource);
        audioSourcePlayer.setSource(0);
    }
    delete vc;
}

void AudioInputSource::setFile(File audioFile)
{
    if (choice == FILE_INPUT)
    {
        if(audioFile.exists())
        {
            AudioFormatReader* tempReader = formatManager.createReaderFor(audioFile);
            fileSource = new AudioFormatReaderSource(tempReader,true);
            transportSource.setSource(fileSource,32768,&playingThread,44100);
            //transportSource.start();
            inputToggle=1;
        }
    }
    if (choice == LIVE_INPUT)
    {
        // handling live input here
    }
}

void AudioInputSource::setToggle(int index)
{
    switch (index) {
        case 0:
            vc->toggleState.push_back(0);           // pizzicato
            break;
        case 2:
            vc->toggleState.push_back(2);           // tremolo
            break;
        case 3:
            vc->toggleState.push_back(3);           // trill
            break;
        case 5:
            vc->toggleState.clear();
        default:
            vc->toggleState.clear();
            break;
    }
}

int AudioInputSource::getCurrentPitch() const
{
    if (vc->pitch<45 || vc->pitch>92)
        return 0;
    else
        return vc->pitch;
}
void AudioInputSource::audioDeviceIOCallback(const float **inputChannelData, int totalNumInputChannels, float **outputChannelData, int totalNumOutputChannels, int numSamples)
{
   
    
    if (choice == FILE_INPUT )
    {
        if (bufferReady == true && inputToggle == 1){
            violinTracking(calculateBuffer.getSampleData(0));
            //ok = false;
            bufferReady = false;
        }
       
        if (bufferReady == false && inputToggle == 1)
        {
            //std::cout<<*outputChannelData[0]<<std::endl;
//            if (bufferIndex < 87){
//                sampleBuffer.clear();
//                sampleBuffer.copyFrom(0, 0, outputChannelData[0], numSamples);
//                if (sampleBuffer.getSampleData(0))
//                    calculateBuffer.copyFrom(0, numSamples*bufferIndex, sampleBuffer, 0, 0, numSamples);
//                bufferIndex++;
//            }
//            else
//                bufferReady = true;
            sampleBuffer.clear();
            sampleBuffer.copyFrom(0, 0, outputChannelData[0], numSamples);
            tempBuffer.copyFrom(0, 0, calculateBuffer, 0, numSamples, RECORDSIZE - numSamples);
            calculateBuffer.clear();
            tempBuffer.copyFrom(0, RECORDSIZE - numSamples, sampleBuffer, 0, 0, numSamples);
            calculateBuffer.copyFrom(0, 0, tempBuffer, 0, 0, RECORDSIZE);
            tempBuffer.clear();
            bufferReady = true;
        }
//        else
//        {
//            //vc->pitch = 0;
//        }
        audioSourcePlayer.audioDeviceIOCallback (inputChannelData, totalNumInputChannels, outputChannelData, totalNumOutputChannels, numSamples);   //pass the output to the player

    }
    if (choice == LIVE_INPUT)
    {
        //std::cout<<*inputChannelData[0]<<std::endl;

        for (int i = 0; i < numSamples; ++i)
            for (int j = totalNumOutputChannels; --j >= 0;)
                outputChannelData[j][i] = 0;
        
        if (bufferReady == true){
            violinTracking(calculateBuffer.getSampleData(0));
            bufferReady = false;
        }
        
        if (bufferReady == false)
        {
            sampleBuffer.clear();
            sampleBuffer.copyFrom(0, 0, inputChannelData[0], numSamples);
            tempBuffer.copyFrom(0, 0, calculateBuffer, 0, numSamples, RECORDSIZE - numSamples);
            calculateBuffer.clear();
            tempBuffer.copyFrom(0, RECORDSIZE - numSamples, sampleBuffer, 0, 0, numSamples);
            calculateBuffer.copyFrom(0, 0, tempBuffer, 0, 0, RECORDSIZE);
            tempBuffer.clear();
            bufferReady = true;
        }
        
    }
    
}

void AudioInputSource::filePlayingControl()
{
    if(choice==FILE_INPUT)
    {
        if(transportSource.isPlaying())
            transportSource.stop();
        else
            transportSource.start();
    }
}

void AudioInputSource::violinTracking(float* data)
{
//    float* d = new float[RECORDSIZE];
//    for( int i=0; i<RECORDSIZE; i++)
//    d[i] = data[i];
    
    vc->getReady(data);
    
//    delete d;
}

int AudioInputSource::getCurrentTech() const
{
    if (vc->classLabel == "pizzicato")
        return 0;
    else if (vc->classLabel == "tremolo")
        return 2;
    else if (vc->classLabel == "trill")
        return 3;
    else
        return 5;
}

void AudioInputSource::setThredhold(float sliderValue)
{
    std::cout<<"set threshold: "<<sliderValue<<std::endl;
    vc->threshold = sliderValue;
}

void AudioInputSource::audioDeviceAboutToStart(AudioIODevice* device)
{
    if (choice == FILE_INPUT)
        audioSourcePlayer.audioDeviceAboutToStart (device);
}

void AudioInputSource::audioDeviceStopped()
{
    if (choice == FILE_INPUT)
        audioSourcePlayer.audioDeviceStopped();
}
