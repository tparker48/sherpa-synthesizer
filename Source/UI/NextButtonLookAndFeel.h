#pragma once
#include <JuceHeader.h>

class NextButtonLookAndFeel : public LookAndFeel_V4
{
public:
    NextButtonLookAndFeel(bool pointingRight, Colour dark, Colour light)
    {
        this->dark = dark;
        this->light = light;
        this->pointingRight = pointingRight;
    }

    void setColors(Colour dark, Colour light)
    {
        this->dark = dark;
        this->light = light;
    }

    void drawToggleButton(Graphics& g, ToggleButton& t, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:
    Colour dark, light;
    bool pointingRight;
};