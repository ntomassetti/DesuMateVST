/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "decimator.h"
//==============================================================================
/**
*/

enum FilterTypes
{
	HighPass,
	BandPass,
	LowPass
};

class DesuMateAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    DesuMateAudioProcessor();
    ~DesuMateAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

	void setCurrentPresetName(String& newName);
	String getCurrentPresetName();
	void saveStateToXML(XmlElement& xmlState);
	void loadStateFromXML(XmlElement* xmlState);
	void getStateAsText(String& destStr);
	void setStateFromText(const String& stateStr);
	bool saveStateToFile(File newFile);
	void setStateFromFile(File newFile);
    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	void UpdateParameters();

	/*Resets paramters to their default values defined in the constructor*/
	void InitParameters();


	dsp::StateVariableFilter::Parameters<float>::Type SelectFilterType(int inType);

	/*dB to gain*/
	float dBToGain(float inDB) { return pow(10.0f, inDB / 20.0f); };

public:
	/*Store the last file location opened for presets since it 
	does not call the constructor upon opening and closing GUI.
	Temp solution until some sort of config file can maintain
	this information...*/
	File lastFileLocation = File::getSpecialLocation(File::commonDocumentsDirectory);

private:
	//////////////////////////
	//Params
	//Gain
	AudioParameterFloat* inputGain;
	AudioParameterFloat* outputGain;
	//Input Filter
	AudioParameterFloat* inFilterType;
	AudioParameterFloat* inFilterFreq;
	AudioParameterFloat* inFilterRes;
	//Output Filter
	AudioParameterFloat* outFilterType;
	AudioParameterFloat* outFilterFreq;
	AudioParameterFloat* outFilterRes;
	//Decimator
	AudioParameterFloat* bitDepth;
	AudioParameterFloat* sampleRateReduction;
	/////////////////////////
	dsp::ProcessorDuplicator<dsp::StateVariableFilter::Filter<float>, dsp::StateVariableFilter::Parameters<float>> inFilter, outFilter;
	dsp::Gain<float> outputVolGain;
	//
	Decimator* Decimation;
	//
	String presetName = "init";
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DesuMateAudioProcessor)
};
