/*
  ==============================================================================

    SliderLookAndFeel.h
    Created: 6 Sep 2020 5:39:10pm
    Author:  Tom

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SliderLookAndFeel: public juce::LookAndFeel_V4 {

public:
    SliderLookAndFeel(Colour dark, Colour light)
    {
        this->dark = dark;
        this->light = light;

        this->setColour(Slider::ColourIds::textBoxOutlineColourId, Colour());
    }

    void setColors(Colour dark, Colour light)
    {
        this->dark = dark;
        this->light = light;
    }

    void drawLinearSlider(Graphics&, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const Slider::SliderStyle, Slider&) override;

private:
    Colour dark, light;

    const int sliderBarWidth = 75;
    const int sliderHandleHeight = 100, sliderHandleWidth = 300;
};
