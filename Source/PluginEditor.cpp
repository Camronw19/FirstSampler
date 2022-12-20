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

    //load button 
    addAndMakeVisible(mLoadButton); 
 
    //sampleWave
    addAndMakeVisible(sampleWave); 

    //sliders + Labels ==============================================
        //attack
    mAttackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20); 
    addAndMakeVisible(mAttackSlider); 

    mAttackLabel.setFont(15.0f); 
    mAttackLabel.setText("Attack", juce::dontSendNotification); 
    mAttackLabel.setJustificationType(juce::Justification::centredTop); 
    mAttackLabel.attachToComponent(&mAttackSlider, false); 

    attackSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "ATTACK", mAttackSlider);

        //Decay
    mDecaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(mDecaySlider);

    mDecayLabel.setFont(15.0f);
    mDecayLabel.setText("Decay", juce::dontSendNotification);
    mDecayLabel.setJustificationType(juce::Justification::centredTop);
    mDecayLabel.attachToComponent(&mDecaySlider, false);

    decaySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "DECAY", mDecaySlider);
    
        //Sustain
    mSustainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(mSustainSlider);

    mSustainLabel.setFont(15.0f);
    mSustainLabel.setText("Sustain", juce::dontSendNotification);
    mSustainLabel.setJustificationType(juce::Justification::centredTop);
    mSustainLabel.attachToComponent(&mSustainSlider, false);

    sustainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "SUSTAIN", mSustainSlider);

        //Release
    mReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(mReleaseSlider);

    mReleaseLabel.setFont(15.0f);
    mReleaseLabel.setText("Release", juce::dontSendNotification);
    mReleaseLabel.setJustificationType(juce::Justification::centredTop);
    mReleaseLabel.attachToComponent(&mReleaseSlider, false);

    releaseSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "RELEASE", mReleaseSlider);
    
    //==================================================================
     
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