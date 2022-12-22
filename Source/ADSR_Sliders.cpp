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
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colour::fromRGB(246, 133, 84));
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colour::fromRGB(45, 49, 66));
    getLookAndFeel().setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour::fromRGB(65, 69, 86));

    getLookAndFeel().setColour(juce::Slider::textBoxTextColourId, juce::Colour::fromRGB(76, 92, 120));
    getLookAndFeel().setColour(juce::Slider::textBoxOutlineColourId, juce::Colour::fromRGB(223, 225, 228));

    getLookAndFeel().setColour(juce::Label::textColourId, juce::Colour::fromRGB(76, 92, 120));
    
           //attack
    mAttackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(mAttackSlider);

    
    mAttackLabel.setFont(mSliderFont);
    mAttackLabel.setText("Attack", juce::dontSendNotification);
    mAttackLabel.setJustificationType(juce::Justification::centredTop);
    mAttackLabel.attachToComponent(&mAttackSlider, false);

    attackSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "ATTACK", mAttackSlider);

    //Decay
    mDecaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(mDecaySlider);

    mDecayLabel.setFont(mSliderFont);
    mDecayLabel.setText("Decay", juce::dontSendNotification);
    mDecayLabel.setJustificationType(juce::Justification::centredTop);
    mDecayLabel.attachToComponent(&mDecaySlider, false);

    decaySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "DECAY", mDecaySlider);

    //Sustain
    mSustainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(mSustainSlider);

    mSustainLabel.setFont(mSliderFont);
    mSustainLabel.setText("Sustain", juce::dontSendNotification);
    mSustainLabel.setJustificationType(juce::Justification::centredTop);
    mSustainLabel.attachToComponent(&mSustainSlider, false);

    sustainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "SUSTAIN", mSustainSlider);

    //Release
    mReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(mReleaseSlider);

    mReleaseLabel.setFont(mSliderFont);;
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

    /*
    g.setColour (juce::Colours::grey);
    juce::Rectangle<float> window;
    window.setBounds(0, 0, getWidth(), getHeight());
    g.drawRoundedRectangle(window, 5, .5); 
    */
}

void ADSR_Sliders::resized()
{
    auto r = getLocalBounds(); 
    r.removeFromTop(getHeight() / 5);
    mAttackSlider.setBounds(r.removeFromLeft(r.getWidth() / 4));
    mDecaySlider.setBounds(r.removeFromLeft(r.getWidth() / 3));
    mSustainSlider.setBounds(r.removeFromLeft(r.getWidth() / 2));
    mReleaseSlider.setBounds(r.removeFromLeft(r.getWidth()));
}
