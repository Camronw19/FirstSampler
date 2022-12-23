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
    mLoadButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(65, 69, 86));
    mLoadButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colour::fromRGB(65, 69, 86));

    mLoadButton.setColour(juce::TextButton::textColourOffId, juce::Colour::fromRGB(255, 255, 255));
    addAndMakeVisible(mLoadButton);

    //poly menu
    mPolyMenu.setJustificationType(juce::Justification::centred); 
    mPolyMenu.setText("Polyphony"); 
    mPolyMenu.addItem("1", 1);
    mPolyMenu.addItem("2", 2);
    mPolyMenu.addItem("3", 3);
    mPolyMenu.addItem("4", 4);
    mPolyMenu.setColour(juce::ComboBox::backgroundColourId, juce::Colour::fromRGB(65, 69, 86)); 
    mPolyMenu.setColour(juce::ComboBox::ColourIds::buttonColourId, juce::Colour::fromRGB(65, 69, 86));
    addAndMakeVisible(mPolyMenu); 

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
    
    juce::Rectangle<int> rLoadButton(0, 10, 110, getHeight() / 8);
    mLoadButton.setBounds(rLoadButton); 

    juce::Rectangle<int> rPolyMenu(130, 10, 150, getHeight() / 8); 
    mPolyMenu.setBounds(rPolyMenu); 
    r.removeFromTop(rLoadButton.getHeight() + 20); 
    
    juce::Rectangle<int> rSampleWave(getHeight() - r.getHeight(), 10, getWidth() - 20, r.getHeight() - 20);
    sampleWave.setBounds(r); 
}
