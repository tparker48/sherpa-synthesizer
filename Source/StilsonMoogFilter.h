/*
The following class was created by me based on the code here:
https://www.musicdsp.org/en/latest/Filters/145-stilson-s-moog-filter-code.html

Which was based on the work of Tim Stilson
*/


#pragma once
#include <JuceHeader.h>

#define LOWPASS 1
#define BANDPASS 2
#define HIGHPASS 3

class StilsonMoogFilter
{
public:
    void init(float sampleRate);

    void setCutoff(float cutoff);
    void setResonance(float resonance);
    void setSaturationAmount(float saturationAmount);

    void processBlock(AudioBuffer<float>& buffer, int channel , int passMode);

private:
    float saturate(float input);
    float interpolate(float ratio, float a, float b);

    float sampleRate;
    float state[4];
    float output;

    float Q,p;
    float saturationAmount;

    const float saturationLimit = 0.95;
};