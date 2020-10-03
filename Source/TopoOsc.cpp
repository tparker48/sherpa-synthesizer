#include "TopoOsc.h"


void TopoVoice::startNote (int midiNoteNumber, float velocity,
                SynthesiserSound* sound, int /*currentPitchWheelPosition*/)
{
    updateParameters();

    x = params->xPhase * (topoData->width - 1.0);
    y = params->yPhase * (topoData->height - 1.0);
    level = velocity * 0.1;
    tailOff = 0.0;
    tailOn = 0.05;

    yReverse = false;

    noteHz = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    sampleRate = getSampleRate();
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
        x = params->xPhase * (topoData->width - 1.0);
        y = params->yPhase * (topoData->height - 1.0);
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
    double hz = this->noteHz *(1.0 - params->xTuning);
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
    int maxLegal = std::min((int)((topoData->width - 1) * (params->xScale + params->xPhase)), topoData->width - 1);
    if (x > maxLegal)
    {
        int minLegal = (topoData->width - 1) * params->xPhase;
        int window = maxLegal - minLegal;
        x = minLegal + int(((int(round(x)) - minLegal) % window));
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

    //int xRounded = round(x);
    //int yRounded = round(y);
    //
    //if (xRounded >= topoData->width) xRounded = floor(params->xPhase * (topoData->width-1.0));
    //if (yRounded >= topoData->height) yRounded = floor(params->yPhase * (topoData->height-1.0));

    //return topoData->data[xRounded][yRounded];

    int xFloor = floor(x);
    int xCeil = ceil(x);
    double xRatio = x - xFloor;

    int yFloor = floor(y);
    int yCeil = ceil(y);
    double yRatio = y - yFloor;
    
    if (yCeil >= topoData->height) yCeil = yFloor;
    
    double interp = (1.0 - xRatio) * (topoData->data[xFloor][yFloor] * (1.0 - yRatio) + topoData->data[xFloor][yCeil] * (yRatio))
                        + (xRatio) * (topoData->data[xCeil][yFloor] * (1.0 - yRatio) + topoData->data[xCeil][yCeil] * (yRatio));
    if (tailOn < .95)
    {
        tailOn *= 1.01;
        return interp*tailOn;
    }
    else return interp;

}

double TopoVoice::getParameter(std::string id)
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
    params->xScale = .1 + getParameter("xScale") * xScaleModes[params->xScaleMode - 1];
    params->xPhase = getParameter("xPhase");
    params->xTuning = -((getParameter("xTuning") * .25f) - 0.125f);
    params->xScaleMode = getParameter("xScaleMode");
    params->yRate = getParameter("yRate");
    params->yScale = getParameter("yScale");
    params->yPhase = getParameter("yPhase");
}
