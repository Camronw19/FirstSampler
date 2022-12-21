/*
  ==============================================================================

    ADSR_Sliders.cpp
    Created: 21 Dec 2022 11:38:34am
    Author:  camro

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSR_Sliders.h"

//==============================================================================
ADSR_Sliders::ADSR_Sliders(FirstSamplerAudioProcessor& p)
    : audioProcessor(p)
{
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

}

ADSR_Sliders::~ADSR_Sliders()
{
}

void ADSR_Sliders::paint (juce::Graphics& g)
{
  

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background


    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    /*
    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("ADSR_Sliders", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
                */
}

void ADSR_Sliders::resized()
{
    auto r = getBounds(); 

    mAttackSlider.setBounds(r.removeFromLeft(r.getWidth() / 4));
    mDecaySlider.setBounds(r.removeFromLeft(r.getWidth() / 3));
    mSustainSlider.setBounds(r.removeFromLeft(r.getWidth() / 2));
    mReleaseSlider.setBounds(r.removeFromLeft(r.getWidth()));
}
