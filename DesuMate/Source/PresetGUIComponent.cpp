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


#include "PresetGUIComponent.h"

//==============================================================================
PresetGUIComponent::PresetGUIComponent ()
{
	curPreset.setText("Current Preset:", NotificationType::dontSendNotification);
	presetName.setText("init" , NotificationType::dontSendNotification);
	addAndMakeVisible(curPreset);
	addAndMakeVisible(presetName);
	buttonLoadPreset.setButtonText("Load Preset");
	buttonSavePreset.setButtonText("Save Preset");
	
	buttonSavePreset.addListener(this);
	buttonLoadPreset.addListener(this);

	addAndMakeVisible(buttonLoadPreset);
	addAndMakeVisible(buttonSavePreset);
}

PresetGUIComponent::~PresetGUIComponent()
{

}

//==============================================================================
void PresetGUIComponent::paint (Graphics& g)
{

    g.fillAll (Colour(55, 55, 55));

	Path path;
	Rectangle<int> presetBorder(8, 5, 303, 33);
	g.setColour(Colour(17, 17, 17));
	path.addRoundedRectangle(presetBorder, 5.0f);
	g.fillPath(path);
	g.setColour(Colour(100, 100, 100));
	PathStrokeType psType(2.0f);
	psType.setJointStyle(PathStrokeType::JointStyle::beveled);
	g.strokePath(path, psType);
	
}

void PresetGUIComponent::resized()
{
	setBounds(0, 0, getWidth(), 40);
	curPreset.setBounds(10, 0, 150, 40);
	presetName.setBounds(110, 0, 250, 40);
	buttonLoadPreset.setBounds(320, 3, 100, 35);
	buttonSavePreset.setBounds(430, 3, 100, 35);
	
}

void PresetGUIComponent::buttonClicked(Button * button)
{
	if (button == &buttonSavePreset) 
	{
		//Open an explorer window to find locaiton to save to.
		FileChooser fileChooser("Location to save preset to...", File::getSpecialLocation(File::userHomeDirectory), "*.xml");
		
		if(fileChooser.browseForFileToSave(true)){
			File filetoSave(fileChooser.getResult());
			processor->setCurrentPresetName(filetoSave.getFileName().dropLastCharacters(4));
			if (processor->saveStateToFile(filetoSave)) {
				presetName.setText(filetoSave.getFileName().dropLastCharacters(4), dontSendNotification);
				DBG("Saved file");
				DBG(filetoSave.getFullPathName());
			}
			else {
				DBG("Failed to write file");
			}
		}
	}
	if (button == &buttonLoadPreset) 
	{
		FileChooser fileChooser("Preset to load...", File::getSpecialLocation(File::userHomeDirectory), "*.xml");

		if (fileChooser.browseForFileToOpen())
		{
			File filetoLoad(fileChooser.getResult());
			processor->setStateFromFile(filetoLoad);
			presetName.setText(processor->getCurrentPresetName(), dontSendNotification);
		}
	}
}

