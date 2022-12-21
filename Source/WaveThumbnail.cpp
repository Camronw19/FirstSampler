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
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

  
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
