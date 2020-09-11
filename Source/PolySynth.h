//PolySynth.h
//from FM group

#pragma one

#include "../JuceLibraryCode/JuceHeader.h"
#include "TopoDataLoader.h"
#include "TopoOscParameters.h"

#include <string>

class PolySynth
{
public:
    
    PolySynth(MidiKeyboardState& keyState, TopoOscParameters* topoParams) : keyboardState(keyState) 
    {
        this->topoParams = topoParams;

        for (int i = 0; i < NUM_SOURCES; i++)
        {
            TopoDataLoader t(i);
            topoDataChoices[i] = t.getData();
        }
        topoData = &topoDataChoices[EVEREST];
    }
    
    ~PolySynth()
    {
        synth.clearSounds();
        synth.clearVoices();
    }

    void changeTopoSource(int choice)
    {
        if (choice >= NUM_SOURCES) return;
        topoData = &topoDataChoices[choice];
    }

    int getNumVoices() const noexcept
    {
        return synth.getNumVoices();
    }
    
    SynthesiserVoice* getVoice(int index) const
    {
        return synth.getVoice(index);
    }


    template<typename T1, typename T2>
    void addVoice(int number, TopoOscParameters* topoParams)
    {
        static_assert(std::is_base_of<SynthesiserVoice, T1>::value,
                      "Second type must derive from the SynthesiserVoice class.");
        static_assert(std::is_base_of<SynthesiserSound, T2>::value,
                             "First type must derive from the SynthesiserSound class.");
        
        for (auto i = 0; i < number; ++i)
            synth.addVoice (new T1(&topoData, topoParams));
        
        synth.addSound (new T2());
    }
    
    void clearSounds()
    {
       synth.clearSounds();
    }
    
    void clearVoices()
    {
        synth.clearVoices();
    }
    
    void prepareToPlay (double sampleRate)
    {
        synth.setCurrentPlaybackSampleRate (sampleRate);
        midiCollector.reset (sampleRate);
    }
    
    MidiMessageCollector* getMidiCollector()
    {
        return &midiCollector;
    }
    
     void renderNextAudioBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples, MidiBuffer& incomingMidi)
    {
        outputBuffer.clear();
        
        midiCollector.removeNextBlockOfMessages (incomingMidi, numSamples);

        keyboardState.processNextMidiBuffer (incomingMidi, startSample,
                                             numSamples, true);

        synth.renderNextBlock (outputBuffer, incomingMidi,
                               startSample, numSamples);
    }
    
private:
    MidiKeyboardState& keyboardState;
    MidiMessageCollector midiCollector;
    Synthesiser synth;
    TopoOscParameters* topoParams;

    TopoData topoDataChoices[NUM_SOURCES];
    TopoData* topoData;

    int loadedSelection;
};
