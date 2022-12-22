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

    g.setColour(juce::Colour::fromRGB(45, 49, 66));
    g.fillRoundedRectangle(windowFill, 5); 

    
    juce::AudioSampleBuffer* waveForm = &audioProcessor.getWaveForm(); //pointer ro wave form
    
    if (waveForm->getNumSamples() > 0)
    {
        //wave drawing============================================================
        g.setColour(juce::Colour::fromRGB(246, 133, 84));
        juce::Path a;

        mAudioPoints.clear();
        auto buffer = (waveForm->getReadPointer(0)); //read only pointer to wave form 
        int ratio = waveForm->getNumSamples() / getWidth();
        
        //scale audio file to windows x-axis
        for (int sample = 0; sample < waveForm->getNumSamples(); sample += ratio)
        {
            mAudioPoints.push_back(buffer[sample]);
        }
     
        a.startNewSubPath(2, getHeight() / 2);

        //scale y axis                    
        for (int sample = 0; sample < mAudioPoints.size(); ++sample)
        {
            auto point = juce::jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, getHeight(), 0);
            a.lineTo(sample + 2, point);
        }

        g.strokePath(a, juce::PathStrokeType(1));
        mShouldBePainting = false;
        buffer = nullptr; 
        waveForm = nullptr; 

        //file name================================================================
        g.setColour(juce::Colours::white); 
        g.setFont(15.0f); 
        auto textBounds = getLocalBounds().reduced(10, 10); 
        g.drawFittedText(mFileName, textBounds, juce::Justification::topRight, 1);

        //playhead=================================================================

        auto playheadPosition = juce::jmap<int>(audioProcessor.getSampleCount(),
            0, audioProcessor.getWaveForm().getNumSamples(), 3, getWidth());

        g.setColour(juce::Colours::lightgrey); 
        g.drawLine(playheadPosition, 2, playheadPosition, getHeight() - 2, 2.0f);
        g.setColour(juce::Colours::black.withAlpha(0.2f));
        g.fillRect(2,2,playheadPosition - 2, getHeight() - 2); 

        if (playheadPosition > 6)
        {
            g.setColour(juce::Colours::lightgrey);
            juce::Path playheadHead; 
            playheadHead.startNewSubPath(playheadPosition - 4, 2); 
            //auto pPoint = (playheadPosition + 4, 2); 
            playheadHead.lineTo(playheadPosition + 6, 2);
            playheadHead.lineTo(playheadPosition, 9);
            playheadHead.lineTo(playheadPosition - 6, 2);
            g.strokePath(playheadHead, juce::PathStrokeType(1));
            g.fillPath(playheadHead); 
        }


        //=========================================================================
    }

    g.setColour(juce::Colours::black);
    g.drawRoundedRectangle(window, 10, 3);
    
    
}

void AudioWave::resized()
{
    
}

bool AudioWave::isInterestedInFileDrag(const juce::StringArray& files)
{
    for (auto file : files)
    {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aif"))
        {
            return true;
        }
    }
    return false;
}

void AudioWave::filesDropped(const juce::StringArray& files, int x, int y)
{
    for (auto file : files)
    {
        if (isInterestedInFileDrag(file))
        {
            //get file name to paint
            auto myFile = std::make_unique<juce::File>(file); 
            mFileName = myFile->getFileNameWithoutExtension(); 

            //load this file 
            audioProcessor.loadFile(file); 
            repaint(); 
        }
    }
}
