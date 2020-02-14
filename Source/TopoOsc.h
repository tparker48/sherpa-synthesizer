// stand in sine wave oscillator from FM group
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


struct TopoSound : public SynthesiserSound
{

    TopoSound() {}

    bool appliesToNote(int) override { return true; }
    bool appliesToChannel(int) override { return true; }

};

class TopoVoice : public SynthesiserVoice
{
public:

    TopoVoice() {}

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
    void angleCap(); // call after you increment currentAngle to avoid overflows

    float currentAngle = 0.0, angleDelta = 0.0,
        level = 0.0, tailOff = 0.0, twoPi = 0.0;

};
