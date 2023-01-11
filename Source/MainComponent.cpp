/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "OutputProcessor.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
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

    // buttons
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
       
    // sliders
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    
    // listeners
        // button listener
        playButton.addListener(this);
        stopButton.addListener(this);
        loadButton.addListener(this);
        // slider listener
        volSlider.addListener(this);
        speedSlider.addListener(this);
        posSlider.addListener(this);

    volSlider.setRange(0.0, 1.0);
    posSlider.setRange(0.0, 1.0);



    
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    playerOne.prepareToPlay(samplesPerBlockExpected, sampleRate);
 }
void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    //transportSource.getNextAudioBlock(bufferToFill);
//    resampleSource.getNextAudioBlock(bufferToFill);
    playerOne.getNextAudioBlock(bufferToFill);
}

// void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
// {
//     auto* leftChan = bufferToFill.buffer->getWritePointer(0, 
//                                                          bufferToFill.startSample);
//     auto* rightChan = bufferToFill.buffer->getWritePointer(0, 
//                                                          bufferToFill.startSample);

//     for (auto i=0; i < bufferToFill.numSamples ; ++i)
//     {
//         //double sample = rand.nextDouble() * 0.25;
//         //double sample = fmod(phase, 0.2);
//         double sample = sin(phase) * 0.1;

//         leftChan[i] = sample;
//         rightChan[i] = sample;

//         phase += dphase;
        
//     }                                                    
//     //bufferToFill.clearActiveBufferRegion();
// }

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
//    transportSource.releaseResources();
    playerOne.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    double rowH = getHeight() / 6;
    // buttons
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    
    // sliders
    volSlider.setBounds(0, rowH * 2, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    posSlider.setBounds(0, rowH * 4, getWidth(), rowH);

    loadButton.setBounds(0, rowH * 5, getWidth(), rowH);

}

void MainComponent::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        OutputProcessor::info("Play button was clicked ");
        playerOne.start();
    }
     if (button == &stopButton)
    {
        OutputProcessor::info("Stop button was clicked ");
        playerOne.stop();

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
//            loadURL(URL{chosenFile});
            playerOne.loadURL(URL{chosenFile});
        });
    }
}

void MainComponent::sliderValueChanged (Slider *slider)
{
    if (slider == &volSlider)
    {
        playerOne.setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        playerOne.setSpeed(slider->getValue());
    }

    
    if (slider == &posSlider)
    {
        playerOne.setPositionRelative(slider->getValue());
    }

}
