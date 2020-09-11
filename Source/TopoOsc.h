// stand in sine wave oscillator from FM group
#pragma once

#include <algorithm>
#include "../JuceLibraryCode/JuceHeader.h"
#include "TopoDataLoader.h"
#include "TopoOscParameters.h"

struct TopoSound : public SynthesiserSound
{

    TopoSound() {}

    bool appliesToNote(int) override { return true; }
    bool appliesToChannel(int) override { return true; }

};

class TopoVoice : public SynthesiserVoice
{
public:

    TopoVoice() { topoData = NULL; params = NULL; }
    TopoVoice(TopoData** topoData, TopoOscParameters* topoParams) 
    { 
        this->topoDataSelection = topoData;
        this->topoData = *topoDataSelection;
        params = topoParams;
    }

    bool canPlaySound(SynthesiserSound* sound) override
    {
        return dynamic_cast<TopoSound*> (sound) != nullptr;
    }

    void startNote(int midiNoteNumber, float velocity,
        SynthesiserSound* sound, int /*currentPitchWheelPosition*/) override;

    void stopNote(float /*velocity*/, bool allowTailOff) override;

    void pitchWheelMoved(int) override {}
    void controllerMoved(int, int) override {}

    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

private:
    TopoData** topoDataSelection;
    TopoData* topoData;
    TopoOscParameters* params;
    
    void checkSourceSwitch();
    void updateDeltas();
    void incrementPhase();
    void valueCapX(); // call after you increment x to avoid overflows
    void valueCapY(); // call after you increment y to avoid overflows
    float getSample();
    float getParameter(std::string id);
    void updateParameters();


    float noteHz, sampleRate;

    float level = 1.0, tailOff = 0.0, tailOn = 0.0;
    float x = 0.0, xDelta = 0.0;
    float y = 0.0, yDelta = 0.0;

    float xScaleModes[3] = { 0.1f, 0.25f, .5f };

    bool yReverse;
};
