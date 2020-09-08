#include "TopoOsc.h"


/**
 This is where we set up all the parameters needed when a note is pressed.
 */
void TopoVoice::startNote (int midiNoteNumber, float velocity,
                SynthesiserSound* sound, int /*currentPitchWheelPosition*/)
{
    x = params->xPhase * (topoData->width - 1);
    y = params->yPhase * (topoData->height - 1);
    level = velocity * 0.1;
    tailOff = 0.0;

    noteHz = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    sampleRate = (float)getSampleRate();
    updateDeltas();
}

void TopoVoice::stopNote(float /*velocity*/, bool allowTailOff)
{
    if (allowTailOff)
    {
        if (tailOff == 0.0)
            tailOff = 1.0;
    }
    else
    {
        clearCurrentNote();
        xDelta = 0.0;
        x = params->xPhase * (topoData->width - 1);
        y = params->yPhase * (topoData->height - 1);
    }
}

void TopoVoice::renderNextBlock(AudioBuffer<float>& outputBuffer,
    int startSample, int numSamples)
{
    if (xDelta != 0.0)
    {
        checkSourceSwitch();
        updateDeltas();
        if (tailOff > 0.0)
        {
            while (--numSamples >= 0)
            {
                auto currentSample = getSample() * level * params->gain * tailOff;

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, currentSample);

                incrementPhase();
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
                auto currentSample = getSample() * level * params->gain;

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, currentSample);

                incrementPhase();         
                ++startSample;
            }
        }
    }
}

void TopoVoice::checkSourceSwitch()
{
    if (topoData != *topoDataSelection)
    {
        topoData = *topoDataSelection;
        x = 0;
        y = 0;
    }
}

void TopoVoice::updateDeltas()
{
    float hz = this->noteHz * (1.0 - params->xTuning);
    xDelta = (params->xScale * topoData->width) * hz / sampleRate;
    yDelta = params->yRate * (params->yScale / sampleRate);
}

void TopoVoice::incrementPhase()
{
    x += xDelta;
    y += yDelta;
    valueCapX();
    valueCapY();
}

void TopoVoice::valueCapX()
{
    if (x >= std::min( (int)(topoData->width * (params->xScale + params->xPhase)) ,topoData->width))
    {
        int overflow = x - std::min((int)(topoData->width * (params->xScale + params->xPhase)), topoData->width);
        x = (params->xPhase * topoData->width) + overflow;
    }
}

void TopoVoice::valueCapY()
{
    int maxLegalVal = std::min((int)(topoData->height * (params->yScale + params->yPhase)), topoData->height);
    int overflow = y - maxLegalVal;

    if (overflow > 0)
    {
        y = (params->yPhase * topoData->height) + overflow;
    }
}

float TopoVoice::getSample()
{
    if (topoData == NULL) return 0.0;

    int xRounded = round(x);
    int yRounded = round(y);

    if (xRounded >= topoData->width) xRounded = floor(params->xPhase * (topoData->width-1));
    if (yRounded >= topoData->height) yRounded = floor(params->yPhase * (topoData->height-1));

    return topoData->data[xRounded][yRounded];

    //float interpolatedValue;
    //float base, up, right, upRight;
    //
    //int yFloor = floor(y), yCeil = ceil(y);
    //int xFloor = floor(x), xCeil = ceil(x);
    //
    //float xRatioRight   = x - xFloor;
    //float xRatioLeft    = 1.0 - xRatioRight;
    //float yRatioTop     = y - yFloor;
    //float yRatioBottom  = 1.0 - yRatioTop;
    //
    //if (xCeil >= topoData->width) xCeil = floor(params->xPhase * (topoData->width-1));
    //if (yCeil >= topoData->height) yCeil = floor(params->yPhase * (topoData->height-1));
    //
    //base    = topoData->data[xFloor][yFloor];
    //up      = topoData->data[xFloor][yCeil];
    //right   = topoData->data[xCeil][yFloor];
    //upRight = topoData->data[xCeil][yCeil];
    //
    //interpolatedValue  = xRatioLeft * yRatioBottom * base;
    //interpolatedValue += xRatioLeft * yRatioTop * up;
    //interpolatedValue += xRatioRight * yRatioBottom * right;
    //interpolatedValue += xRatioRight * yRatioTop * upRight;
    //
    //return interpolatedValue;
}