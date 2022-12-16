/*
  ==============================================================================

    AudioWave.h
    Created: 16 Dec 2022 8:51:08am
    Author:  camro

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"
#include <JuceHeader.h>

//==============================================================================
/*
*/
class AudioWave  : public juce::Component
{
public:
    AudioWave(FirstSamplerAudioProcessor& p);
    ~AudioWave() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void PaintWave(bool x) { mShouldBePainting = x; }

private:
    bool mShouldBePainting;
    juce::TextButton mLoadButton{ "Load" };
    juce::Label loadLabel;

    std::vector<float> mAudioPoints;
    const float* buffer; 

    FirstSamplerAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioWave)
};
