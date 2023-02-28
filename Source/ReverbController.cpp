/*
  ==============================================================================

    CustomDeckControl.cpp
    Created: 13 Jan 2023 1:48:58am
    Author:  hamza ironside

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ReverbController.h"

//==============================================================================
ReverbController::ReverbController(const std::string& buttonName)
{
    buttonLabel = buttonName;
}

ReverbController::~ReverbController()
{
}

void ReverbController::paintButton(Graphics& g,
                                    bool shouldDrawButtonAsHighlighted,
                                    bool shouldDrawButtonAsDown)
{
    // Define a radius for our component, which is round
    float radius = (getHeight() - 10) / 2;

    // Color the button component differently based on state
    if (shouldDrawButtonAsDown)
    {
        g.setColour(juce::Colours::white);
    }
    else if (shouldDrawButtonAsHighlighted)
    {
        g.setColour(juce::Colours::pink);
    }
    else if (toggle)
    {
        g.setColour(juce::Colours::orange);
    }
    else
    {
        g.setColour(juce::Colours::red);
    }

    // Draw the button using the radius defined above and add the label
    g.fillEllipse(getWidth() / 2 - radius, getHeight() / 2 - radius, 2 * radius, 2 * radius);
    g.setColour(juce::Colours::white);
    g.setFont(10.0f);
    g.drawText(buttonLabel, getLocalBounds(),
               juce::Justification::centred, true);     // draw some placeholder text
}

void ReverbController::resized()
{
}
