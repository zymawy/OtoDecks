/*
  ==============================================================================

    Logger.h
    Created: 11 Jan 2023 11:16:02pm
    Author:  hamza ironside

  ==============================================================================
*/

#pragma once
#include <stdio.h>
#include <fstream>
#include <string>
#include <JuceHeader.h>


class OutputProcessor {
public:
//    A constructor.
    OutputProcessor();

//    A function that prints out the string that is passed to it.
    static void print(std::string test, std::string by = "Logger 👨🏾‍💻> ");

//    A function that prints out the string that is passed to it.
    static void debug(std::string input);
    static void debugJuce(juce::String input);

//    A function that prints out the string that is passed to it.
    static void info(std::string input, std::string icon = "💁🏾‍♂️");

//    Printing out the string that is passed to it.
    static void exception(std::string input);

//    A function that takes a string and a character and returns a vector of strings.
    static std::vector <std::string> explode(std::string const &s, char delim);

//    A function that takes a string and a character and returns a vector of strings.
    static std::string repeat(int n, std::string repeat);

//    Checking if the string is a number.
    static bool is_number(const std::string &s);

};
