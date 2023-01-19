/*
  ==============================================================================

    AudioPlayer.cpp
    Created: 11 Jan 2023 10:38:51pm
    Author:  hamza ironside

  ==============================================================================
*/

#include "AudioPlayer.h"
#include "OutputProcessor.h"

AudioPlayer::AudioPlayer(AudioFormatManager& _formatManager)
: formatManager(_formatManager)
{


}

AudioPlayer::~AudioPlayer() {};

void AudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate) {

    transportSource.prepareToPlay(
        samplesPerBlockExpected,
        sampleRate);
    resampleSource.prepareToPlay(
        samplesPerBlockExpected,
        sampleRate);
    reverbSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
};
void AudioPlayer::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) {
    // Switch to the reverb source if reverb is active
        if (reverb == true)
        {
            reverbSource.getNextAudioBlock(bufferToFill);
        }
        // Otherwise use the regular resample source
        else
        {
            resampleSource.getNextAudioBlock(bufferToFill);
        }
//    resampleSource.getNextAudioBlock(bufferToFill);
};
void AudioPlayer::releaseResources() {
    transportSource.releaseResources();
    resampleSource.releaseResources();
    reverbSource.releaseResources();
};

void AudioPlayer::loadURL(URL audioURL) {
    
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader,
true));
        transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset (newSource.release());
    }
    
};

void AudioPlayer::setGain(double gain) {
    if (gain < 0 || gain > 1.0) {
        OutputProcessor::info("Gain Is Not a Valid Value : " + std::to_string(gain));
    } else {
        transportSource.setGain(gain);
    }
};
void AudioPlayer::setSpeed(double ratio) {
    if (ratio < 0 || ratio > 100.0) {
        OutputProcessor::info("speed Is Not a Valid Value : " + std::to_string(ratio));
    } else {
        resampleSource.setResamplingRatio(ratio);
    }
};
void AudioPlayer::setPosition(double posInSecs) {
    transportSource.setPosition(posInSecs);
};

void AudioPlayer::setPositionRelative(double pos) {
    if (pos < 0 || pos > 1.0) {
        OutputProcessor::info("setPositionRelative Is Not a Valid Value : " + std::to_string(pos));
    } else {
        setPosition(transportSource.getLengthInSeconds() * pos);
    }
};



void AudioPlayer::start() {
    transportSource.start();
};

void AudioPlayer::stop() {
    transportSource.stop();
};



double AudioPlayer::getPositionRelative()
{
    // Calculate the % of the track played at the current time stamp
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}



void AudioPlayer::toggleReverb()
{
    // Toggle the reverb state between true and false
    reverb = !reverb;
}

