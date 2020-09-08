/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/SliderLookAndFeel.h"
#include "UI/DialLookAndFeel.h"
#include "UI/ButtonLookAndFeel.h"

//==============================================================================
/**
*/
class TopoSynthAudioProcessorEditor  : public AudioProcessorEditor,
                                       private Slider::Listener
{
public:
    TopoSynthAudioProcessorEditor(TopoSynthAudioProcessor&);
    ~TopoSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged(Slider* slider) override;
    void sourceChanged();
    void updateToggleState(int mode);
    
    TopoSynthAudioProcessor& processor;

    Colour Grey, Red, Orange, Yellow, Green;
    
    ComboBox sourceSelect;

    Slider gain;
    Slider  xTuning, xScale, xPhase;
    Slider yRate, yScale, yPhase;
    Slider filterCutoff, filterResonance;

    ToggleButton xScaleFull, xScaleMedium, xScaleSmall;
    float xScaleModes[3];

    SliderLookAndFeel* customSlider;
    DialLookAndFeel* customDial;
    ButtonLookAndFeel* customButton;

    float divisionWidthRatio, divisionHeightRatio, smallSectionWidthRatio, largeSectionWidthRatio, sectionHeightRatio;
    float divisionW, divisionH, smallSectionW, largeSectionW, sectionH;
    float comboW, comboH, comboX, comboY;

    const float gainSensitivity = 0.05;
    const float xTuningSensitivity = 0.02;
    const float filterCutoffSensitivity = 0.05;
    const float filterResonanceSensitivity = 0.04;
    const float widthMax = 1600.0;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TopoSynthAudioProcessorEditor)
};
