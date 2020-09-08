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

    void paint (Graphics&) override;
    void resized() override;

private:
    TopoSynthAudioProcessor& processor;

    ComboBox sourceSelect;

    Slider xRate, xScale, xPhase;
    Slider yRate, yScale, yPhase;
    Slider filterCutoff, filterResonance;

    ImageButton xScaleFull, xScaleMedium, xScaleSmall;
    float xScaleModes[3];

    void sliderValueChanged(Slider* slider) override;
    void sourceChanged();
    void updateToggleState(int mode);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TopoSynthAudioProcessorEditor)
};
