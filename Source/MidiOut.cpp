//
//  MidiOut.cpp
//  Thinkplay Back-End
//

#include "MidiOut.h"


MidiOut::MidiOut()
{
    //=== Setup the MIDI Output Port ===//
    midiNameArray.set(0, "C");
    midiNameArray.set(1, "C#/Db");
    midiNameArray.set(2, "D");
    midiNameArray.set(3, "D#/Eb");
    midiNameArray.set(4, "E");
    midiNameArray.set(5, "F");
    midiNameArray.set(6, "F#/Gb");
    midiNameArray.set(7, "G");
    midiNameArray.set(8, "G#/Ab");
    midiNameArray.set(9, "A");
    midiNameArray.set(10, "A#/Bb");
    midiNameArray.set(11, "B");
    temp = "Null";
#if JUCE_MAC || JUCE_LINUX
    
    //create a new device for the output
    midiOutput = MidiOutput::createNewDevice("from violinTrigger");
    
    if(midiOutput)
    {
        //start thread
        midiOutput->startBackgroundThread();
    }
    else
    {
        //whoops, we couldn't create the device
        DBG("Failed to create virtual MIDI Device");
    }
    
#endif // if JUCE_MAC || JUCE_LINUX
    
#if JUCE_WINDOWS
    
#endif
}

MidiOut::~MidiOut()
{
 	// IMPORTANT - The following statement causes errors in windows, comment out if on an PC
#if JUCE_MAC || JUCE_LINUX
    //Stop midi thread
    midiOutput->stopBackgroundThread();
#endif
    
    //delete midiOutput
	midiOutput = nullptr;
}

String MidiOut::getPitchName(int midiNote) const
{
    if(midiNote!=0){
        temp.equalsIgnoreCase(midiNameArray[midiNote%12]);
        return midiNameArray[midiNote%12];
    }
    else
        return temp;
}

void MidiOut::sendMidiOut(int channel, int noteNumber, int velocity)
{
    if (velocity != 0)
    {
        //send note-on midi message
        midiOutput->sendMessageNow(MidiMessage::noteOn(channel, noteNumber, (uint8)velocity));
    }
    else
    {
        //send note-of midi message
        midiOutput->sendMessageNow(MidiMessage::noteOff(channel, noteNumber));
    }
}

