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
	int colorMult = 128;
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
				if (param->name == "Input Filter Type" || param->name == "Output Filter Type") {
					aSlider->textFromValueFunction = [](double value) {
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
			else {
				aSlider->setRange(param->range.start, param->range.end);
				aSlider->setSkewFactor(.25f);
			}
			aSlider->setSliderStyle(Slider::LinearBar);
			
			aSlider->setColour(Slider::ColourIds::trackColourId, Colour(0, colorMult, colorMult));
			aSlider->setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::black);
			//aSlider->setSliderStyle(Slider::LinearHorizontal);
			//getLookAndFeel().setColour(Slider::backgroundColourId, Colours::red);
			aSlider->setValue(*param);

			aSlider->onValueChange = [this, aSlider] { changeSliderValue(aSlider); };
			aSlider->onDragStart = [this, aSlider] { startDragChange(aSlider); };
			aSlider->onDragEnd = [this, aSlider] { endDragChange(aSlider); };

			addAndMakeVisible(aSlider);

			Label* aLabel;
			paramLabels.add(aLabel = new Label(param->name, param->name));
			aLabel->setColour(Label::ColourIds::backgroundColourId, Colour(0, colorMult, colorMult));
			aLabel->setBorderSize(BorderSize<int>(4));
			aLabel->setColour(Label::ColourIds::outlineColourId, Colours::black);
			addAndMakeVisible(aLabel);
			colorMult -= 10;
		}

	}
	noParameterLabel.setJustificationType(Justification::horizontallyCentred | Justification::verticallyCentred);
	noParameterLabel.setFont(noParameterLabel.getFont().withStyle(Font::italic));
	setResizable(true, true);
	setResizeLimits(300, paramControlHeight * paramSliders.size(), 12000, paramControlHeight * paramSliders.size());
	if (paramSliders.size() == 0)
	{
		addAndMakeVisible(noParameterLabel);
		setSize(300, 100);
	}
	else
	{
		setSize(paramSliderWidth + paramLabelWidth,
			jmax(100, paramControlHeight * paramSliders.size()));

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
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
/*
    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
	*/
}

void DesuMateAudioProcessorEditor::resized()
{
	auto r = getLocalBounds();
	noParameterLabel.setBounds(r);

	for (auto i = 0; i < paramSliders.size(); ++i)
	{
		auto paramBounds = r.removeFromTop(paramControlHeight);
		auto labelBounds = paramBounds.removeFromLeft(paramLabelWidth);

		paramLabels[i]->setBounds(labelBounds);
		paramSliders[i]->setBounds(paramBounds);
	}
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

void DesuMateAudioProcessorEditor::endDragChange(Slider * slider)
{
	if (auto* param = getParameterForSlider(slider))
		param->endChangeGesture();
}

void DesuMateAudioProcessorEditor::filterSliderTypeValue(Slider * slider)
{
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
		if (auto* param = dynamic_cast<AudioParameterFloat*> (params[i])) {
			if (i < paramSliders.size())
				paramSliders[i]->setValue(*param);
		}
	}
}
