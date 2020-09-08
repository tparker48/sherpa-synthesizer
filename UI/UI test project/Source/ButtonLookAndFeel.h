#pragma once
#include <JuceHeader.h>

class ButtonLookAndFeel : public LookAndFeel_V4
{
public:
    ButtonLookAndFeel(Colour dark, Colour light)
    {
        this->dark = dark;
        this->light = light;

        //this->setColour(Slider::ColourIds::textBoxOutlineColourId, Colour());
    }

    void drawTickBox(Graphics& g, Component& c, float x, float y, float w, float h, bool ticked, bool isEnabled, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    void drawToggleButton(Graphics& g, ToggleButton& t, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:
    Colour dark, light;
};