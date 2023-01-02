/*
  ==============================================================================

    WaveThumbnail.h
    Created: 21 Dec 2022 12:47:03pm
    Author:  camro

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AudioWave.h"

//==============================================================================
/*
*/
class WaveThumbnail  : public juce::Component
{
public:
    WaveThumbnail(FirstSamplerAudioProcessor&);
    ~WaveThumbnail() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    AudioWave sampleWave;
    juce::TextButton mLoadButton{ "Load" };
    juce::TextButton mShowADSR; 
    juce::ComboBox mPolyMenu; 
    
    juce::Font mButtonFont{ 16.0f, juce::Font::bold };
    

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> polyAttachment;
    FirstSamplerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveThumbnail)
};
