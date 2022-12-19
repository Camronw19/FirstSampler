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
       juce::Rectangle<float> window, windowFill; 
       window.setBounds(0, 0, getWidth(), getHeight());
       windowFill.setBounds(2, 2, getWidth() - 4, getHeight() - 4);

       g.setColour(juce::Colours::cadetblue);
       g.fillRoundedRectangle(windowFill, 5); 

      
    
    if (mShouldBePainting)
    {
        g.setColour(juce::Colours::yellow); 
        juce::Path a;

        mAudioPoints.clear();
        juce::AudioSampleBuffer* waveForm = &audioProcessor.getWaveForm(); //pointer ro wave form
        auto buffer = (waveForm->getReadPointer(0)); //read only pointer to wave form 
        int ratio = waveForm->getNumSamples() / getWidth();
        
        //scale audio file to windows x-axis
        for (int sample = 0; sample < waveForm->getNumSamples(); sample += ratio)
        {
            mAudioPoints.push_back(buffer[sample]);
        }
     
        a.startNewSubPath(5, getHeight() / 2);

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

    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(window, 10, 3);
    
    
}

void AudioWave::resized()
{
   
}
