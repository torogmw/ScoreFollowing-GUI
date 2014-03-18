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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "ScoreComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ScoreComponent::ScoreComponent ()
{
    addAndMakeVisible (resetButton = new TextButton ("reset"));
    resetButton->setButtonText (TRANS("Reset"));
    resetButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    resetButton->addListener (this);
    resetButton->setColour (TextButton::buttonColourId, Colour (0xfff8a970));

    addAndMakeVisible (loadButton = new TextButton ("load"));
    loadButton->setButtonText (TRANS("Load"));
    loadButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    loadButton->addListener (this);
    loadButton->setColour (TextButton::buttonColourId, Colour (0xfff8a970));

    addAndMakeVisible (modelButton = new TextButton ("model"));
    modelButton->setButtonText (TRANS("Model"));
    modelButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight | Button::ConnectedOnTop | Button::ConnectedOnBottom);
    modelButton->addListener (this);
    modelButton->setColour (TextButton::buttonColourId, Colour (0xfff8a970));

    addAndMakeVisible (scoreLabel = new Label ("new label",
                                               TRANS("Score ")));
    scoreLabel->setFont (Font ("Helvetica", 20.00f, Font::plain));
    scoreLabel->setJustificationType (Justification::centred);
    scoreLabel->setEditable (false, false, false);
    scoreLabel->setColour (TextEditor::textColourId, Colours::black);
    scoreLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (stateLabel = new Label ("state label",
                                               TRANS("hidden \n"
                                               "state")));
    stateLabel->setFont (Font (15.00f, Font::plain));
    stateLabel->setJustificationType (Justification::centred);
    stateLabel->setEditable (false, false, false);
    stateLabel->setColour (TextEditor::textColourId, Colours::black);
    stateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (modeToggleButton = new ToggleButton ("nide toggle button"));
    modeToggleButton->setButtonText (TRANS("follow score"));
    modeToggleButton->addListener (this);


    //[UserPreSize]
    modeToggleButton->setColour(TextButton::buttonColourId, Colour (0x91ff7f50));
    //[/UserPreSize]

    setSize (800, 420);


    //[Constructor] You can add your own custom stuff here..
    isFollowingScore = false;
    //[/Constructor]
}

ScoreComponent::~ScoreComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    resetButton = nullptr;
    loadButton = nullptr;
    modelButton = nullptr;
    scoreLabel = nullptr;
    stateLabel = nullptr;
    modeToggleButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ScoreComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0x8ffefefe));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ScoreComponent::resized()
{
    resetButton->setBounds (696, 16, 86, 24);
    loadButton->setBounds (696, 40, 86, 24);
    modelButton->setBounds (696, 64, 86, 24);
    scoreLabel->setBounds (328, 24, 176, 24);
    stateLabel->setBounds (8, 16, 72, 32);
    modeToggleButton->setBounds (0, 368, 72, 48);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ScoreComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == resetButton)
    {
        //[UserButtonCode_resetButton] -- add your button handler code here..
        //[/UserButtonCode_resetButton]
    }
    else if (buttonThatWasClicked == loadButton)
    {
        //[UserButtonCode_loadButton] -- add your button handler code here..
        FileChooser chooser (("Choose score file to open"),File::nonexistent,"*",true);
        chooser.browseForFileToOpen();
        if(chooser.getResult().exists())
        {
            setFile(chooser.getResult());
        }
        //[/UserButtonCode_loadButton]
    }
    else if (buttonThatWasClicked == modelButton)
    {
        //[UserButtonCode_modelButton] -- add your button handler code here..
        //[/UserButtonCode_modelButton]
    }
    else if (buttonThatWasClicked == modeToggleButton)
    {
        //[UserButtonCode_modeToggleButton] -- add your button handler code here..
        isFollowingScore = modeToggleButton->getToggleState();
        //[/UserButtonCode_modeToggleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ScoreComponent::setFile(const juce::File &file)
{
    notes.clear();
    times.clear();
    scoreLabel->setText(file.getFileNameWithoutExtension(), dontSendNotification);
    StringArray rawText;
    file.readLines(rawText);
    for(int i = 0; i<rawText.size(); i++)
    {
        StringArray tokens;
        tokens.addTokens (rawText[i], " ", "\"");
        notes.insert(i, tokens[0].getIntValue());
        times.insert(i, tokens[1].getIntValue());
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ScoreComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="800" initialHeight="420">
  <BACKGROUND backgroundColour="8ffefefe"/>
  <TEXTBUTTON name="reset" id="6108542cce1ccb2a" memberName="resetButton" virtualName=""
              explicitFocusOrder="0" pos="696 16 86 24" bgColOff="fff8a970"
              buttonText="Reset" connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="load" id="185a657117448487" memberName="loadButton" virtualName=""
              explicitFocusOrder="0" pos="696 40 86 24" bgColOff="fff8a970"
              buttonText="Load" connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="model" id="a20e7574d53b5cb1" memberName="modelButton" virtualName=""
              explicitFocusOrder="0" pos="696 64 86 24" bgColOff="fff8a970"
              buttonText="Model" connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="9ade6abaa6eb85fe" memberName="scoreLabel"
         virtualName="" explicitFocusOrder="0" pos="328 24 176 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Score " editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Helvetica" fontsize="20" bold="0"
         italic="0" justification="36"/>
  <LABEL name="state label" id="37d42797bdc7d218" memberName="stateLabel"
         virtualName="" explicitFocusOrder="0" pos="8 16 72 32" edTextCol="ff000000"
         edBkgCol="0" labelText="hidden &#10;state" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <TOGGLEBUTTON name="nide toggle button" id="48f1b565107c51d0" memberName="modeToggleButton"
                virtualName="" explicitFocusOrder="0" pos="0 368 72 48" buttonText="follow score"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
