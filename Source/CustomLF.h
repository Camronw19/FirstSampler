/*
  ==============================================================================

    CustomLF.h
    Created: 19 Dec 2022 2:29:33pm
    Author:  camro

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CustomLAF : public juce::LookAndFeel_V4
{
public: 
    CustomLAF()
    {
        setColour(juce::TextButton::textColourOffId, juce::Colour::fromRGB(65, 69, 86));
      
    }

    
    void drawPopupMenuBackground(juce::Graphics& g, int width, int height) override
    {
        g.setColour(juce::Colour::fromRGB(45, 49, 66));
        g.fillAll(); 
    }

}; 