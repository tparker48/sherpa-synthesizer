/*
  ==============================================================================

    SliderLookAndFeel.cpp
    Created: 6 Sep 2020 10:05:30pm
    Author:  Tom

  ==============================================================================
*/

#include "SliderLookAndFeel.h"

void SliderLookAndFeel::drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle, Slider&)
{
    

    int barWidth = width / 6;
    int barOffset = width / 2 - barWidth / 2;

    int handleWidth = width;
    int handleHeight = barWidth * 1.5;
    
    int handleStreakWidth = .96 * handleWidth;
    int handleStreakHeight = .25 * handleHeight;

    int handleY = (height - handleHeight + 1) * ((sliderPos) / maxSliderPos);
    int handleStreakY = handleY + (handleHeight / 2) - handleStreakHeight / 2;
    int handleStreakX = (handleWidth - handleStreakWidth) / 2;

    // bar
    g.setColour(dark);
    g.fillRect(x + barOffset, y, barWidth, height);

    // handle
    g.fillRect(x, handleY, width, handleHeight);

    g.setColour(light);
    g.fillRect(x + handleStreakX, handleStreakY, handleStreakWidth, handleStreakHeight);
}



