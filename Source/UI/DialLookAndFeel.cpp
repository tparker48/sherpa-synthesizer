/*
  ==============================================================================

    DialLookAndFeel.cpp
    Created: 6 Sep 2020 11:44:05pm
    Author:  Tom

  ==============================================================================
*/

#include "DialLookAndFeel.h"


void DialLookAndFeel::drawLinearSlider(Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const Slider::SliderStyle, Slider&)
{

    // dial
    g.setColour(dark);
    g.fillEllipse(x, y, width, height);

    // marker
    float originX = x + width / 2.0;
    float originY = y + height / 2.0;
    float radius = (width / 2.0);
    float markerRadius = radius / 5.0;

    float rotationPercentage = sliderPos / maxSliderPos;
    float rotation = minRotation + rotationPercentage * (maxRotation - minRotation);

    float markerX = (radius*.75) * -cos(rotation);
    float markerY = (radius*.75) * -sin(rotation);

    g.setColour(light);
    g.fillEllipse(originX +markerX - markerRadius/2, originY + markerY - markerRadius/2, markerRadius, markerRadius);

}