/*
  ==============================================================================

    AudioPlayer.h
    Created: 11 Jan 2023 10:38:51pm
    Author:  hamza ironside

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class AudioPlayer : public AudioSource {
public:
    AudioPlayer(AudioFormatManager& _formatManager);
    ~AudioPlayer();
    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    
    void loadURL(URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    
    /** Set the position of playback to a relative (%) time value
     * (e.g., set it to 45% of the track's total length)
     * @param {double} posInSecs - The percentage value of the track length to which the playhead should be set
    */
    void setPositionRelative(double pos);

    /** Get the relative position of the playhead */
    double getPositionRelative();

    /** Start playback */
    void start();

    /** Stop playback */
    void stop();

    /** Apply the reverb effect */
    void toggleReverb();
    
private:
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{&transportSource, false, 2};
    
    /**
     * @var {bool} - tracks the state of whether reverb should be applied or not
    */
    bool reverb{false};
    ReverbAudioSource reverbSource{&resampleSource, false};
    
};
