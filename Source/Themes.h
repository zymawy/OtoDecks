/*
  ==============================================================================

    Themes.h
    Created: 21 Jan 2023 3:30:16pm
    Author:  hamza ironside

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Themes  : public juce::Component
{
public:
    Themes();
    ~Themes() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Themes)
};
