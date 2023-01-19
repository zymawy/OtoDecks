/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioPlayer.h"
#include "Deck.h"
#include "PlaylistComponent.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    
    /**
     * @member - the AudioFormatManager that provides and manages audio formats
     */
    AudioFormatManager formatManager;

    /**
     * @member - the AudioThumbnailCache used for the wave form display
     */
    AudioThumbnailCache thumbCache{100};
    
    AudioPlayer playerOne{formatManager};
    
    Deck deckOne{&playerOne,formatManager, thumbCache};
    
    AudioPlayer playerTwo{formatManager};
    
    Deck deckTwo{&playerTwo,formatManager, thumbCache};
    
    MixerAudioSource mixerSource;

    /**
     * @member - The music library
     */
    PlaylistComponent playlistComponent{&deckOne, &deckTwo};


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
