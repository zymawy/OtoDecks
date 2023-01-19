/*
  ==============================================================================

    WaveformDisplay.h
    Created: 12 Jan 2023 9:15:50pm
    Author:  hamza ironside

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
                         public ChangeListener
{
public:
    WaveformDisplay( AudioFormatManager& formatManagerToUse,
                    AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    /**
     * Update the playhead when the audio thumbnail changes
     * @param {ChangeBroadcaster} source - any object that gets a listener attached can be passed in. In our case it's the Audio Thumbnail.
    */
    void changeListenerCallback(ChangeBroadcaster *source) override;

    /**
     * Load a file path into the audio player. This is used when files are dropped onto the Ddeck directly.
    * @param {URL} url - A file path to an audio file to load
     */
    void loadURL(URL audioURL);

    /** Set the position of playback to a relative (%) time value
     * (e.g., set it to 45% of the track's total length)
     * @param {double} posInSecs - The percentage value of the track length to which the playhead should be set
    */
    void setPositionRelative(double pos);

private:
    
    /**
    * @member - The audio thumbnail used to draw the wave form
    */
    AudioThumbnail audioThumb;

    /**
     * @var - tracks if a file has been loaded into the wave form or not
    */
    bool fileLoaded;

    /**
     * @var - track the position of the playhead
    */
    double position;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
