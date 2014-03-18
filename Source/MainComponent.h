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

#ifndef __JUCE_HEADER_9002020A4DD09B20__
#define __JUCE_HEADER_9002020A4DD09B20__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "ScoreComponent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainComponent  : public Component,
                       public ButtonListener,
                       public ComboBoxListener,
                       public SliderListener
{
public:
    //==============================================================================
    MainComponent ();
    ~MainComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void sliderValueChanged (Slider* sliderThatWasMoved);

    // Binary resources:
    static const char* background_png;
    static const int background_pngSize;
    static const char* musicpizzicato_png;
    static const int musicpizzicato_pngSize;
    static const char* musictremolo_png;
    static const int musictremolo_pngSize;
    static const char* musictrill_png;
    static const int musictrill_pngSize;
    static const char* musictremololighted_png;
    static const int musictremololighted_pngSize;
    static const char* musicpizzicatolighted_png;
    static const int musicpizzicatolighted_pngSize;
    static const char* musictrilllighted_png;
    static const int musictrilllighted_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    bool isTremoloToggled;
    bool isPizzToggled;
    bool isTrillToggled;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> settingComponent;
    ScopedPointer<ScoreComponent> component;
    ScopedPointer<ToggleButton> pizzToggle;
    ScopedPointer<ToggleButton> tremoloToggle;
    ScopedPointer<ToggleButton> trillToggle;
    ScopedPointer<ComboBox> inputSettingComboox;
    ScopedPointer<Slider> thresholdSlider;
    ScopedPointer<TextEditor> udpEditor;
    ScopedPointer<TextButton> ipButton;
    ScopedPointer<TextButton> portButton;
    ScopedPointer<TextButton> messageButton;
    ScopedPointer<Label> label;
    ScopedPointer<ToggleButton> liveModeToggle;
    ScopedPointer<ToggleButton> fileModeToggle;
    Image cachedImage_background_png;
    Image cachedImage_musicpizzicato_png;
    Image cachedImage_musictremolo_png;
    Image cachedImage_musictrill_png;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_9002020A4DD09B20__
