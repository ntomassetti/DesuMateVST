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
/***
	GUI Component for the top bar menu
***/
//==============================================================================
PresetGUIComponent::PresetGUIComponent ()
{
	//Labels
	curPreset.setText("Current Preset:", dontSendNotification);
	presetName.setText("init" , dontSendNotification);
	labelVer.setText(ProjectInfo::versionString, dontSendNotification);
	Font verFont = Font(7);
	Colour verTextCol = Colour(0.f, 0.0f, 1.0f, 0.35f);
	verTextCol.withAlpha(0.35f);
	labelVer.setColour(labelVer.textColourId, verTextCol);
	labelVer.setFont(verFont);
	addAndMakeVisible(curPreset);
	addAndMakeVisible(presetName);
	addAndMakeVisible(labelVer);
	//Buttons
	buttonLoadPreset.setButtonText("Load Preset");
	buttonLoadPreset.setColour(buttonLoadPreset.buttonColourId, Colour(25, 25, 25));
	buttonSavePreset.setButtonText("Save Preset");
	buttonSavePreset.setColour(buttonLoadPreset.buttonColourId, Colour(25, 25, 25));
	buttonInit.setButtonText("init");
	buttonInit.setColour(buttonLoadPreset.buttonColourId, Colour(25, 25, 25));
	buttonRand.setButtonText("rand");
	buttonRand.setColour(buttonLoadPreset.buttonColourId, Colour(25, 25, 25));

	buttonSavePreset.addListener(this);
	buttonLoadPreset.addListener(this);
	buttonInit.addListener(this);
	buttonRand.addListener(this);

	addAndMakeVisible(buttonLoadPreset);
	addAndMakeVisible(buttonSavePreset);
	addAndMakeVisible(buttonInit);
	addAndMakeVisible(buttonRand);
}

PresetGUIComponent::~PresetGUIComponent()
{

}

//==============================================================================
void PresetGUIComponent::paint (Graphics& g)
{

    g.fillAll (Colour(55, 55, 55));
	//Preset Border for label
	Path path;
	Rectangle<int> presetBorder(8, 4, 303, 34);
	g.setColour(Colour(17, 17, 17));
	path.addRoundedRectangle(presetBorder, 5.0f);
	g.fillPath(path);
	g.setColour(Colour(100, 100, 100));
	PathStrokeType psType(2.0f);
	psType.setJointStyle(PathStrokeType::JointStyle::beveled);//Not sure if this is actually influencing anything
	g.strokePath(path, psType);
	//Logo Image from PNG file
	imageLogo = ImageCache::getFromMemory(BinaryData::DesuLogo_01_png, BinaryData::DesuLogo_01_pngSize);
	g.setOpacity(0.35);
	g.drawImage(imageLogo, getWidth() - 160, 3, imageLogo.getWidth(), imageLogo.getHeight(), 0, 0, imageLogo.getWidth(), imageLogo.getHeight());
}

void PresetGUIComponent::resized()
{
	//Hard coded bounds since we don't want text wrapping on labels
	//Otherwise probably could be done in a cleaner fashion... (To do?)
	setBounds(0, 0, getWidth(), 40);
	curPreset.setBounds(10, 0, 150, 40);
	presetName.setBounds(110, 0, 250, 40);
	buttonLoadPreset.setBounds(320, 3, 100, 35);
	buttonSavePreset.setBounds(430, 3, 100, 35);
	buttonInit.setBounds(540, 3, 50, 35);
	buttonRand.setBounds(600, 3, 50, 35);
	labelVer.setBounds(getWidth() - 50, 0, 30, 30);
}

void PresetGUIComponent::buttonClicked(Button * button)
{
	if (button == &buttonSavePreset) 
	{
		//Open an explorer window to find locaiton to save to.
		FileChooser fileChooser("Select a preset to load...", processor->lastFileLocation, "*.desu");
		if(fileChooser.browseForFileToSave(true))
		{
			File filetoSave(fileChooser.getResult());
			processor->setCurrentPresetName(filetoSave.getFileName().dropLastCharacters(5));
			if (processor->saveStateToFile(filetoSave)) 
			{
				String newPresetName = filetoSave.getFileName().dropLastCharacters(5);
				presetName.setText(newPresetName, dontSendNotification);
				DBG("Saved file");
				DBG(filetoSave.getFullPathName());
			}
			else 
			{
				DBG("Failed to write file");
			}

			processor->lastFileLocation = fileChooser.getResult().getParentDirectory();
		}
	}
	if (button == &buttonLoadPreset) 
	{
		//To do: Create config file that can save and change preset folder location.
		//For now we default to the documents directory.
		FileChooser fileChooser("Select a preset to load...", processor->lastFileLocation, "*.desu");


		if (fileChooser.browseForFileToOpen())
		{
			File filetoLoad(fileChooser.getResult());
			processor->setStateFromFile(filetoLoad);
			presetName.setText(processor->getCurrentPresetName(), dontSendNotification);
			processor->lastFileLocation = fileChooser.getResult().getParentDirectory();
		}
	}
	if (button == &buttonInit)
	{
		processor->InitParameters();
		processor->setCurrentPresetName(String("init"));
		presetName.setText("init", dontSendNotification);
	}
	if (button == &buttonRand)
	{
		processor->RandomizeParameters();
	}
}

