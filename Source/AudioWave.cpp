/*
  ==============================================================================

    AudioWave.cpp
    Created: 16 Dec 2022 8:51:08am
    Author:  camro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioWave.h"

//==============================================================================
AudioWave::AudioWave(FirstSamplerAudioProcessor& p)
    : audioProcessor(p), mShouldBePainting(false) // buffer(nullptr)
{
    
}

AudioWave::~AudioWave()
{
   // delete buffer; 
}

void AudioWave::paint (juce::Graphics& g)
{
       g.fillAll (juce::Colours::cadetblue);   // clear the background

    
    if (mShouldBePainting)
    {
        g.setColour(juce::Colours::yellow); 
        juce::Path a;
       

        mAudioPoints.clear();
    

        juce::AudioSampleBuffer* waveForm = &audioProcessor.getWaveForm();
        int ratio = waveForm->getNumSamples() / getWidth();
      
        

       auto buffer = (waveForm->getReadPointer(0));
        
        //scale audio file to windows x-axis
        for (int sample = 0; sample < waveForm->getNumSamples(); sample += ratio)
        {
            mAudioPoints.push_back(buffer[sample]);
        }
     
        a.startNewSubPath(0, getHeight() / 2);

        //scale y axis                    
        for (int sample = 0; sample < mAudioPoints.size(); ++sample)
        {
            auto point = juce::jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, getHeight(), 0);
            a.lineTo(sample, point);
        }

        g.strokePath(a, juce::PathStrokeType(1));
        mShouldBePainting = false;
        buffer = nullptr; 
        waveForm = nullptr; 
    }
    
    
}

void AudioWave::resized()
{
   
}
