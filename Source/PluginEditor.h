/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TopoSynthAudioProcessorEditor  : public AudioProcessorEditor,
                                       private Slider::Listener
{
public:
    TopoSynthAudioProcessorEditor (TopoSynthAudioProcessor&);
    ~TopoSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    TopoSynthAudioProcessor& processor;

    Slider xRate, xScale, xPhase;
    Slider yRate, yScale, yPhase;
    Slider filterCutoff, filterResonance;

    void sliderValueChanged(Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TopoSynthAudioProcessorEditor)
};
