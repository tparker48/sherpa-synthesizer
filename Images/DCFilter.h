/*
  ==============================================================================

    DCBiasCorrection.h
    Created: 16 Jan 2021 3:32:21pm
    Author:  Tom

  ==============================================================================
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