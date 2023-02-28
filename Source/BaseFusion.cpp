/*
  ==============================================================================

    BaseFusion.cpp
    Created: 23 Feb 2023 1:00:30am
    Author:  hamza ironside

  ==============================================================================
*/

#include "BaseFusion.h"
#include <JuceHeader.h>

BaseFusion::BaseFusion() {
    setOwnColours();
}


void BaseFusion::setOwnColours() {
    Font generalFont("Operator Mono Lig", "Light Italic", 20.9f);
    
    
    // let's got going and add our beatiful fonts
    
    LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName ("Operator Mono Lig");
    
}

