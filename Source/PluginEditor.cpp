/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FirstSamplerAudioProcessorEditor::FirstSamplerAudioProcessorEditor (FirstSamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), sampleWave(p)
{
    mLoadButton.onClick = [&]()
    {
        audioProcessor.loadFile(); 
        sampleWave.PaintWave(true);
        sampleWave.repaint();
    };

    //load label
    loadLabel.setText("Load a Sound",juce::dontSendNotification); 
    loadLabel.setJustificationType(juce::Justification::centred); 
    loadLabel.setColour(juce::Label::backgroundColourId, juce::Colours::grey);
    addAndMakeVisible(loadLabel); 

    //load button 
    addAndMakeVisible(mLoadButton); 
 
    //sampleWave
    addAndMakeVisible(sampleWave); 



    setSize (600, 400);
}

FirstSamplerAudioProcessorEditor::~FirstSamplerAudioProcessorEditor()
{
    
}

//==============================================================================
void FirstSamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    
    
    //if a sound is loaded will display "Sound loaded" if a sound is not loaded will display "Load a sound"  
    if (audioProcessor.getNumSamplerSounds() > 0)
    {
        loadLabel.setText("Sound Loaded", juce::dontSendNotification);

    }
    else
        loadLabel.setText("Load a Sound", juce::dontSendNotification);

    


}

void FirstSamplerAudioProcessorEditor::resized()
{
    auto r = getLocalBounds(); 
    loadLabel.setBounds(r.removeFromTop(20)); 

    juce::Rectangle<int> rButton (getWidth() / 2 - 150, (getHeight() - r.getHeight()) + 20, 300, 60);
    r.removeFromTop(rButton.getHeight() + 20);
    mLoadButton.setBounds(rButton); 
    
    juce::Rectangle<int> rSampWave(getWidth() / 2 - 250, (getHeight() - r.getHeight()) + 20, 500, 200);
    sampleWave.setBounds(rSampWave); 
    

}

//==============================================================================
bool FirstSamplerAudioProcessorEditor::isInterestedInFileDrag(const juce::StringArray& files)
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

void FirstSamplerAudioProcessorEditor::filesDropped(const juce::StringArray& files, int x, int y)
{
    for (auto file : files)
    {
        if (isInterestedInFileDrag(file))
        {
            //load this file 
            audioProcessor.loadFile(file); 
            sampleWave.PaintWave(true); 
            sampleWave.repaint(); 
        }
    }
}