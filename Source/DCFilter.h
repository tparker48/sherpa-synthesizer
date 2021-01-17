/*
 adapted from https://www.dsprelated.com/freebooks/filters/DC_Blocker.html and https://www.musicdsp.org/en/latest/Filters/135-dc-filter.html 
*/

#pragma once
#include <JuceHeader.h>

class DCFilter
{
public:
    void init(float sampleRate);

    void processBlock(AudioBuffer<float>& buffer, int channel);

private:

    float R, ym1, xm1;

    float processSample(float x);
};