/*
  ==============================================================================

    Deck.cpp
    Created: 12 Jan 2023 12:09:14am
    Author:  hamza ironside

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Deck.h"
#include "OutputProcessor.h"


//==============================================================================
Deck::Deck(AudioPlayer* _player,
           AudioFormatManager& formatManagerToUse,
                           AudioThumbnailCache& cacheToUse
           ): player(_player),
              waveformDisplay(formatManagerToUse, cacheToUse)
{

//    setLookAndFeel (&fusionLookV1);
    setLookAndFeel(&fusionLookV3);
    
    volSlider.setSliderStyle (Slider::Rotary);
    volSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 0, 0);
    
//    volSlider.setLookAndFeel(&fusionLookV1);

    volLabel.attachToComponent(&volSlider, true);
    
    speedSlider.setSliderStyle (Slider::Rotary);
    speedSlider.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    
    // buttons
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(reverbButton);
    addAndMakeVisible(toogle);
    
    
    addAndMakeVisible(waveformDisplay);
       
    // sliders
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    
//    volSlider.setRange(0.0, 1.0);
//    speedSlider.setRange(0.0, 100.0);
//    posSlider.setRange(0.0, 1.0);
    
    // Set suitable ranges for the sliders
    // Volume: From 0% to 100%
    // Speed: From 0.5x to 2x speed
    // Position: From 0 % to 100 %
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.5, 2.0);
    posSlider.setRange(0.0, 1.0);
    
    
    // listeners
        // button listener
        playButton.addListener(this);
        stopButton.addListener(this);
        loadButton.addListener(this);
        // slider listener
        volSlider.addListener(this);
        speedSlider.addListener(this);
        posSlider.addListener(this);
    
    // Start a timer so that timerCallback() will be called every 500ms.
    startTimer(500);
}

Deck::~Deck()
{
    stopTimer();
}

void Deck::paint (juce::Graphics& g)
{}

void Deck::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    double rowH = getHeight() / 10;
    // buttons
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH * 1.1, getWidth(), rowH);
    
    // sliders
    toogle.setBounds(0, rowH * 2, getWidth(), rowH);
//    reverbButton.setBounds(0, rowH * 2, getWidth(), rowH);
    
    volSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 4, getWidth(), rowH);
    posSlider.setBounds(0, rowH * 5, getWidth(), rowH);

    waveformDisplay.setBounds(0, rowH * 6, getWidth() , rowH * 2);
    
    loadButton.setBounds(0, rowH * 8, getWidth(), rowH);

//    playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::yellowgreen);
//    stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::rebeccapurple);
//    loadButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightseagreen);
    
//    waveformDisplay.setBounds(0, rowH*5, getWidth(), rowH*3);
//    posSlider.setBounds(rowH*2,rowH*4, getWidth(), rowH);
    
//        auto border = 4;

//        auto area = getLocalBounds();

//        auto dialArea = area.removeFromTop (area.getHeight() / 3);

//    volSlider.setBounds (dialArea.removeFromLeft (dialArea.getWidth() / 2).reduced (border));
//    speedSlider.setBounds (dialArea.reduced (border));
}



void Deck::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        player->start();
    }
     if (button == &stopButton)
    {
        player->stop();

    }
    if (button == &loadButton)
    {

        // this does not appear to work in current version of JUCE
        // (6.1) despite appearing in the docs
        // it might a macro that disables it. TBC
        //FileChooser chooser{"Select a file..."};
        // if (chooser.browseForFileToOpen())
        // {
        //     loadURL(URL{chooser.getResult()});
        // }
        //
        // this does work in 6.1 but the syntax is a little funky
        // https://docs.juce.com/master/classFileChooser.html#ac888983e4abdd8401ba7d6124ae64ff3
        // - configure the dialogue
        auto fileChooserFlags =
        FileBrowserComponent::canSelectFiles;
        // - launch out of the main thread
        // - note how we use a lambda function which you've probably
        // not seen before. Please do not worry too much about that.
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            auto chosenFile = chooser.getResult();
            player->loadURL(URL{chosenFile});
            
            waveformDisplay.loadURL(URL{chosenFile});
        });
    }
}

void Deck::sliderValueChanged (Slider *slider)
{
    if (slider == &volSlider && slider->getValue() > 0)
    {
        player->setGain(slider->getValue());
    }

    
    if (slider == &speedSlider && slider->getValue() > 0)
    {
        player->setSpeed(slider->getValue());
    }

    if (slider == &posSlider && slider->getValue() > 0)
    {
        player->setPositionRelative(slider->getValue());
    }

}



bool Deck::isInterestedInFileDrag (const StringArray& files) {
    return true;
};

void Deck::filesDropped (const StringArray& files, int x, int y) {

    
    if (files.size() == 1) {
        player->loadURL(URL{ File{files[0]} });
    }
    
};



void Deck::timerCallback()
{

    // Adjust the playhead of the waverform periodically
    waveformDisplay.setPositionRelative(
        player->getPositionRelative());
}


void Deck::loadURL(const URL& url)
{
    // Load a file path into the player and waverform respectively
    player->loadURL(url);
    waveformDisplay.loadURL(url);
}
