/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FirstSamplerAudioProcessorEditor::FirstSamplerAudioProcessorEditor (FirstSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), mWaveThumbnail(p), sliders(p)
{
    addAndMakeVisible(mWaveThumbnail); 

    addAndMakeVisible(sliders); 

    setSize (600, 500);
}

FirstSamplerAudioProcessorEditor::~FirstSamplerAudioProcessorEditor()
{
    
}

//==============================================================================
void FirstSamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));  
}

void FirstSamplerAudioProcessorEditor::resized()
{
    auto r = getLocalBounds(); 
    //loadLabel.setBounds(r.removeFromTop(20)); 
    r.removeFromTop(10); 

    
    juce::Rectangle<int> rSampWave(50, (getHeight() - r.getHeight()) + 20, getWidth() - 100, getHeight()/ 1.8);
    mWaveThumbnail.setBounds(rSampWave);
    r.removeFromTop(rSampWave.getHeight() + 40);

    juce::Rectangle<int> rSliders(75, (getHeight() - r.getHeight()), getWidth() - 150, r.getHeight() - 20); 
    sliders.setBounds(rSliders);
    //r.removeFromTop(rSliders.getHeight() + 20); 
}

//==============================================================================
