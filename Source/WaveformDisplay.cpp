/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 12 Jan 2023 9:15:50pm
    Author:  hamza ironside

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay( AudioFormatManager& formatManagerToUse,
                                 AudioThumbnailCache& cacheToUse):
                                                                audioThumb(1000, formatManagerToUse, cacheToUse),
                                                               fileLoaded(false),
                                                               position(0)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    audioThumb.addChangeListener(this);

}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::orange);
    
    // Draw a playhead onto the wave form, if a file is loaded
    if (fileLoaded)
    {
        // Draw the wave form
        audioThumb.drawChannel(g,
                               getLocalBounds(),
                               0,
                               audioThumb.getTotalLength(),
                               0,
                               1.0f);
        g.setColour(Colours::lightgreen);

        // Draw the playhead
        g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight());
    }
    else
    // Remind the user to load a track
    {
        g.setFont(20.0f);
        g.drawText("Load a track...", getLocalBounds(),
                   Justification::centred, true);  // draw some placeholder text
    }
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::loadURL(URL audioURL)
{

    // Load a new file into the audio thumbnail
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));

    // Redraw the waveform if a new file is loaded in
    if (fileLoaded)
    {

        repaint();
    }
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster* source)
{
    // Redraw the waveform if the audio thumbnail changes - used to update the playhead
    repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position && pos == pos)
    {
        // Set the position in % where the playhead should be
        position = pos;
        repaint();
    }
}
