/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"




class PresetGUIComponent  : public Component, Button::Listener
{
public:
    //==============================================================================
    PresetGUIComponent();
    ~PresetGUIComponent();

    //==============================================================================


    void paint (Graphics& g) override;
    void resized() override;

	void buttonClicked(Button* button) override;

	void setProcessor(DesuMateAudioProcessor* p) { processor = p; }

private:
	DesuMateAudioProcessor* processor;
	Label curPreset;
	Label presetName;
	Label labelVer;
	Image imageLogo;

	TextButton buttonLoadPreset;
	TextButton buttonSavePreset;
	TextButton buttonInit;
    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetGUIComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
