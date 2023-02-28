/*
  ==============================================================================

    FustionV4.h
    Created: 20 Jan 2023 5:56:31am
    Author:  hamza ironside

  ==============================================================================
*/

#pragma once
#include "BaseFusion.h"

class FusionLookV4 : public LookAndFeel_V4,
                     public BaseFusion
{
public:
    FusionLookV4() {
        Font generalFont("Operator Mono Lig", "Light Italic", 20.9f);
//        setFont(generalFont);
        
//        setColour(Slider::rotarySliderOutlineColourId, Colours::chocolate);
//        setColour(Slider::rotarySliderFillColourId, Colours::blanchedalmond);
//        setColour(Slider::rotarySliderFillColourId, juce::Colours::red);
//
//        setColour(TextButton::buttonColourId,Colours::blue);
//        setColour(TextButton::buttonOnColourId, Colours::navy);
//
//        setColour(ToggleButton::ColourIds::textColourId, Colours::red);
//        setColour(ToggleButton::ColourIds::tickColourId, Colours::orange);
//        setColour(ToggleButton::ColourIds::tickDisabledColourId, Colours::orangered);
//
//        setColour(TextEditor::backgroundColourId,Colour(255, 255, 255));
//        setColour(TextEditor::textColourId,Colours::darkgrey);
        
        DBG(("V4 selected"));
    }
};
