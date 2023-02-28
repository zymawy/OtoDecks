/*
  ==============================================================================

    FustionV3.h
    Created: 20 Jan 2023 5:56:03am
    Author:  hamza ironside

  ==============================================================================
*/

#pragma once
#include "BaseFusion.h"

class FusionLookV3 : public LookAndFeel_V3,
                     public BaseFusion
{
public:
    FusionLookV3() {        
        setColour(Slider::rotarySliderOutlineColourId, Colour(43, 46, 74));
        setColour(Slider::rotarySliderFillColourId, Colours::blanchedalmond);
        setColour(Slider::rotarySliderFillColourId, Colour(144, 55, 73));
        
        setColour(TextButton::buttonColourId, Colour(232, 69, 69));
        setColour(TextButton::buttonOnColourId, Colour(83, 53, 74));
        setColour(TextButton::textColourOnId, Colour(233, 232, 232));
        setColour(TextButton::textColourOffId, Colour(233, 232, 232));
        
        setColour(ToggleButton::ColourIds::textColourId, Colours::red);
        setColour(ToggleButton::ColourIds::tickColourId, Colours::orange);
        setColour(ToggleButton::ColourIds::tickDisabledColourId, Colours::orangered);
        setColour(ListBox::backgroundColourId, Colour(33, 146, 255));
        setColour(ListBox::outlineColourId, Colour(144, 55, 73));
        setColour(ListBox::textColourId, Colour(233, 232, 232));
            
        setColour(TableHeaderComponent::highlightColourId, Colour(233, 232, 232));
        setColour(TableHeaderComponent::outlineColourId, Colour(233, 232, 232));
        
        setColour(TableHeaderComponent::backgroundColourId, Colour(232, 69, 69));
        setColour(TableHeaderComponent::textColourId, Colour(83, 53, 74));
        DBG(("V3 selected"));
    }
};
