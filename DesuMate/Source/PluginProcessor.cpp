/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DesuMateAudioProcessor::DesuMateAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	//memory allocation
	Decimation = new Decimator[getNumOutputChannels()];

	//Params
	addParameter(bitDepth = new AudioParameterFloat("bitDepth", "Bit Rate", 1.f, 32.f, 16.f));
	addParameter(sampleRateReduction = new AudioParameterFloat("sampleRateReduction", "Samplerate Reduction", 0.001f, 1.00f, 1.00f));
}

DesuMateAudioProcessor::~DesuMateAudioProcessor()
{
	delete [] Decimation;
}

//==============================================================================
const String DesuMateAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DesuMateAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DesuMateAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DesuMateAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DesuMateAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DesuMateAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DesuMateAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DesuMateAudioProcessor::setCurrentProgram (int index)
{
}

const String DesuMateAudioProcessor::getProgramName (int index)
{
    return {};
}

void DesuMateAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DesuMateAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

}

void DesuMateAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
	
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DesuMateAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DesuMateAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
		Decimation[channel].updateParameters(*bitDepth,*sampleRateReduction);
		auto* inputBuffer = buffer.getReadPointer(channel);
		
		auto* outputBuffer = buffer.getWritePointer (channel);
		for (int i = 0; i < buffer.getNumSamples(); i++) {
			outputBuffer[i] = Decimation[channel].process(inputBuffer[i]);
		}
        
    }
}

//==============================================================================
bool DesuMateAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DesuMateAudioProcessor::createEditor()
{
    return new DesuMateAudioProcessorEditor (*this);
}

//==============================================================================
void DesuMateAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	MemoryOutputStream(destData, true).writeFloat(*bitDepth);
	MemoryOutputStream(destData, true).writeFloat(*sampleRateReduction);
}

void DesuMateAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	*bitDepth = MemoryInputStream(data, static_cast<size_t> (sizeInBytes), false).readFloat();
	*sampleRateReduction = MemoryInputStream(data, static_cast<size_t> (sizeInBytes), false).readFloat();
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DesuMateAudioProcessor();
}
