/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class FirstSamplerAudioProcessor  : public juce::AudioProcessor, 
                                    public juce::ValueTree::Listener
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    FirstSamplerAudioProcessor();
    ~FirstSamplerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::String loadFile(); 
    void loadFile(const juce::String& path); 

    int getNumSamplerSounds() { return mSampler.getNumSounds(); }
    juce::AudioBuffer<float>& getWaveForm() { return mWaveForm; }
    
    void updateGain(); 
    void updateADSR(); 
    void updatePoly();
    juce::ADSR::Parameters& getADSRParams() { return mADSRParameters;  }
    juce::AudioProcessorValueTreeState& getAPVTS() { return mAPVTS; }

    std::atomic<bool>& isNotePlayed() { return mIsNotePlayed; }
    std::atomic<int>& getSampleCount() { return mSampleCount; }

    float getSampleLength() { return mFormatReader->lengthInSamples / getSampleRate(); }

private:
    juce::Synthesiser mSampler; 
    const int mNumVoices{ 3 }; 
    juce::AudioBuffer<float> mWaveForm;

    juce::AudioFormatManager mFormatManager; 
    juce::AudioFormatReader* mFormatReader { nullptr }; 

    juce::AudioProcessorValueTreeState mAPVTS; 
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters(); 
    juce::ADSR::Parameters mADSRParameters; 
    void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override; 

    std::atomic<bool> mIsNotePlayed{ false }; 
    std::atomic<int> mSampleCount{ 0 }; 
    std::atomic<float> currentGain{.015};
    std::atomic<int> mPoly{ 3 }; 
    float previousGain{ 0 }; 
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FirstSamplerAudioProcessor)
};
