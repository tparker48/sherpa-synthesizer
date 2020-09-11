#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/SliderLookAndFeel.h"
#include "UI/DialLookAndFeel.h"
#include "UI/ButtonLookAndFeel.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef juce::AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;

//==============================================================================
/**
*/
class TopoSynthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    TopoSynthAudioProcessorEditor(TopoSynthAudioProcessor&, AudioProcessorValueTreeState&);
    ~TopoSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    void sourceChanged();
    void updateToggleState(int mode);
    void buttonStateChanged();
    
    TopoSynthAudioProcessor& processor;
    AudioProcessorValueTreeState& vts;

    Colour Grey, Red, Orange, Yellow, Green;
    
    ComboBox sourceSelect, buttonState;

    Slider gain;
    Slider xTuning, xScale, xPhase;
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

    
    std::unique_ptr<ComboBoxAttachment> sourceSelectionP, buttonStateP;
    std::unique_ptr<SliderAttachment> gainP, xPhaseP, xScaleP, xTuningP, yRateP, yScaleP, yPhaseP,
                                        filterCutoffP, filterResonanceP;

   

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TopoSynthAudioProcessorEditor)
};
