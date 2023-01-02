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
class AudioWave  : public juce::Component,
                   public juce::FileDragAndDropTarget
{
public:
    AudioWave(FirstSamplerAudioProcessor& p);
    ~AudioWave() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;
    void setFileName(juce::String F) { mFileName = F; }
    void paintADSR() { mPaintADSR = !mPaintADSR; repaint(); }
    bool isPaintingADSR() { return mPaintADSR; }

private:
    bool mShouldBePainting;
    bool mPaintADSR; 
    juce::TextButton mLoadButton{ "Load" };
    juce::Label loadLabel;
    juce::String mFileName { "" }; 

    std::vector<float> mAudioPoints;
   // const float* buffer; 

    FirstSamplerAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioWave)
};
