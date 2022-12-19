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

    /*
    //load label
    loadLabel.setText("Load a Sound",juce::dontSendNotification); 
    loadLabel.setJustificationType(juce::Justification::centred); 
    loadLabel.setColour(juce::Label::backgroundColourId, juce::Colours::grey);
    addAndMakeVisible(loadLabel); 
    */

    //load button 
    addAndMakeVisible(mLoadButton); 
 
    //sampleWave
    addAndMakeVisible(sampleWave); 

    //sliders + Labels
        //attack
    mAttackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20); 
    mAttackSlider.setRange(0.0f, 5.0f, 0.01); 
    addAndMakeVisible(mAttackSlider); 

    mAttackLabel.setFont(15.0f); 
    mAttackLabel.setText("Attack", juce::dontSendNotification); 
    mAttackLabel.setJustificationType(juce::Justification::centredTop); 
    mAttackLabel.attachToComponent(&mAttackSlider, false); 

        //Decay
    mDecaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mDecaySlider.setRange(0.0f, 5.0f, 0.01);
    addAndMakeVisible(mDecaySlider);

    mDecayLabel.setFont(15.0f);
    mDecayLabel.setText("Decay", juce::dontSendNotification);
    mDecayLabel.setJustificationType(juce::Justification::centredTop);
    mDecayLabel.attachToComponent(&mDecaySlider, false);

        //Sustain
    mSustainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mSustainSlider.setRange(0.0f, 5.0f, 0.01);
    addAndMakeVisible(mSustainSlider);

    mSustainLabel.setFont(15.0f);
    mSustainLabel.setText("Sustain", juce::dontSendNotification);
    mSustainLabel.setJustificationType(juce::Justification::centredTop);
    mSustainLabel.attachToComponent(&mSustainSlider, false);

        //Release
    mReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    mReleaseSlider.setRange(0.0f, 5.0f, 0.01);
    addAndMakeVisible(mReleaseSlider);

    mReleaseLabel.setFont(15.0f);
    mReleaseLabel.setText("Release", juce::dontSendNotification);
    mReleaseLabel.setJustificationType(juce::Justification::centredTop);
    mReleaseLabel.attachToComponent(&mReleaseSlider, false);



    setSize (600, 500);
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
    /*
    if (audioProcessor.getNumSamplerSounds() > 0)
    {
        loadLabel.setText("Sound Loaded", juce::dontSendNotification);

    }
    else
        loadLabel.setText("Load a Sound", juce::dontSendNotification);
    */
    


}

void FirstSamplerAudioProcessorEditor::resized()
{
    auto r = getLocalBounds(); 
    //loadLabel.setBounds(r.removeFromTop(20)); 
    r.removeFromTop(10); 

    juce::Rectangle<int> rButton (getWidth() / 2 - getWidth() / 4, (getHeight() - r.getHeight()) + 10, 300, 60);
    r.removeFromTop(rButton.getHeight() + 20);
    mLoadButton.setBounds(rButton); 
    
    juce::Rectangle<int> rSampWave(getWidth() / 2 - getWidth() / 2.4, (getHeight() - r.getHeight()) + 20, 500, 200);
    r.removeFromTop(rSampWave.getHeight() + 40);
    sampleWave.setBounds(rSampWave); 

    juce::Rectangle<int> rSliders(getWidth() / 2 - getWidth() / 2.4, (getHeight() - r.getHeight()) + 20, 500, 100);
    mAttackSlider.setBounds(rSliders.removeFromLeft(rSliders.getWidth() / 4));
    mDecaySlider.setBounds(rSliders.removeFromLeft(rSliders.getWidth() / 3));
    mSustainSlider.setBounds(rSliders.removeFromLeft(rSliders.getWidth() / 2));
    mReleaseSlider.setBounds(rSliders.removeFromLeft(rSliders.getWidth() ));
    

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