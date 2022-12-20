/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "AudioWave.h"

//==============================================================================
/**
*/
class FirstSamplerAudioProcessorEditor  : public juce::AudioProcessorEditor, 
                                          public juce::FileDragAndDropTarget
{
public:
    FirstSamplerAudioProcessorEditor (FirstSamplerAudioProcessor&);
    ~FirstSamplerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    bool isInterestedInFileDrag(const juce::StringArray& files) override; 
    void filesDropped(const juce::StringArray& files, int x, int y) override; 

private:


    juce::TextButton mLoadButton { "Load" }; 
    //juce::Label loadLabel; 

    AudioWave sampleWave; 

    //sliders ==================================================================================
    juce::Slider mAttackSlider, mDecaySlider, mSustainSlider, mReleaseSlider; 
        //slider labels
    juce::Label mAttackLabel, mDecayLabel, mSustainLabel, mReleaseLabel; 
        //listener for sliders
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackSliderAttachment; 
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decaySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseSliderAttachment;

    //===========================================================================================

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FirstSamplerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FirstSamplerAudioProcessorEditor)
};
