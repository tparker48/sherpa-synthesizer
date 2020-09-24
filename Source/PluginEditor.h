#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/SliderLookAndFeel.h"
#include "UI/DialLookAndFeel.h"
#include "UI/ButtonLookAndFeel.h"
#include "UI/ToggleButtonLookAndFeel.h"
#include "UI/CloseButtonLookAndFeel.h"
#include "UI/NextButtonLookAndFeel.h"


typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
typedef juce::AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;

//==============================================================================
/**
*/
class TopoSynthAudioProcessorEditor  : public AudioProcessorEditor , public MouseListener
{
public:
    TopoSynthAudioProcessorEditor(TopoSynthAudioProcessor&, AudioProcessorValueTreeState&);
    ~TopoSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // main UI
    void sourceChanged();
    void updateToggleState(int mode);
    void buttonStateChanged();
    void filterToggle();
    
    TopoSynthAudioProcessor& processor;
    AudioProcessorValueTreeState& vts;
    
    int numColorSchemes;
    int scheme;
    Colour Colors[4][14];
    Colour Grey;
    
    ComboBox sourceSelect, buttonState, colorChoice;

    Slider gain;
    Slider xTuning, xScale, xPhase;
    Slider yRate, yScale, yPhase;
    Slider filterCutoff, filterResonance;

    ToggleButton xScaleFull, xScaleMedium, xScaleSmall;
    ToggleButton filterTypeToggle;

    SliderLookAndFeel *customSliderX, *customSliderY;
    DialLookAndFeel *customDialX, *customDialFilter, *customDialSource;
    ButtonLookAndFeel *customButton;
    ToggleButtonLookAndFeel *customToggleButton;
    CloseButtonLookAndFeel *customCloseButton;
    NextButtonLookAndFeel *customRightButton;
    NextButtonLookAndFeel *customLeftButton;

    float divisionWidthRatio, divisionHeightRatio, smallSectionWidthRatio, largeSectionWidthRatio, sectionHeightRatio;
    float divisionW, divisionH, smallSectionW, largeSectionW, sectionH;
    float aboutSectionH, aboutSectionW;
    float comboW, comboH, comboX, comboY;

    const float gainSensitivity = 0.05;
    const float xTuningSensitivity = 0.02;
    const float filterCutoffSensitivity = 0.05;
    const float filterResonanceSensitivity = 0.04;
    const float widthMax = 1600.0;


    std::unique_ptr<ButtonAttachment> filterTypeP;
    std::unique_ptr<ComboBoxAttachment> sourceSelectionP, buttonStateP, colorChoiceP;
    std::unique_ptr<SliderAttachment> gainP, xPhaseP, xScaleP, xTuningP, yRateP, yScaleP, yPhaseP, filterCutoffP, filterResonanceP;


    // about section UI
    void mouseUp(const MouseEvent& event) override;

    void initializeAboutMenuUI();
    void paintAboutMenu(Graphics& g);
    void resizedAboutMenu();
    void setAboutVisibility(bool visible);

    void updateLookAndFeels();
    void initLookAndFeels();

    void openAboutMenu();
    void closeAboutMenu();
    void cycleColorScheme(int dir);

    void colorsChanged();

    PopupMenu rightClickMenu;
    bool aboutMenuOpen = false;

    Image vstLogo;

    ToggleButton closeAboutMenuButton, leftButton, rightButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TopoSynthAudioProcessorEditor)
};
