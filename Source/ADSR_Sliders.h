/*
  ==============================================================================

    ADSR_Sliders.h
    Created: 21 Dec 2022 11:38:34am
    Author:  camro

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class ADSR_Sliders  : public juce::Component
{
public:
    ADSR_Sliders(FirstSamplerAudioProcessor& p);
    ~ADSR_Sliders() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Font mSliderFont{ 16.0f, juce::Font::bold };
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

    FirstSamplerAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSR_Sliders)
};
