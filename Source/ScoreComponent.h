/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_27BA2BD040C84E9E__
#define __JUCE_HEADER_27BA2BD040C84E9E__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#define LOWNOTE 51
#define HIGHNOTE 90
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ScoreComponent  : public Component,
                        public Timer,
                        public ButtonListener
{
public:
    //==============================================================================
    ScoreComponent ();
    ~ScoreComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setFile(const File& file);                 // set and parse the score
    void setRange(int totalTime);
    void timerCallback() override;
    // below should be private methods

    void updateCursorPosition(int currentTime);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    DrawableRectangle currentPositionMarker;        // cursor to follow the score
    Array<int> notes;                               // score notes buffer
    Array<int> times;                              // score notes corresponding length
    OwnedArray<DrawableRectangle> scores;
    int visibleRange;
    bool isFollowingScore;
    File lastFileDropped;
    float currentTime;
    

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> resetButton;
    ScopedPointer<TextButton> loadButton;
    ScopedPointer<Label> scoreLabel;
    ScopedPointer<Label> stateLabel;
    ScopedPointer<ToggleButton> modeToggleButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScoreComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_27BA2BD040C84E9E__
