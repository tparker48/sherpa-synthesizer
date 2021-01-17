/*
 adapted from https://www.dsprelated.com/freebooks/filters/DC_Blocker.html and https://www.musicdsp.org/en/latest/Filters/135-dc-filter.html
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
