/*
  ==============================================================================

    PlaylistComponent.h
    Created: 12 Jan 2023 11:06:53pm
    Author:  hamza ironside

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Deck.h"
//==============================================================================
/*
*/
class PlaylistComponent : public Component,
                        public TableListBoxModel,
                        public Button::Listener,
                        public TextEditor::Listener,
                        public Timer,
                        public FileDragAndDropTarget
{
public:
    /**
     * @constructor
     */
    PlaylistComponent(Deck *_deckOne, Deck *_deckTwo);
    ~PlaylistComponent() override;

    void paint(juce::Graphics &) override;
    void resized() override;

    /**
     * Provide JUCE with a way to determine how many rows the music library has
     */
    int getNumRows() override;

    /**
     * Paint the table rows' background, mostly the colour and selected state when clicked
     * @param {Graphics} - the graphics context used to paint the table rows
     * @param {int} rowNumber - the number of the row currently being painted
     * @param {int} width - The width of the rows
     * @param {int} height - The height of the rows
     * @param {bool} rowIsSelected - evaluates to true if the current row being painted has been selected by the user
     * @returns {void} - only results in painted row background
     */
    void paintRowBackground(Graphics &,
                            int rowNumber,
                            int width,
                            int height,
                            bool rowIsSelected) override;

    /**
     * Paint the table cell contents
     * @param {Graphics} - the graphics context used to paint the table rows
     * @param {int} rowNumber - the number of the row currently being painted
     * @param {int} columnId - The column currently being painted, from left to right
     * @param {int} width - Width of the current cell
     * @param {bool} height - Height of the current cell
     * @param {bool} rowIsSelected - Evaluates to true if the current row of this cell is selected
     * @returns {void} - only results in painted cell
     */
    void paintCell(Graphics &,
                   int rowNumber,
                   int columnId,
                   int width,
                   int height,
                   bool rowIsSelected) override;

    /**
     * Update cells with custom components - in our case, buttons to play tracks on the two decks
     * @param {int} rowNumber - the number of the row currently being painted
     * @param {int} columnId - The column currently being painted, from left to right
     * @param {bool} rowIsSelected - Evaluates to true if the current row of this cell is selected
     * @param {Component*} existingComponentToUpdate - A pointer to the component that needs to be updated
     * @returns {void} - only results in painted cell
     */
    Component *refreshComponentForCell(int rowNumber,
                                       int columnId,
                                       bool isRowSelected,
                                       Component *existingComponentToUpdate) override;

    /**
     * Handle button click events
     * @param {Button*} button - A pointer to the button that is firing the event
     * @returns {void} - Results in different procedures executed depending on which button fired the event
     */
    void buttonClicked(Button *button) override;

    /**
     * Define logic for accepting file drops onto the component
     * @param {StringArray&} files - An array of strings, each containing the path to a music file
     * @return {bool} - We've set the entire component to accept file drops, with no restrictions. Always returns true.
     */
    bool isInterestedInFileDrag(const StringArray &files) override;

    /**
     * Capture dropped files
     * @param {StringArray&} files - An array of strings, each containing the path to a music file
     * @param {int} x, y - The position of the file drop
     * @returns {void} - Results in files being available to process
     */
    void filesDropped(const StringArray &files, int x, int y) override;
    
    void timerCallback() override;

    void loadFromLibrary(int identifier);
    
    bool fileExist(String& trackName);
    
    void removeTrack(int trackId);
    
    
    String getTrackLength(File musicFile);
    
    void textEditorTextChanged(TextEditor& textEditor) override;
    
    void dataRemove(int index);
    
    void addFileToLibrary();
    
    void extractData(String title,
        File file,
        URL path,
        String length);
    
    void clearData();
    
    void loadTrack();
    

private:
    TableListBox tableComponent;       // The music library table
    /**
     Get the length of a track in minutes and seconds, in the MM:SS format
     @param {String} file - Path to the file that we want to get the time length of
     @returns {String} - Time length of the audio file in MM:SS format.
    */
    String getLengthOfTrack(String file);

    // This is needed to read the audio files to get their lengt
    AudioFormatManager formatManager;

    // The two decks, their respective GUIs, so the playlist can push tracks to them
    // These are initialised through the constructor
    Deck *deckOne;
    int deckOneSelectedTrackId;
    Deck *deckTwo;
    int deckTwoSelectedTrackId;

    FileChooser fChooser{"Select a file..."};

    Label searchTitle;
    
    TextEditor searchable{ "Search..." };
    
    TextButton addButton{ "ADD" };
    
    
    Array<String> trackTitles;
    Array<File> trackFiles;
    Array<String> trackLengths;
    Array<URL> trackPaths;
    

    Array<String> trackTitleSearch;
    Array<File> trackFileSearch;
    Array<String> trackLengthSearch;
    Array<URL> trackPathSearch;

    // OS-agnostic path to store the music library as a text file on disk
    File library{File::getSpecialLocation(juce::File::userMusicDirectory).getFullPathName() + "/tracks.txt"};
    
    FusionLookV1 fusionLookV1;
    FusionLookV2 fusionLookV2;
    FusionLookV3 fusionLookV3;
    FusionLookV4 fusionLookV4;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
