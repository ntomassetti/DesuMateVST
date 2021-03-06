/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DesuMateAudioProcessorEditor::DesuMateAudioProcessorEditor (DesuMateAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	presetComp.setProcessor(&processor);
	addAndMakeVisible(presetComp);
	int colorMult = 100;
	auto& params = processor.getParameters();
	for (auto pa : params)
	{

		if (auto* param = dynamic_cast<AudioParameterFloat*> (pa))
		{
			Slider* aSlider;
			
			paramSliders.add(aSlider = new Slider(param->name));
			if (param->name == "Bit Rate" || param->name == "Input Filter Type" || param->name == "Output Filter Type")
			{
				aSlider->setRange(param->range.start, param->range.end, 1);
				if (param->name == "Input Filter Type" || param->name == "Output Filter Type") 
				{
					aSlider->textFromValueFunction = [](double value)
					{
						String filterType;
						switch ((int)value)
						{
							case 0:
								filterType = "Highpass Filter";
								break;
							case 1:
								filterType = "Bandpass Filter";
								break;
							case 2:
								filterType = "Lowpass Filter";
							default:
								filterType = "Lowpass Filter";
								break;
						}
						return filterType;
					};
				}
			}
			else if (param->name == "Output Gain")
			{
				aSlider->setRange(param->range.start, param->range.end);
				aSlider->setNumDecimalPlacesToDisplay(2);
				aSlider->setSkewFactor(1.5f);
			}
			else if (param->name == "Samplerate Reduction")
			{
				aSlider->setRange(param->range.start, param->range.end);
				aSlider->setNumDecimalPlacesToDisplay(3);
				aSlider->setSkewFactor(0.5f);
			}
			else
			{
				aSlider->setRange(param->range.start, param->range.end);
				aSlider->setNumDecimalPlacesToDisplay(3);
				aSlider->setSkewFactor(.25f);

			}
			if (auto* p = dynamic_cast<AudioProcessorParameterWithID*> (pa))
			{
				aSlider->setDoubleClickReturnValue(true, param->range.convertFrom0to1(p->getDefaultValue()));
			}
			aSlider->setSliderStyle(Slider::LinearBar);

			aSlider->setColour(Slider::ColourIds::trackColourId, Colour(0, colorMult, 218));
			aSlider->setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::black);
			aSlider->setValue(*param);
			aSlider->onValueChange = [this, aSlider] { changeSliderValue(aSlider); };
			aSlider->onDragStart = [this, aSlider] { startDragChange(aSlider); };
			aSlider->onDragEnd = [this, aSlider] { endDragChange(aSlider); };
			
			addAndMakeVisible(aSlider);

			Label* aLabel;
			paramLabels.add(aLabel = new Label(param->name, param->name));
			aLabel->setColour(Label::ColourIds::backgroundColourId, Colour(0, colorMult, 218));
			aLabel->setColour(Label::ColourIds::outlineColourId, Colours::black);
			addAndMakeVisible(aLabel);
			colorMult += 10;
		}

	}
	noParameterLabel.setJustificationType(Justification::horizontallyCentred | Justification::verticallyCentred);
	noParameterLabel.setFont(noParameterLabel.getFont().withStyle(Font::italic));
	
	//Resizeable
	setResizable(true, true);
	setResizeLimits(300, paramControlHeight * paramSliders.size() + 40, 12000, paramControlHeight * paramSliders.size()+40);
	//
	if (paramSliders.size() == 0)
	{
		addAndMakeVisible(noParameterLabel);
		setSize(250, 250);
	}
	else
	{
		setSize(paramSliderWidth + paramLabelWidth,
			jmax(100, paramControlHeight * paramSliders.size() + 40));

		startTimer(100);
	}
}

DesuMateAudioProcessorEditor::~DesuMateAudioProcessorEditor()
{
}

//==============================================================================
void DesuMateAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	Image BGImage;
	BGImage = ImageCache::getFromMemory(BinaryData::HA_BG_Logo_01_png, BinaryData::HA_BG_Logo_01_pngSize);
    g.fillAll (Colour(35, 35, 35));
	if (HABuild)
	{
		g.setOpacity(0.15f);
		g.drawImage(BGImage, getWidth()*0.4, getHeight()* 0.28, BGImage.getWidth()*0.7f, BGImage.getHeight()*0.7f, 0, 0, BGImage.getWidth(), BGImage.getHeight());

	}
}

void DesuMateAudioProcessorEditor::resized()
{
	auto r = getLocalBounds();
	noParameterLabel.setBounds(r);
	presetComp.setBounds(0, 0, getWidth(), 40);
	for (auto i = 0; i < paramSliders.size(); ++i)
	{
		auto paramBounds = r.removeFromTop(paramControlHeight);
		auto labelBounds = paramBounds.removeFromLeft(paramLabelWidth);

		paramLabels[i]->setBounds(labelBounds.getX(), labelBounds.getY() + 40, labelBounds.getWidth(), labelBounds.getHeight());
		paramSliders[i]->setBounds(paramBounds.getX(), paramBounds.getY() + 40, paramBounds.getWidth(), paramBounds.getHeight());
	}
	//processor.lastUIWidth = getWidth();
	//processor.lastUIHeight = getHeight();
}

void DesuMateAudioProcessorEditor::changeSliderValue(Slider * slider)
{
	if (auto* param = getParameterForSlider(slider))
		*param = (float)slider->getValue();
}

void DesuMateAudioProcessorEditor::startDragChange(Slider * slider)
{
	if (auto* param = getParameterForSlider(slider))
		param->beginChangeGesture();
}

void DesuMateAudioProcessorEditor::endDragChange(Slider* slider)
{
	if (auto* param = getParameterForSlider(slider))
		param->endChangeGesture();
}


AudioParameterFloat * DesuMateAudioProcessorEditor::getParameterForSlider(Slider * slider)
{
	auto& params = getAudioProcessor()->getParameters();
	return dynamic_cast<AudioParameterFloat*> (params[paramSliders.indexOf(slider)]);
}

void DesuMateAudioProcessorEditor::timerCallback()
{
	auto& params = getAudioProcessor()->getParameters();

	for (auto i = 0; i < params.size(); i++) {
		if (auto* param = dynamic_cast<AudioParameterFloat*> (params[i]))
		{
			if (i < paramSliders.size()) 
				paramSliders[i]->setValue(*param);
		}
	}
}
