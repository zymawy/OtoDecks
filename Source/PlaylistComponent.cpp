/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 12 Jan 2023 11:06:53pm
    Author:  hamza ironside

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include <algorithm>
#include "OutputProcessor.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(Deck *_deckOne, Deck *_deckTwo) : deckOne(_deckOne), deckTwo(_deckTwo)
{
    //Load the Library again
    loadTrack();
    
    // Create the music library table with column headers for track title and length
    // Two additional columns without a title will later display the buttons to add the track to the left and right deck
    tableComponent.getHeader().addColumn("Track Title", 1, 200);
    tableComponent.getHeader().addColumn("Track Length", 2, 100);
    tableComponent.getHeader().addColumn("Deck One", 3, 100);
    tableComponent.getHeader().addColumn("Deck Tow", 4, 100);
    tableComponent.getHeader().addColumn("", 5, 50);
    
    tableComponent.setOutlineThickness(1);
    
    tableComponent.setHeaderHeight (22);
    tableComponent.setRowHeight (20);
    setLookAndFeel(&fusionLookV3);
    
    tableComponent.setLookAndFeel(&fusionLookV3);
    // Make the music library table and search box visible
    addAndMakeVisible(tableComponent);
    tableComponent.setModel(this);

    
    addAndMakeVisible(searchable);
    searchable.addListener(this);
    

    addAndMakeVisible(addButton);
    addButton.addListener(this);
    
    // Register formats with the AudioFormatManager for the purpose of then reading the time length of audio files
    formatManager.registerBasicFormats();
    
    startTimer(550);
}

PlaylistComponent::~PlaylistComponent()
{}

void PlaylistComponent::paint(juce::Graphics &g)
{
    // set default text to show on a search box as well as set color
    searchable.setTextToShowWhenEmpty("Search...(Hint: type more then 2 chart)", Colours::darkgrey);
}


void PlaylistComponent::resized()
{
    double rowHeight = getHeight() / 10;
    
    // Position the table that displays the music library
    tableComponent.setBounds(0, 0, getWidth(), getHeight() * 0.8);

    // Position the search box (title and input field)
    
    searchable.setBounds(0, getHeight() * 0.81, getWidth(), getHeight() * 0.07);
    
    addButton.setBounds(0, rowHeight * 9, getWidth(), rowHeight * 1);
}

int PlaylistComponent::getNumRows()
{
    return trackFileSearch.size();
}

void PlaylistComponent::paintRowBackground(Graphics &g,
                                           int rowNumber,
                                           int width,
                                           int height,
                                           bool rowIsSelected)
{
    auto alternateColour = getLookAndFeel().findColour (ListBox::backgroundColourId)
                                                   .interpolatedWith(getLookAndFeel().findColour (ListBox::textColourId), 0.03f);
    if (rowIsSelected)
    {
        g.fillAll(Colours::orange);
    }
    else
    {
        g.fillAll(alternateColour);
    }
}

void PlaylistComponent::paintCell(Graphics &g,
                                  int rowNumber,
                                  int columnId,
                                  int width,
                                  int height,
                                  bool rowIsSelected)
{
    // Insert the track titles into the first column of the library
    if (columnId == 1)
    {
        g.drawText(trackTitleSearch[rowNumber], 2, 0, width - 4, height,
            juce::Justification::centredLeft, true);
    }

    // Insert the track length into the second column of the library
    if (columnId == 2)
    {
        g.drawText(trackLengthSearch[rowNumber], 2, 0, width - 4, height,
            juce::Justification::centredLeft, true);
    }
}

Component *PlaylistComponent::refreshComponentForCell(int rowNumber,
                                                      int columnId,
                                                      bool isRowSelected,
                                                      Component *existingComponentToUpdate)
{
    // Place deck buttons for the left deck into the third column
    if (columnId == 3)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton *btn = new TextButton{"Left Deck"};
            String id{std::to_string(rowNumber)};
            btn->setComponentID(id);
            btn->setName("Left");
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }

    // Place deck buttons for the right deck into the third column
    if (columnId == 4)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton *btn = new TextButton{"Right Deck"};
            String id{std::to_string(rowNumber)};
            btn->setComponentID(id);
            btn->setName("Right");
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    
    if (columnId == 5) {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new TextButton("Delete");
            String id{ std::to_string(rowNumber * 3 + 2) };
            btn->setComponentID(id);
            btn->setName("Delete");
            btn->addListener(this);
            existingComponentToUpdate = btn;
            btn->setColour(TextButton::buttonColourId, Colour(233, 100, 121));
            btn->setColour(TextButton::textColourOffId, Colour(67, 66, 66));
    
        }
    }
    
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(Button *button)
{
    try {
        
        
        if (button == &addButton) {
            addFileToLibrary();
            tableComponent.updateContent();
            tableComponent.repaint();
        } else {
            // Convert the buttons component ID to an integer, so we can use it as the index of our track titles array
            int id = std::stoi(button->getComponentID().toStdString());
            
            // If the left button was clicked, push the track to the left deck
            if (button->getName() == "Left")
            {
                
                deckOne->loadURL(trackPaths[id]);
                deckOneSelectedTrackId= id;
                OutputProcessor::debug("Left : " +std::to_string(id) + "Chossen : " + std::to_string(deckOneSelectedTrackId));
                
            }
            
            // If the right button was clicked, push the track to the left deck
            if (button->getName() == "Right")
            {
                deckTwo->loadURL(trackPaths[id]);
                deckTwoSelectedTrackId = id;
                OutputProcessor::debug("Right : " +std::to_string(id) + "Chossen : " + std::to_string(deckTwoSelectedTrackId));
                
            }
            
            if (id % 3 == 2 && button->getName() == "Delete")
            {
                OutputProcessor::debug(std::to_string(deckTwoSelectedTrackId) + std::to_string(deckOneSelectedTrackId) +  std::to_string(id));
                
                if (( deckTwoSelectedTrackId == id || deckOneSelectedTrackId == id )) {
                    
                    AlertWindow::showMessageBoxAsync(AlertWindow::AlertIconType::InfoIcon, "You Can't delete A track that on the run!", "Acknowledged");
                    return;
                }
                removeTrack(static_cast<int>(id / 3));
            }
        }
    } catch (const std::exception &e) {
        AlertWindow::showMessageBoxAsync(AlertWindow::AlertIconType::InfoIcon, e.what(), "Acknowledged");
    }
}

bool PlaylistComponent::isInterestedInFileDrag(const StringArray &files) { return true; }

void PlaylistComponent::filesDropped(const StringArray &files, int x, int y)
{
    try {
        
        // Store the music library to a text file on disk so we can retrieve it again
        // Create an output stream
        FileOutputStream libStream(library);
    
    // Iterate over all dropped files and store the track titles and lengths into vectors
    for (String file : files)
    {
        if (!fileExist(file))
        {
            libStream << file << newLine;
             // let's got going and extract our matedata for current track ...
            extractData(file, File{file}, URL{File{file}}, getTrackLength(file));
            tableComponent.updateContent();
            tableComponent.repaint();
        } else {
            OutputProcessor::debugJuce("Play-list Error: "+ file + "Is already added");
            }
    }
    }
catch (const std::exception &e)
    {
            OutputProcessor::debug("Error Dropping files into library");
    }
}

String PlaylistComponent::getLengthOfTrack(String file)
{
    auto duration{0};

    // Calculate the duration of the track by using an AudioFormatReader on the audio file
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(File{file}));
    if (reader.get() != nullptr)
    {
        duration = (float)reader->lengthInSamples / reader->sampleRate;
    }

    // Calculate minutes and seconds
    String minutes = std::to_string(duration / 60);
    String seconds = std::to_string(duration % 60);

    // If the track doesn't have any seconds beyond the full minute, we need to append another 0
    // Otherwise tracks that are e.g. 5 minutes long show up as "5:0" instead of "5:00".
    if (seconds == "0")
    {
        seconds = "00";
    }

    // Return the combined track length in MM:SS format
    return minutes + ":" + seconds;
}

void PlaylistComponent::timerCallback()
{}


void PlaylistComponent::textEditorTextChanged(TextEditor& textEditor)
{
    try
    {
        // lets' get going and clear our old date
        clearData();
        
        String keyword = textEditor.getText();

        for (auto& track : trackFiles)
        {
            if (track.exists())
            {
                File FileFound(track);
                String title = FileFound.getFileName();
                String length = getTrackLength(FileFound);
                URL trackPath = FileFound.getCurrentWorkingDirectory().getFullPathName();

                if (title.containsIgnoreCase(keyword))
                {
                    trackTitleSearch.add(title);
                    trackFileSearch.add(FileFound);
                    trackPathSearch.add(trackPath);
                    trackLengthSearch.add(length);
                }
            }
            tableComponent.updateContent();
            tableComponent.repaint();
        }
    }
    catch (const std::exception &e)
    {
        
        AlertWindow::showMessageBoxAsync(AlertWindow::AlertIconType::InfoIcon, e.what(), "Acknowledged");
    }
}


String PlaylistComponent::getTrackLength(juce::File trackFile)
{
    try
    {
        
        auto duration{0};

        AudioFormatManager formatManager;
        formatManager.registerBasicFormats();
        std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(File{trackFile}));
        if (reader.get() != nullptr)
        {
            duration = (float) reader->lengthInSamples / reader->sampleRate;
        }
        
        String minutes = std::to_string(duration / 60);
        String seconds = std::to_string(duration % 60);
        if (seconds == "0")
        {
            seconds = "00";
        }

        // Return the combined track length in MM:SS format
        return minutes + ":" + seconds;
    }
    catch (const std::exception &e)
    {
        AlertWindow::showMessageBoxAsync(AlertWindow::AlertIconType::InfoIcon,
                                         e.what(), "Acknowledged");
    }

    return "";
}


void PlaylistComponent::removeTrack(int trackId)
{
    try
    {
        URL removeTrack = trackPaths[trackId];

        for (int trackNum = 0; trackNum < trackFiles.size(); ++trackNum)
        {
            if (removeTrack.isLocalFile() && trackFiles[trackNum] == removeTrack.getLocalFile())
            {
                dataRemove(trackNum);
            }
        }
        
        resized();
        tableComponent.resized();

        textEditorTextChanged(searchable);
    }
    catch (const std::exception &e)
    {
        AlertWindow::showMessageBoxAsync(AlertWindow::AlertIconType::InfoIcon, e.what(), "Acknowledged");
    }
}


void PlaylistComponent::dataRemove(int index)
{
    try
    {
        trackFiles.removeAndReturn(index);
        trackPaths.removeAndReturn(index);
        trackTitles.removeAndReturn(index);
        trackLengths.removeAndReturn(index);

        trackTitleSearch.removeAndReturn(index);
        trackFileSearch.removeAndReturn(index);
        trackPathSearch.removeAndReturn(index);
        trackLengthSearch.removeAndReturn(index);
    }
    catch (const std::exception &e)
    {
        AlertWindow::showMessageBoxAsync(AlertWindow::AlertIconType::InfoIcon, e.what(), "Acknowledged");
    }

}



void PlaylistComponent::addFileToLibrary()
{
    
    try
    {
        auto fileChooserFlags =
        FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            auto chosenFile = chooser.getResult();
            String musicName{ chosenFile.getFileNameWithoutExtension() };
            if (!fileExist(musicName))
            {
                extractData(
                           musicName,
                           chosenFile,
                           chosenFile.getCurrentWorkingDirectory().getFullPathName(),
                           getTrackLength(chosenFile)
                           );
                tableComponent.updateContent();
                tableComponent.repaint();
            }
            else {
                    AlertWindow::showMessageBoxAsync(AlertWindow::AlertIconType::InfoIcon,
                                                     "", musicName + " added", "Acknowledged");
            }

        });

    }
    catch (const std::exception &e)
    {
        AlertWindow::showMessageBoxAsync(AlertWindow::AlertIconType::InfoIcon, e.what(), "Acknowledged");
    }
    
}

bool PlaylistComponent::fileExist(String& trackName)
{
    try
    {
        return (std::find(trackTitles.begin(), trackTitles.end(), trackName) != trackTitles.end());
    }
    catch (const std::exception &e)
    {
        AlertWindow::showMessageBoxAsync(AlertWindow::AlertIconType::InfoIcon, e.what(), "Acknowledged");
    }
    
    return false;
}


void PlaylistComponent::extractData(String title,
    File file,
    URL path,
    String length)
{
    try
    {
        String trackName{ file.getFileNameWithoutExtension() };

        trackTitles.add(trackName);
        trackFiles.add(file);
        trackPaths.add(path);
        trackLengths.add(length);

        trackTitleSearch.add(trackName);
        trackFileSearch.add(file);
        trackPathSearch.add(path);
        trackLengthSearch.add(length);
    }
    catch (const std::exception &e)
    {
        AlertWindow::showMessageBoxAsync(AlertWindow::AlertIconType::InfoIcon, e.what(), "Acknowledged");
    }

}


void PlaylistComponent::loadTrack()
{
    
    try
    {
        
        // Load the existing library file, if available
        if (library.existsAsFile())
        {
            FileInputStream libStream(library);
            
            while (!libStream.isExhausted())
            {
                String currentTrack = libStream.readNextLine();
                File file = File{currentTrack};
                OutputProcessor::debugJuce(file.getFullPathName());
                 // let's got going and extract our matedata for current track ...
                extractData(
                            currentTrack,
                            file,
                            URL{file},
                            getTrackLength(file));
                tableComponent.updateContent();
            }
        }
    }
    catch (const std::exception &e)
    {
        AlertWindow::showMessageBoxAsync(AlertWindow::AlertIconType::InfoIcon, e.what(), "Acknowledged");
    }
}


void PlaylistComponent::loadFromLibrary(int buttonId)
{
    

    try
    {
        if (buttonId % 3 == 0) {  // even ID: load to player 1
            deckOne->loadURL(URL{ trackFiles[buttonId / 3] });
        }
        else if (buttonId % 3 == 1) {  // odd ID: load to player 2
            deckTwo->loadURL(URL{ trackFiles[buttonId / 3] });
        }
    }
    catch (int& e)
    {
        AlertWindow::showMessageBoxAsync(AlertWindow::AlertIconType::InfoIcon,  "Loading into Decks Error: Number ", "Acknowledged");
    }
    
}


void PlaylistComponent::clearData() {
    
    trackTitleSearch.clear();
    trackFileSearch.clear();
    trackPathSearch.clear();
    trackLengthSearch.clear();
    
}
