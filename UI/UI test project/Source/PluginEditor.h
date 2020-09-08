/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SliderLookAndFeel.h"
#include "DialLookAndFeel.h"
#include "ButtonLookAndFeel.h"

//==============================================================================
/**
*/
class UiTestAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    UiTestAudioProcessorEditor (UiTestAudioProcessor&);
    ~UiTestAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    UiTestAudioProcessor& processor;

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

    float gainSensitivity = 0.05;
    float xTuningSensitivity = 0.02;
    float filterCutoffSensitivity = 0.05;
    float filterResonanceSensitivity = 0.04;
    float widthMax = 1600.0;
 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UiTestAudioProcessorEditor)
};
