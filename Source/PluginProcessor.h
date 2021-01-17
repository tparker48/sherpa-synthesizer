#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PolySynth.h"
#include "TopoOsc.h"
#include "StilsonMoogFilter.h"
#include "DCFilter.h"

class TopoSynthAudioProcessor  : public AudioProcessor
{
public:
  
    TopoSynthAudioProcessor();
    ~TopoSynthAudioProcessor();

    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    PolySynth topoSynth;
    TopoOscParameters topoParams;

private:
    float getFilterType();
    float getCutoff();
    float getResonance();

    MidiKeyboardState keyboardState;
    StilsonMoogFilter filterLeft, filterRight;
    DCFilter dcLeft, dcRight;
    TopoVoice* tempVoice;

    AudioProcessorValueTreeState vts;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TopoSynthAudioProcessor)
};
