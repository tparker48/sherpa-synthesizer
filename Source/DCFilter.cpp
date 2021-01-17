/*
  ==============================================================================

    DCBiasCorrection.cpp
    Created: 16 Jan 2021 3:32:21pm
    Author:  Tom

  ==============================================================================
*/

#include "DCFilter.h"


void DCFilter::init(float sampleRate)
{
    R = 1.0f - (190.0f / sampleRate);
    xm1 = 0.0f;
    ym1 = 0.0f;
}
    
void DCFilter::processBlock(AudioBuffer<float>& buffer, int channel)
{
    float input, output;

    int numSamples = buffer.getNumSamples();
    int startSample = 0;

    
    for (int i = 0; i < numSamples; i++) {
		input = buffer.getSample(channel, startSample + i);
        output = processSample(input);
        buffer.setSample(channel, startSample + i, output);
    }
}
    
float DCFilter::processSample(float x)
{
    float y = x - xm1 + R*ym1;
    xm1 = x;
    ym1 = y;
    return y;
}
