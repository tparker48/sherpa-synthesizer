#include "TopoOsc.h"


/**
 This is where we set up all the parameters needed when a note is pressed.
 */
void TopoVoice::startNote (int midiNoteNumber, float velocity,
                SynthesiserSound* sound, int /*currentPitchWheelPosition*/)
{
    x = params->xPhase * (topoData->width - 1);
    y = params->yPhase * (topoData->height - 1);
    level = velocity * 0.15;
    tailOff = 0.0;

    auto xCyclesPerSecond = params->xRate * MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    xDelta = xCyclesPerSecond * (params->xScale / getSampleRate());

    auto yCyclesPerSecond = params->yRate;
    yDelta = yCyclesPerSecond * (params->yScale / getSampleRate()); // watch out, SUPER small number for low yRate
}

/**
 Little decay envelope, SEE MIDI Synth tutorial.
 */
void TopoVoice::stopNote (float /*velocity*/, bool allowTailOff)
{
    if (allowTailOff)
    {
        if (tailOff == 0.0)
            tailOff = 1.0;
    }
    else
    {
        clearCurrentNote();
        x = params->xPhase * (topoData->width - 1);
        y = params->yPhase * (topoData->height - 1);
    }
}

void TopoVoice::renderNextBlock (AudioBuffer<float>& outputBuffer,
                      int startSample, int numSamples)
{
    if (xDelta != 0.0)
    {
        if (tailOff > 0.0)
        {
            while (--numSamples >= 0)
            {
                auto currentSample = getSample() * level * tailOff;
                
                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);
                
                x += xDelta;
                y += yDelta;
                valueCapX();
                valueCapY();
                ++startSample;

                tailOff *= 0.99;

                if (tailOff <= 0.005)
                {
                    clearCurrentNote();

                    xDelta = 0.0;
                    yDelta = 0.0;
                    break;
                }
            }
        }
        else
        {
            while (--numSamples >= 0)
            {
                auto currentSample = getSample() * level;

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);

                x += xDelta;
                y += yDelta;
                valueCapX();
                valueCapY();
                ++startSample;
            }
        }
    }
}

void TopoVoice::valueCapX()
{
    if (x >= topoData->width * (params->xScale + params->xPhase))
    {
        x -= topoData->width * (params->xScale + params->xPhase);
    }
}

void TopoVoice::valueCapY()
{
    if (y >= topoData->height * (params->yScale + params->yPhase))
    {
        y -= topoData->height * (params->yScale + params->yPhase);
    }
}

float TopoVoice::getSample()
{
    //return (random.nextFloat() * 0.25f - 0.125f);
    // x and y are floats, data is indexed by integers
    // calculate weighted average of values nearest to (x,y) 
    if (topoData == NULL) return 0.0;

    float interpolatedValue;
    float base, up, right, upRight;

    int yFloor = floor(y), yCeil = ceil(y);
    int xFloor = floor(x), xCeil = ceil(x);

    float xRatioRight   = x - xFloor;
    float xRatioLeft    = 1.0 - xRatioRight;
    float yRatioTop     = y - yFloor;
    float yRatioBottom  = 1.0 - yRatioTop;

    if (xCeil >= topoData->width) xCeil = floor(params->xPhase * topoData->width);
    if (yCeil >= topoData->height) yCeil = floor(params->yPhase * topoData->height);

    base    = topoData->data[xFloor][yFloor];
    return base;
    up      = topoData->data[xFloor][yCeil];
    right   = topoData->data[xCeil][yFloor];
    upRight = topoData->data[xCeil][yCeil];

    interpolatedValue  = xRatioLeft * yRatioBottom * base;
    interpolatedValue += xRatioLeft * yRatioTop * up;
    interpolatedValue += xRatioRight * yRatioBottom * right;
    interpolatedValue += xRatioRight * yRatioTop * upRight;

    return interpolatedValue;
}