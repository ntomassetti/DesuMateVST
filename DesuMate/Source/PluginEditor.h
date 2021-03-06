/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "PresetGUIComponent.h"
//==============================================================================
/**
*/
class DesuMateAudioProcessorEditor  : public AudioProcessorEditor, private Timer
{
public:
    DesuMateAudioProcessorEditor (DesuMateAudioProcessor&);
    ~DesuMateAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void changeSliderValue(Slider* slider);
	void startDragChange(Slider* slider);
	void endDragChange(Slider* slider);
	
	enum
	{
		paramControlHeight = 40,
		paramLabelWidth = 80,
		paramSliderWidth = 770
	};

private:

	PresetGUIComponent presetComp;

	Label noParameterLabel{ "noparam", "No parameters available" };
	OwnedArray<Slider> paramSliders;
	OwnedArray<Label> paramLabels;
	OwnedArray<Label> paramFilterTypeLabels;

	AudioParameterFloat* getParameterForSlider(Slider* slider);

	bool HABuild = true;

	void timerCallback() override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DesuMateAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DesuMateAudioProcessorEditor)
};
