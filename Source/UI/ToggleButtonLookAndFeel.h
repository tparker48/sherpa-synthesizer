#pragma once
#include <JuceHeader.h>

class ToggleButtonLookAndFeel : public LookAndFeel_V4
{
public:
    ToggleButtonLookAndFeel(Colour dark, Colour light)
    {
        this->dark = dark;
        this->light = light;
    }

    void setColors(Colour dark, Colour light)
    {
        this->dark = dark;
        this->light = light;
    }

    void drawToggleButton(Graphics& g, ToggleButton& t, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:
    Colour dark, light;
};