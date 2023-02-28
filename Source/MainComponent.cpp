/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainComponent::MainComponent()
{
    setSize (800, 600);
    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }  
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
    
    addAndMakeVisible(deckOne);
    addAndMakeVisible(deckTwo);
    
    addAndMakeVisible(playlistComponent);
    
    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
    
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    
    // decks for the playback
    playerOne.prepareToPlay(samplesPerBlockExpected, sampleRate);
    playerTwo.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    
    //mixer for the playback
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    //Parallel
    mixerSource.addInputSource(&playerOne, false);
    mixerSource.addInputSource(&playerTwo, false);

 }
void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    // audio blocks for the mixer
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.
    playerOne.releaseResources();
    playerTwo.releaseResources();
    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll(Colour(33, 146, 255));
}

void MainComponent::resized()
{
    
    deckOne.setBounds(0, 0, getWidth() / 2, getHeight() / 2);
    deckTwo.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight() / 2);
    playlistComponent.setBounds(0, getHeight() / 2, getWidth(), getHeight() / 2);
}
