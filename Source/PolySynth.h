//PolySynth.h
//from FM group

#pragma one

#include "../JuceLibraryCode/JuceHeader.h"
#include "TopoDataLoader.h"
#include "TopoOscParameters.h"
#include "SourceChanger.h"

#include <string>

class PolySynth
{
public:
    
    PolySynth(MidiKeyboardState& keyState, TopoOscParameters* topoParams) : keyboardState(keyState) 
    {
        this->topoParams = topoParams;
        TopoDataLoader t(path + csvNames[0]);
        topoDataChoices[0] = t.getData();
        topoData = &topoDataChoices[0];
        loadedSelection = 0;
    }
    
    ~PolySynth()
    {
        synth.clearSounds();
        synth.clearVoices();
    }

    void changeTopoSource(int choice)
    {
        if (choice >= 4) return;

        if (topoDataChoices[choice].width == 0 || topoDataChoices[choice].height == 0)
        {
            loadedSelection = choice;
            topoParams->sourceLoading = true;
            sourceChanger.changeSource(path + csvNames[choice], &topoDataChoices[choice], &(topoParams->sourceLoading));
        }
        else {
            loadedSelection = choice;
        }
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

        if (!topoParams->sourceLoading) {
            topoData = &topoDataChoices[loadedSelection];
            sourceChanger.stop();
        }
    }
    
private:
    MidiKeyboardState& keyboardState;
    MidiMessageCollector midiCollector;
    Synthesiser synth;
    TopoOscParameters* topoParams;

    std::string path = ABS_PATH;
    std::string csvNames[4] = { EVEREST, IRON, SADDLE, LONGDARK };

    TopoData topoDataChoices[4];
    TopoData* topoData;

    SourceChanger sourceChanger;
    int loadedSelection;
};
