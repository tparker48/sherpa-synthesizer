/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TopoSynthAudioProcessorEditor::TopoSynthAudioProcessorEditor (TopoSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    double ratio = 7.0 / 3.5;
    setResizeLimits(400, 400 / ratio, 1600, 1600 / ratio);
    getConstrainer()->setFixedAspectRatio(ratio);
    setSize(1000.0, 1000.0 / ratio);

    Grey = Colour(60, 60, 60);
    Red = Colour(214, 40, 40);
    Orange = Colour(247, 127, 0);
    Yellow = Colour(252, 191, 73);
    Green = Colour(95, 198, 148);

    xScaleModes[X_SCALE_FULL] = .5f;
    xScaleModes[X_SCALE_MEDIUM] = 0.25f;
    xScaleModes[X_SCALE_SMALL] = 0.1f;
    processor.topoParams.xScaleMode = X_SCALE_FULL;

    divisionWidthRatio = 0.014;
    divisionHeightRatio = 0.028;
    smallSectionWidthRatio = 0.185;
    largeSectionWidthRatio = 0.28;
    sectionHeightRatio = 0.94;
   
    customSlider = new SliderLookAndFeel(Grey, Colours::white);
    customDial = new DialLookAndFeel(Grey, Colours::white);
    customButton = new ButtonLookAndFeel(Grey, Colours::white);

    getLookAndFeel().setColour(PopupMenu::ColourIds::backgroundColourId, Grey);
    getLookAndFeel().setColour(PopupMenu::ColourIds::highlightedBackgroundColourId, (Colours::darkgrey));
    getLookAndFeel().setColour(PopupMenu::ColourIds::textColourId, (Colours::white));
    getLookAndFeel().setColour(PopupMenu::ColourIds::highlightedTextColourId, (Colours::white));

    

    //xScaleModes[X_SCALE_FULL] = 1.0f;
    //xScaleModes[X_SCALE_MEDIUM] = 0.5f;
    //xScaleModes[X_SCALE_SMALL] = 0.2f;
    //processor.topoParams.xScaleMode = X_SCALE_FULL;

    // Source Select Combo Box
    addAndMakeVisible(sourceSelect);
    sourceSelect.addItem("Everest", 1);
    sourceSelect.addItem("Iron Mountain", 2);
    sourceSelect.addItem("South Saddle", 3);
    sourceSelect.addItem("The Long Dark", 4);
    sourceSelect.setSelectedId(1);
    sourceSelect.onChange = [this] { sourceChanged(); };
    sourceSelect.setColour(ComboBox::ColourIds::backgroundColourId, Grey);
    sourceSelect.setColour(ComboBox::ColourIds::textColourId, (Colours::white));
    sourceSelect.setColour(ComboBox::ColourIds::outlineColourId, Grey);

    // Gain Knob
    addAndMakeVisible(&gain);
    gain.setSliderStyle(Slider::LinearBarVertical);
    gain.setRange(0.0, 1.0, .001);
    gain.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    gain.setPopupDisplayEnabled(false, false, this);
    gain.setValue(.75);
    gain.setLookAndFeel(customDial);
    gain.setVelocityBasedMode(true);


    // X Phase Slider
    addAndMakeVisible(&xPhase);
    xPhase.setSliderStyle(Slider::LinearBarVertical);
    xPhase.setRange(0.0, .99, 0.01);
    xPhase.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    xPhase.setPopupDisplayEnabled(false, false, this);
    xPhase.setValue(.5);
    xPhase.setLookAndFeel(customSlider);

    // X Scale Slider
    addAndMakeVisible(&xScale);
    xScale.setSliderStyle(Slider::LinearBarVertical);
    xScale.setRange(0.01, 1.0, 0.01);
    xScale.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    xScale.setPopupDisplayEnabled(false, false, this);
    xScale.setValue(.5);
    xScale.setLookAndFeel(customSlider);

    // X Tuning Dial
    addAndMakeVisible(&xTuning);
    xTuning.setSliderStyle(Slider::LinearBarVertical);
    xTuning.setRange(0.0, 1.0, .001);
    xTuning.setTextBoxStyle(Slider::NoTextBox, false, 70, 30);
    xTuning.setPopupDisplayEnabled(false, false, this);
    xTuning.setValue(0.5);
    xTuning.setLookAndFeel(customDial);
    xTuning.setVelocityBasedMode(true);
    xTuning.setDoubleClickReturnValue(true, 0.5);


    // X Scale Buttons
    // Full
    addAndMakeVisible(&xScaleFull);
    xScaleFull.onClick = [this] { updateToggleState(X_SCALE_FULL);   };
    xScaleFull.setRadioGroupId(1001);
    xScaleFull.setClickingTogglesState(true);
    xScaleFull.setLookAndFeel(customButton);
    xScaleFull.setToggleState(true, NotificationType::dontSendNotification);

    // Medium
    addAndMakeVisible(&xScaleMedium);
    xScaleMedium.onClick = [this] { updateToggleState(X_SCALE_MEDIUM);   };
    xScaleMedium.setRadioGroupId(1001);
    xScaleMedium.setClickingTogglesState(true);
    xScaleMedium.setLookAndFeel(customButton);

    //Small
    addAndMakeVisible(&xScaleSmall);
    xScaleSmall.onClick = [this] { updateToggleState(X_SCALE_SMALL);   };
    xScaleSmall.setRadioGroupId(1001);
    xScaleSmall.setClickingTogglesState(true);
    xScaleSmall.setLookAndFeel(customButton);

    // Y Phase
    addAndMakeVisible(&yPhase);
    yPhase.setSliderStyle(Slider::LinearBarVertical);
    yPhase.setRange(0.0, 0.99, 0.01);
    yPhase.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    yPhase.setPopupDisplayEnabled(false, false, this);
    yPhase.setValue(.5);
    yPhase.setLookAndFeel(customSlider);

    // Y Rate
    addAndMakeVisible(&yRate);
    yRate.setSliderStyle(Slider::LinearBarVertical);
    yRate.setRange(0.0, 750.0, .5);
    yRate.setSkewFactorFromMidPoint(250.0f);
    yRate.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    yRate.setPopupDisplayEnabled(false, false, this);
    yRate.setValue(200);
    yRate.setLookAndFeel(customSlider);

    // Y Scale
    addAndMakeVisible(&yScale);
    yScale.setSliderStyle(Slider::LinearBarVertical);
    yScale.setRange(0.0, 1.0, 0.01);
    yScale.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    yScale.setPopupDisplayEnabled(false, false, this);
    yScale.setValue(.5);
    yScale.setLookAndFeel(customSlider);

    // Filter Cutoff
    addAndMakeVisible(&filterCutoff);
    filterCutoff.setSliderStyle(Slider::LinearBarVertical);
    filterCutoff.setRange(0.0, 1.0, 0.001);
    filterCutoff.setSkewFactorFromMidPoint(.2f);
    filterCutoff.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    filterCutoff.setPopupDisplayEnabled(false, false, this);
    filterCutoff.setValue(0.4);
    filterCutoff.setLookAndFeel(customDial);
    filterCutoff.setVelocityBasedMode(true);

    // Filter Resonance
    addAndMakeVisible(&filterResonance);
    filterResonance.setSliderStyle(Slider::LinearBarVertical);
    filterResonance.setRange(0.0, 1.0, 0.001);
    filterResonance.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    filterResonance.setPopupDisplayEnabled(false, false, this);
    filterResonance.setValue(.3);
    filterResonance.setLookAndFeel(customDial);
    filterResonance.setVelocityBasedMode(true);


    gain.setVelocityModeParameters(1.0, 0, gainSensitivity, false);
    xTuning.setVelocityModeParameters(1.0, 0, xTuningSensitivity, false);
    filterCutoff.setVelocityModeParameters(1.0, 0, filterCutoffSensitivity, false);
    filterResonance.setVelocityModeParameters(1.0, 0, filterResonanceSensitivity, false);

    gain.addListener(this);
     
    xScale.addListener(this);
    xPhase.addListener(this);
    xTuning.addListener(this);

    yRate.addListener(this);
    yScale.addListener(this);
    yPhase.addListener(this);

    filterCutoff.addListener(this);
    filterResonance.addListener(this);


    resized();
}

TopoSynthAudioProcessorEditor::~TopoSynthAudioProcessorEditor()
{
    gain.setLookAndFeel(nullptr);
    xPhase.setLookAndFeel(nullptr);
    xScale.setLookAndFeel(nullptr);
    xTuning.setLookAndFeel(nullptr);
    xScaleFull.setLookAndFeel(nullptr);
    xScaleMedium.setLookAndFeel(nullptr);
    xScaleSmall.setLookAndFeel(nullptr);
    yPhase.setLookAndFeel(nullptr);
    yRate.setLookAndFeel(nullptr);
    yScale.setLookAndFeel(nullptr);
    filterCutoff.setLookAndFeel(nullptr);
    filterResonance.setLookAndFeel(nullptr);
    
    delete customSlider;
    delete customDial;
    delete customButton;
}

//==============================================================================
void TopoSynthAudioProcessorEditor::paint (Graphics& g)
{
    // Draw each background pannel

    g.fillAll(Grey);

    float x = divisionW;
    float y = divisionH;

    g.setColour(Red);
    g.fillRect(x, y , smallSectionW, sectionH);

    x += divisionW + smallSectionW ;


    g.setColour(Orange);
    g.fillRect(x, y, largeSectionW, sectionH);

    x += divisionW + largeSectionW;


    g.setColour(Yellow);
    g.fillRect(x, y, largeSectionW, sectionH);

    x += divisionW + largeSectionW;


    g.setColour(Green);
    g.fillRect(x, y, smallSectionW, sectionH);

    // Square off edges of the comboBox
    g.setColour(Grey);
    g.fillRect(comboX, comboY, comboW, comboH);

    
    // Text
    g.setColour(Grey);

    float fontHeader = getWidth() * 0.025;
    float fontLabel = getWidth() * 0.0175;
    
    int textW = getWidth() * 0.1;
    int textH = getHeight() * 0.1;

    int headerY = y + sectionH * .05 - textH / 2;

    // Pannel text
    g.setFont(fontHeader);

    x = divisionW;
    g.drawFittedText("signal", x + smallSectionW/2 - textW/2, headerY , textW, textH, Justification::centred, 1);

    x += smallSectionW + divisionW;
    g.drawFittedText("x", x + largeSectionW / 2 - textW / 2, headerY, textW, textH, Justification::centred, 1);

    x += largeSectionW + divisionW;
    g.drawFittedText("y", x + largeSectionW / 2 - textW / 2, headerY, textW, textH, Justification::centred, 1);

    x += largeSectionW + divisionW;
    g.drawFittedText("filter", x + smallSectionW / 2 - textW / 2, headerY, textW, textH, Justification::centred, 1);

    // label text
    g.setFont(fontLabel);
    

    Component* c;

    // source
    c = &sourceSelect;
    x = c->getX() + (c->getWidth()/2) - textW / 2;
    y = c->getBottom();
    g.drawFittedText("source",x , y, textW, textH, Justification::centred, 1);

    // gain
    c = &gain;
    x = c->getX() + (c->getWidth() / 2) - textW / 2;
    y = c->getBottom();
    g.drawFittedText("gain", x, y, textW, textH, Justification::centred, 1);


    // x phase
    c = &xPhase;
    x = c->getX() + (c->getWidth() / 2) - textW / 2;
    y = c->getBottom();
    g.drawFittedText("phase", x, y, textW, textH, Justification::centred, 1);

    // x scale
    c = &xScale;
    x = c->getX() + (c->getWidth() / 2) - textW / 2;
    y = c->getBottom();
    g.drawFittedText("scale", x, y, textW, textH, Justification::centred, 1);

    // x scale range
    int buttonLabelPaddingFactor = 0.03 * getHeight();

    c = &xScaleFull;
    x = c->getX() + (c->getWidth() / 2) - textW / 2;
    //y = c->getBottom();
    g.drawFittedText("scale_range", x, y, textW, textH, Justification::centred, 1);

    c = &xScaleFull;
    y = c->getBottom() - buttonLabelPaddingFactor;
    g.drawFittedText("---", x, y, textW, textH, Justification::centred, 1);

    c = &xScaleMedium;
    y = c->getBottom() - buttonLabelPaddingFactor;
    g.drawFittedText("--", x, y, textW, textH, Justification::centred, 1);

    c = &xScaleSmall;
    y = c->getBottom() - buttonLabelPaddingFactor;
    g.drawFittedText("-", x, y, textW, textH, Justification::centred, 1);

    // x detune
    c = &xTuning;
    x = c->getX() + (c->getWidth() / 2) - textW / 2;
    y = c->getBottom();
    g.drawFittedText("detune", x, y, textW, textH, Justification::centred, 1);

    // y phase
    c = &yPhase;
    x = c->getX() + (c->getWidth() / 2) - textW / 2;
    y = c->getBottom();
    g.drawFittedText("phase", x, y, textW, textH, Justification::centred, 1);

    //// y rate
    c = &yRate;
    x = c->getX() + (c->getWidth() / 2) - textW / 2;
    y = c->getBottom();
    g.drawFittedText("rate", x, y, textW, textH, Justification::centred, 1);

    //// y scale
    c = &yScale;
    x = c->getX() + (c->getWidth() / 2) - textW / 2;
    y = c->getBottom();
    g.drawFittedText("scale", x, y, textW, textH, Justification::centred, 1);

    // cutoff
    c = &filterCutoff;
    x = c->getX() + (c->getWidth() / 2) - textW / 2;
    y = c->getBottom();
    g.drawFittedText("cutoff", x, y, textW, textH, Justification::centred, 1);

    // resonance
    c = &filterResonance;
    x = c->getX() + (c->getWidth() / 2) - textW / 2;
    y = c->getBottom();
    g.drawFittedText("resonance", x, y, textW, textH, Justification::centred, 1);


}

void TopoSynthAudioProcessorEditor::resized()
{
    // update scaling variables

    double w = getWidth();
    double h = getHeight();

    divisionW = divisionWidthRatio * w;
    divisionH = divisionHeightRatio * h;
    smallSectionW = smallSectionWidthRatio * w;
    largeSectionW = largeSectionWidthRatio * w;
    sectionH = sectionHeightRatio * h;

    int sliderW = largeSectionW * .2;
    int sliderH = sectionH * .75;
    int sliderXPadding = largeSectionW * .075;

    int largeDialSize = smallSectionW * .5;
    int smallDialSize = largeDialSize * .75;

    comboW = smallSectionW * .8;
    comboH = comboW * .2;
    float comboXPadding = (smallSectionW - comboW) / 2.0;
    float comboYPadding = sectionH * .25;
    
    // Red Pannel 
    int x = divisionW;
    int y = divisionH;

    comboX = x + comboXPadding;
    comboY = y + comboYPadding;
    sourceSelect.setBounds(x + comboXPadding ,y + comboYPadding, comboW, comboH);

    int gainXPadding = (smallSectionW - largeDialSize) / 2.0;
    int gainYPadding = sectionH * .55;
    gain.setBounds(x + gainXPadding, y + gainYPadding, largeDialSize, largeDialSize);

    // Orange Pannel
    x += divisionW + smallSectionW;

    xPhase.setBounds(x + sliderXPadding, y + (sectionH - sliderH) / 2, sliderW, sliderH);

    int xScalePadding = 4.75 * sliderXPadding;
    xScale.setBounds(x + xScalePadding, y + (sectionH - sliderH) / 2, sliderW, sliderH);

    int xScaleRightEdge = (xScalePadding + sliderW);
    int xTuningXPadding = xScaleRightEdge + ((largeSectionW - xScaleRightEdge) - smallDialSize) / 2.0;
    int xTuningYPadding = sectionH * .15;
    xTuning.setBounds(x + xTuningXPadding, y + xTuningYPadding, smallDialSize, smallDialSize);

    int buttonSize = largeSectionW * .12;
    int xButtonXPadding = xScaleRightEdge + ((largeSectionW - xScaleRightEdge) - buttonSize) / 2.0;
    int xButtonYPadding = sectionH * .46;
    int xButtonYSpacing = buttonSize * 2.0;

    xScaleFull.setBounds(x + xButtonXPadding,   y + xButtonYPadding + 0*xButtonYSpacing, buttonSize, buttonSize);
    xScaleMedium.setBounds(x + xButtonXPadding, y + xButtonYPadding + 1*xButtonYSpacing, buttonSize, buttonSize);
    xScaleSmall.setBounds(x + xButtonXPadding,  y + xButtonYPadding + 2*xButtonYSpacing, buttonSize, buttonSize);
    
    // Yellow Pannel
    x += divisionW + largeSectionW;
    sliderXPadding = sliderXPadding * 1.25;

    yPhase.setBounds(x + sliderXPadding, y + (sectionH - sliderH) / 2, sliderW, sliderH);

    int yRateXPadding = (largeSectionW - sliderW) / 2;
    yRate.setBounds(x + yRateXPadding, y + (sectionH - sliderH) / 2, sliderW, sliderH);

    int yScaleXPadding = largeSectionW - sliderW - sliderXPadding;
    yScale.setBounds(x + yScaleXPadding, y + (sectionH - sliderH) / 2, sliderW, sliderH);

    // Green Pannel
    x += divisionW + largeSectionW;

    int cutoffXPadding = (smallSectionW - largeDialSize) / 2;
    int cutoffYPadding = sectionH * .18;
    filterCutoff.setBounds(x + cutoffXPadding, y + cutoffYPadding, largeDialSize, largeDialSize);

    int resonanceXPadding = (smallSectionW - smallDialSize) / 2;
    int resonanceYPadding = sectionH * .6;
    filterResonance.setBounds(x + resonanceXPadding, y + resonanceYPadding, smallDialSize, smallDialSize);
}



void TopoSynthAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    //When a slider value changes, check which slider was changed
    //and update the correct processor variable accordingly.

    if (slider == &gain)
        processor.topoParams.gain = (slider->getValue()) * 1.25;
    else if (slider == &xScale)
        processor.topoParams.xScale = .1f + slider->getValue() * xScaleModes[processor.topoParams.xScaleMode];
    else if (slider == &xPhase)
        processor.topoParams.xPhase = slider->getValue();
    else if (slider == &xTuning)
        processor.topoParams.xTuning = -((slider->getValue()*.5f) - 0.25f);
    else if (slider == &yRate)
        processor.topoParams.yRate = slider->getValue();
    else if (slider == &yScale)
        processor.topoParams.yScale = slider->getValue();
    else if (slider == &yPhase)
        processor.topoParams.yPhase = slider->getValue();
    else if (slider == &filterCutoff)
        processor.topoParams.filterCutoff = 50.0f + (slider->getValue() * 19950.0f);
    else if (slider == &filterResonance)
        processor.topoParams.filterResonance = (slider->getValue() * .87f) + .05f;
}

void TopoSynthAudioProcessorEditor::sourceChanged()
{
    int choice = sourceSelect.getSelectedId() - 1;
    processor.topoSynth.changeTopoSource(choice);
}

void TopoSynthAudioProcessorEditor::updateToggleState(int mode)
{
    processor.topoParams.xScaleMode = mode;
    processor.topoParams.xScale = .1f +  xScale.getValue() * xScaleModes[processor.topoParams.xScaleMode];
}
