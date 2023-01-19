/*
  ==============================================================================

    Deck.h
    Created: 12 Jan 2023 12:09:14am
    Author:  hamza ironside

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AudioPlayer.h"
#include "WaveformDisplay.h"
#include "CustomDeckControl.h"

//==============================================================================
/*
*/
class Deck  : public juce::Component,
              public Button::Listener,
              public Slider::Listener,
              public FileDragAndDropTarget,
              public Timer
{
public:
    Deck(AudioPlayer* player,
         AudioFormatManager &formatManagerToUse,
         AudioThumbnailCache &cacheToUse);
    ~Deck() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /** implement Button::Listener */
    void buttonClicked (Button *) override;

    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;
    
    bool isInterestedInFileDrag (const StringArray& files) override;

    void filesDropped (const StringArray& files, int x, int y) override;
    
    
    /**
     * Periodically update the wave form display with the current playhead position
     */
    void timerCallback() override;
    
    
    /**
     * Load a file path into the audio player. This is used when files are dropped onto the Ddeck directly.
    * @param {URL} url - A file path to an audio file to load
     */
    void loadURL(const URL &url);

private:
    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    
    CustomDeckControl reverbButton{"REVERB"};
  
    Slider volSlider;
    Slider speedSlider;
    Slider posSlider;
    
    AudioPlayer* player;
    
    WaveformDisplay waveformDisplay;
    
    // https://docs.juce.com/master/classFileChooser.html#ac888983e4abdd8401ba7d6124ae64ff3

    juce::FileChooser fChooser{"Select a file..."};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Deck)
};
