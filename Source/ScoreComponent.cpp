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

    addAndMakeVisible (scoreLabel = new Label ("new label",
                                               TRANS("Title")));
    scoreLabel->setFont (Font ("Helvetica", 20.00f, Font::plain));
    scoreLabel->setJustificationType (Justification::centred);
    scoreLabel->setEditable (false, false, false);
    scoreLabel->setColour (TextEditor::textColourId, Colours::black);
    scoreLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (stateLabel = new Label ("state label",
                                               TRANS("hidden state")));
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
    gtcmtByebye = new DialogWindow("Farewell GTCMT",
                                   Colours::black,
                                   true,
                                   true);
    //[/UserPreSize]

    setSize (800, 420);


    //[Constructor] You can add your own custom stuff here..
    isFollowingScore = false;
    currentPositionMarker.setFill (Colours::orangered.withAlpha (0.85f));
    addAndMakeVisible (currentPositionMarker);
    gradComponent = new TechGradComponent();
    visibleRange = 0;
    currentIndex = 0;
    currentPitch = 0;
    //[/Constructor]
}

ScoreComponent::~ScoreComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    resetButton = nullptr;
    loadButton = nullptr;
    scoreLabel = nullptr;
    stateLabel = nullptr;
    modeToggleButton = nullptr;
    gradComponent = nullptr;
    gtcmtByebye = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ScoreComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0x8ffefefe));

    g.setColour (Colours::grey);
    g.fillRect (10, 30, 780, 2);

    g.setColour (Colours::grey);
    g.fillRect (10, 390, 780, 2);

    g.setColour (Colours::grey);
    g.fillRect (10, 30, 2, 360);

    g.setColour (Colours::grey);
    g.fillRect (790, 30, 2, 360);

    //[UserPaint] Add your own custom painting code here..
    g.setColour (Colours::black);

    if (notes.size() > 0)
    {
        for (int i = 0; i<scores.size(); i++)
        {
            scores[i]->setFill (Colours::black.withAlpha (0.85f));
            scores[i]->setVisible(true);
        }
    }
    else
    {
        g.setFont (20.0f);
        g.drawFittedText ("No score selected", getLocalBounds(), Justification::centred, 2);
    }
    //[/UserPaint]
}

void ScoreComponent::resized()
{
    resetButton->setBounds (624, 0, 86, 24);
    loadButton->setBounds (712, 0, 86, 24);
    scoreLabel->setBounds (300, 0, 200, 24);
    stateLabel->setBounds (0, 0, 120, 24);
    modeToggleButton->setBounds (0, 392, 104, 24);
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
        notes.clear();
        times.clear();
        scores.clear();
        stopTimer();
        updateCursorPosition(0);
        currentIndex = 0;
        repaint();
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
    scores.clear();
    int totalLength = 0;
    scoreLabel->setText(file.getFileNameWithoutExtension(), dontSendNotification);
    StringArray rawText;
    file.readLines(rawText);
    for(int i = 0; i<rawText.size(); i++)
    {
        StringArray tokens;
        tokens.addTokens (rawText[i], " ", "\"");
        notes.insert(i, tokens[0].getIntValue());
        times.insert(i, tokens[1].getIntValue());
        std::cout<<tokens[1].getIntValue()<<" ";
        totalLength+=tokens[1].getIntValue();
    }
    setRange(totalLength);
    startTimer(25);
}
void ScoreComponent::setRange(int totalTime)
{
    visibleRange = totalTime;                                   // total time meters?
    // scorllbar maybe added here
    // calculate position, height and width of the score rectangle based on the total time
    float noteYInterval = 360/(HIGHNOTE-LOWNOTE+1);
    float noteXInterval = 780.0/visibleRange;
    int noteIndex = 0;
    for (int i = 0; i<notes.size(); i++)
    {
        DrawableRectangle* temp = new DrawableRectangle();                             // current inserting note
        addAndMakeVisible(temp);
        temp->setRectangle(Rectangle<float> (10+noteIndex*noteXInterval, 390-(notes[i]-LOWNOTE)*noteYInterval, noteXInterval*times[i], noteYInterval));
        scores.add(temp);
        noteIndex+=times[i];
    }
    updateCursorPosition(0.2);        // start at the very beginning
    repaint();

}


void ScoreComponent::setPitch(int pitchValue)
{
    sharedMemory.enter();
    currentPitch = pitchValue;
    sharedMemory.exit();
}

void ScoreComponent::updateCursorPosition(int timeIndex)
{
    if(notes.size()>0)
    {
        float noteXInterval = 780.0/visibleRange;
        currentPositionMarker.setVisible(true);
        currentPositionMarker.setRectangle (Rectangle<float> (10+noteXInterval*timeIndex,30,2,360));
    }
    else
    {
        currentPositionMarker.setVisible(false);
    }
}
void ScoreComponent::timerCallback()
{
    // start to listen?
    if(isFollowingScore && currentIndex < notes.size())
    {
        sharedMemory.enter();
        //std::cout<<currentPitch<<std::endl;
        int temp = currentPitch;
        sharedMemory.exit();
        if (abs (notes[currentIndex] - temp) == 12 || notes[currentIndex] == temp)
        {
            int timeIndex = 0;
            for (int j = 0; j<=currentIndex; j++) timeIndex+=times[j];
            updateCursorPosition(timeIndex);
            currentIndex++;
        }
    }
    if(isFollowingScore && currentIndex == notes.size() && scoreLabel->getText().equalsIgnoreCase("pomp and circumstance"))
    {
        addAndMakeVisible(gradComponent);
        gtcmtByebye->showDialog("Farewell GTCMT", gradComponent, this, Colours::black, true);
        stopTimer();
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
                 parentClasses="public Component, public Timer" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="800" initialHeight="420">
  <BACKGROUND backgroundColour="8ffefefe">
    <RECT pos="10 30 780 1.5" fill="solid: ff808080" hasStroke="0"/>
    <RECT pos="10 390 780 1.5" fill="solid: ff808080" hasStroke="0"/>
    <RECT pos="10 30 1.5 360" fill="solid: ff808080" hasStroke="0"/>
    <RECT pos="790 30 1.5 360" fill="solid: ff808080" hasStroke="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="reset" id="6108542cce1ccb2a" memberName="resetButton" virtualName=""
              explicitFocusOrder="0" pos="624 0 86 24" bgColOff="fff8a970"
              buttonText="Reset" connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="load" id="185a657117448487" memberName="loadButton" virtualName=""
              explicitFocusOrder="0" pos="712 0 86 24" bgColOff="fff8a970"
              buttonText="Load" connectedEdges="15" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="9ade6abaa6eb85fe" memberName="scoreLabel"
         virtualName="" explicitFocusOrder="0" pos="300 0 200 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Title" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Helvetica" fontsize="20" bold="0"
         italic="0" justification="36"/>
  <LABEL name="state label" id="37d42797bdc7d218" memberName="stateLabel"
         virtualName="" explicitFocusOrder="0" pos="0 0 120 24" edTextCol="ff000000"
         edBkgCol="0" labelText="hidden state" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <TOGGLEBUTTON name="nide toggle button" id="48f1b565107c51d0" memberName="modeToggleButton"
                virtualName="" explicitFocusOrder="0" pos="0 392 104 24" buttonText="follow score"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
