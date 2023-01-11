/*
  ==============================================================================

    Logger.cpp
    Created: 11 Jan 2023 11:16:02pm
    Author:  hamza ironside

  ==============================================================================
*/

#include "OutputProcessor.h"

#include <iostream>
#include <sstream>
#include <vector>


OutputProcessor::OutputProcessor() {}


void OutputProcessor::print(std::string taxt, std::string by) {
    std::cout << by << taxt << std::endl;
}


void OutputProcessor::debug(std::string taxt) {
    print(taxt, "debug🐛> ");
}

void OutputProcessor::info(std::string taxt, std::string icon) {
//    std::cout.width(50);

    print(taxt, "Logger: " + icon + "> ");
}


void OutputProcessor::exception(std::string taxt) {
    print(taxt, "exception🚨> ");
}



std::string OutputProcessor::repeat(int n, std::string repeat) {

    std::ostringstream os;
    for (int i = 0; i < n; i++)
        os << repeat;


    return os.str();
}

bool OutputProcessor::is_number(const std::string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}
