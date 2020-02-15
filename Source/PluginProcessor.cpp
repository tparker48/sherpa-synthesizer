/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TopoSynthAudioProcessor::TopoSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
                       topoSynth(keyboardState)
#else 
    : topoSynth(keyboardState)
#endif
{

    topoSynth.clearVoices();
    topoSynth.clearSounds();

    topoParams.xRate    = 1.0;
    topoParams.xScale   = 1.0;
    topoParams.xPhase   = 0.0;
    topoParams.yRate = 0.00001;
    topoParams.yScale = 1.0;
    topoParams.yPhase = 1.0;

    topoSynth.addVoice<TopoVoice, TopoSound>(12, &topoParams);
}

TopoSynthAudioProcessor::~TopoSynthAudioProcessor()
{
}

//==============================================================================
const String TopoSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TopoSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TopoSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TopoSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TopoSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TopoSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TopoSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TopoSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String TopoSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void TopoSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TopoSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    topoSynth.prepareToPlay(sampleRate);
}

void TopoSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TopoSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TopoSynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    buffer.clear();

    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; i++)
        buffer.clear(i, 0, buffer.getNumSamples());

    // WIP, NOT GENERAL ENOUGH -- Will be used to pass parameters to PolySynth.
    for (auto i = 0; i < topoSynth.getNumVoices(); i++)
    {
        if ((tempVoice = dynamic_cast<TopoVoice*>(topoSynth.getVoice(i))))
        {
        }
    }

    topoSynth.renderNextAudioBlock(buffer, 0, buffer.getNumSamples(), midiMessages);
}

//==============================================================================
bool TopoSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TopoSynthAudioProcessor::createEditor()
{
    return new TopoSynthAudioProcessorEditor (*this);
}

//==============================================================================
void TopoSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TopoSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TopoSynthAudioProcessor();
}
