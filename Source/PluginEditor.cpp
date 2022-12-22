/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FirstSamplerAudioProcessorEditor::FirstSamplerAudioProcessorEditor (FirstSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), mWaveThumbnail(p), mADSRSliders(p)
{

   // getLookAndFeel().setColour(juce::ResizableWindow::backgroundColourId, juce::Colour::fromRGB(81,90,98)); 
    addAndMakeVisible(mWaveThumbnail); 
    addAndMakeVisible(mADSRSliders);

    startTimerHz(30); 


    setSize (600, 500);
}

FirstSamplerAudioProcessorEditor::~FirstSamplerAudioProcessorEditor()
{
    stopTimer();
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
    r.removeFromTop(rSampWave.getHeight() + 30);

    juce::Rectangle<int> rSliders(75, (getHeight() - r.getHeight()), getWidth() - 150, r.getHeight() - 60); 
    mADSRSliders.setBounds(rSliders);
    //r.removeFromTop(rSliders.getHeight() + 20); 
}

//==============================================================================

void FirstSamplerAudioProcessorEditor::timerCallback()
{
    static bool ResetPlayhead = false; 

    if (audioProcessor.isNotePlayed())
    {
        mWaveThumbnail.getChildComponent(1)->repaint(); 
        ResetPlayhead = true; 
    }
    else
    {
        if (ResetPlayhead)
        {
            mWaveThumbnail.getChildComponent(1)->repaint();
            ResetPlayhead = false; 
        }
    }
}