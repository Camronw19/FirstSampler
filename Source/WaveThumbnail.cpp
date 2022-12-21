/*
  ==============================================================================

    WaveThumbnail.cpp
    Created: 21 Dec 2022 12:47:03pm
    Author:  camro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveThumbnail.h"

//==============================================================================
WaveThumbnail::WaveThumbnail(FirstSamplerAudioProcessor& p)
    : audioProcessor(p), sampleWave(p)
{
    mLoadButton.onClick = [&]()
    {
        sampleWave.setFileName(audioProcessor.loadFile());
        sampleWave.repaint();

    };

    //load button 
    addAndMakeVisible(mLoadButton);

    //sampleWave
    addAndMakeVisible(sampleWave);
}

WaveThumbnail::~WaveThumbnail()
{
}

void WaveThumbnail::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background 
}

void WaveThumbnail::resized()
{
    auto r = getLocalBounds(); 

    
    juce::Rectangle<int> rLoadButton(25, 10, getWidth() - 50, getHeight() / 5);
    mLoadButton.setBounds(rLoadButton); 
    r.removeFromTop(rLoadButton.getHeight() + 20); 
    
    juce::Rectangle<int> rSampleWave(getHeight() - r.getHeight(), 10, getWidth() - 20, r.getHeight() - 20);
    sampleWave.setBounds(r); 
}
