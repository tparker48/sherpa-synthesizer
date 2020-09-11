#include "PluginProcessor.h"
#include "PluginEditor.h"

TopoSynthAudioProcessor::TopoSynthAudioProcessor()
    : AudioProcessor(BusesProperties().withOutput("Output", AudioChannelSet::stereo(), true)), topoSynth(keyboardState, &topoParams),
      vts(*this, nullptr, "parameters", createParameterLayout())
{
    topoParams.vts = &(this->vts);
    topoSynth.clearVoices();
    topoSynth.clearSounds();

    topoSynth.addVoice<TopoVoice, TopoSound>(12, &topoParams);
}

TopoSynthAudioProcessor::~TopoSynthAudioProcessor()
{
}

const String TopoSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TopoSynthAudioProcessor::acceptsMidi() const
{
    return true;
}

bool TopoSynthAudioProcessor::producesMidi() const
{
    return false;
}

bool TopoSynthAudioProcessor::isMidiEffect() const
{
    return false;
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


void TopoSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    topoSynth.prepareToPlay(sampleRate);
    filterLeft.init(sampleRate);
    filterRight.init(sampleRate);
}

void TopoSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TopoSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    return true;
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

    float cutoff = getCutoff();
    float resonance = getResonance();

    filterLeft.setCutoff(cutoff);
    filterLeft.setResonance(resonance);

    filterRight.setCutoff(cutoff);
    filterRight.setResonance(resonance);

    topoSynth.renderNextAudioBlock(buffer, 0, buffer.getNumSamples(), midiMessages);
    filterLeft.processBlock(buffer,  0, LOWPASS);
    filterRight.processBlock(buffer, 1, LOWPASS);
  
}

bool TopoSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TopoSynthAudioProcessor::createEditor()
{
    return new TopoSynthAudioProcessorEditor (*this, vts);
}


void TopoSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    auto state = vts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void TopoSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(vts.state.getType()))
            vts.replaceState(juce::ValueTree::fromXml(*xmlState));
}


AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TopoSynthAudioProcessor();
}





AudioProcessorValueTreeState::ParameterLayout TopoSynthAudioProcessor::createParameterLayout()
{

    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    auto sourceSelection = std::make_unique<AudioParameterFloat>("sourceSelection", "Source", 1.0, NUM_SOURCES, 1.0);

    auto gain = std::make_unique<AudioParameterFloat>("gain", "Gain",
        NormalisableRange<float>(0.0f, 1.25f, 0.01f), 1.0f);

    auto xPhase = std::make_unique<AudioParameterFloat>("xPhase", "X Phase",
        NormalisableRange<float>(0.0f, .99f, false), 0.2f);

    auto xScale = std::make_unique<AudioParameterFloat>("xScale", "X Scale",
        NormalisableRange<float>(0.01f, 1.0f, 0.01f), 0.3f);

    auto xScaleRange = std::make_unique<AudioParameterFloat>("xScaleRange", "X Scale Range", 1.0, 3.0, 3.0);

    auto xTuning = std::make_unique<AudioParameterFloat>("xTuning", "Detune",
        NormalisableRange<float>(0.0, 1.0, .001), 0.5f);

    auto yPhase = std::make_unique<AudioParameterFloat>("yPhase", "Y Phase",
        NormalisableRange<float>(0.0f, .99f, 0.01f), 0.5f);

    auto yScale = std::make_unique<AudioParameterFloat>("yScale", "Y Scale",
        NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.2f);

    auto yRate = std::make_unique<AudioParameterFloat>("yRate", "Y Rate",
        NormalisableRange<float>(0.01f, 850.0f, 0.01f, 0.5f), 250.0f);


    auto filterCutoff = std::make_unique<AudioParameterFloat>("filterCutoff", "Filter Cutoff",
        NormalisableRange<float>(50.00f, 20000.0f, 0.001f, .45f), 4000.0f);

    auto filterResonance = std::make_unique<AudioParameterFloat>("filterResonance", "Filter Resonance",
        NormalisableRange<float>(0.0f, 1.0f, 0.001f), .2f);

    params.push_back(std::move(sourceSelection));
    params.push_back(std::move(gain));
    params.push_back(std::move(xPhase));
    params.push_back(std::move(xScale));
    params.push_back(std::move(xScaleRange));
    params.push_back(std::move(xTuning));
    params.push_back(std::move(yPhase));
    params.push_back(std::move(yScale));
    params.push_back(std::move(yRate));
    params.push_back(std::move(filterCutoff));
    params.push_back(std::move(filterResonance));

    return { params.begin(), params.end() };
}

float TopoSynthAudioProcessor::getCutoff()
{
    auto x = vts.getRawParameterValue("filterCutoff");
    if (x != NULL)
    {
        return *x;
    }
    else return 600.0f;
}
float TopoSynthAudioProcessor::getResonance()
{
    auto x = vts.getRawParameterValue("filterResonance");
    if (x != NULL)
    {
        return (*x * .87f) + .05f;
    }
    else return 0.2f;
}