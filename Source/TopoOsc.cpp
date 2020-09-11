#include "TopoOsc.h"


void TopoVoice::startNote (int midiNoteNumber, float velocity,
                SynthesiserSound* sound, int /*currentPitchWheelPosition*/)
{
    updateParameters();

    x = params->xPhase * (topoData->width - 1);
    y = params->yPhase * (topoData->height - 1);
    level = velocity * 0.1;
    tailOff = 0.0, tailOn = 0.05;

    yReverse = false;

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
        updateParameters();
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
                    tailOn = 0.05;
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
        tailOn = 0.05;
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

    if (!yReverse) {
        y += yDelta;
    }
    else
    {
        y -= yDelta;
    }

    valueCapX();
    valueCapY();
}

void TopoVoice::valueCapX()
{
    if (x >= std::min( (int)(topoData->width * (params->xScale + params->xPhase)) ,topoData->width))
    {
        int overflow = x - std::min((int)(topoData->width * (params->xScale + params->xPhase)), topoData->width);
        x = (params->xPhase * topoData->width);
    }
}

void TopoVoice::valueCapY()
{
    int maxLegalVal = std::min(topoData->height - 1, int((topoData->height - 1) * (params->yPhase + params->yScale) ));
    int minLegalVal = std::max(0, int((topoData->height - 1) * (params->yPhase)));
    
    if (y < minLegalVal)
    {
        y = minLegalVal;
        yReverse = false;
    }
    else if (y > maxLegalVal)
    {
        y = maxLegalVal;
        yReverse = true;
    }
}

float TopoVoice::getSample()
{
    if (topoData == NULL) return 0.0;

    int xRounded = round(x);
    int yRounded = round(y);

    if (xRounded >= topoData->width) xRounded = floor(params->xPhase * (topoData->width-1));
    if (yRounded >= topoData->height) yRounded = floor(params->yPhase * (topoData->height-1));

    //return topoData->data[xRounded][yRounded];

    int yFloor = floor(y);
    int yCeil = ceil(y);
    float ratio = y - yFloor;
    
    if (yCeil >= topoData->height) yCeil = yFloor;
    
    float yInterp = topoData->data[xRounded][yFloor] *(1.0f - ratio) + topoData->data[xRounded][yCeil] * (ratio);
    if (tailOn < .95)
    {
        tailOn *= 1.01;
        return yInterp*tailOn;
    }
    else return yInterp;

}

float TopoVoice::getParameter(std::string id)
{
    auto x = params->vts->getRawParameterValue(id);
    if (x != NULL)
    {
        return *x;
    }
    else
    {
        return 0.0;
    }
}

void TopoVoice::updateParameters()
{
    params->gain = getParameter("gain");
    params->xScaleMode = (int)getParameter("xScaleRange");
    params->xScale = .1f + getParameter("xScale") * xScaleModes[params->xScaleMode - 1];
    params->xPhase = getParameter("xPhase");
    params->xTuning = -((getParameter("xTuning") * .5f) - 0.25f);
    params->xScaleMode = getParameter("xScaleMode");
    params->yRate = getParameter("yRate");
    params->yScale = getParameter("yScale");
    params->yPhase = getParameter("yPhase");
}