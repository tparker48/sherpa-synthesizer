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
    
    PolySynth(MidiKeyboardState& keyState) : keyboardState(keyState) 
    {
        TopoDataLoader t(path + csvNames[0]);
        topoDataChoices[0] = t.getData();
        topoData = &topoDataChoices[0];
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
            sourceChanger.changeSource(path + csvNames[choice], &topoDataChoices[choice], &loadingIsDone);
        }
        else {
            topoData = &topoDataChoices[choice];
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
    
    /**
     @brief Add a certain number of voices to the PolySynth.
     
     @param T1 : A class that derives from the SynthesiserVoice class (provided by JUCE).
     
     @param  T2 : A class that derives from the SynthesiserSound class (provided by JUCE).
     
     @param number : The amount of voices to be added to the PolySynth.
     */
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

        if (loadingIsDone) {
            topoData = &topoDataChoices[loadedSelection];
            loadingIsDone = false;
            sourceChanger.stop();
        }
    }
    
private:
    MidiKeyboardState& keyboardState;
    MidiMessageCollector midiCollector;
    Synthesiser synth;

    std::string path = ABS_PATH;
    std::string csvNames[4] = { EVEREST, IRON, SADDLE, LONGDARK };

    TopoData topoDataChoices[4];
    TopoData* topoData;

    SourceChanger sourceChanger;
    bool loadingIsDone = false;
    int loadedSelection;
};
