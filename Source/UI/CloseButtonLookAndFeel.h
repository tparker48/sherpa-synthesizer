#pragma once
#include <JuceHeader.h>

class CloseButtonLookAndFeel : public LookAndFeel_V4
{
public:
    CloseButtonLookAndFeel(Colour dark, Colour light)
    {
        this->dark = dark;
        this->light = light;
    }

    void drawToggleButton(Graphics& g, ToggleButton& t, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:
    Colour dark, light;
};