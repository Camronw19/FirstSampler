/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveThumbnail.h"
#include "ADSR_Sliders.h"

//==============================================================================
/**
*/
class FirstSamplerAudioProcessorEditor  : public juce::AudioProcessorEditor, 
                                          public juce::Timer
                                          
{
public:
    FirstSamplerAudioProcessorEditor (FirstSamplerAudioProcessor&);
    ~FirstSamplerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void timerCallback() override; 

private:
    WaveThumbnail mWaveThumbnail;
    ADSR_Sliders mADSRSliders; 
    
    FirstSamplerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FirstSamplerAudioProcessorEditor)
};
