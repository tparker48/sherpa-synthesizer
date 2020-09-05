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
    setSize (700, 300);
    getLookAndFeel().setColour(Slider::trackColourId, Colours::white);

    xScaleModes[X_SCALE_FULL] = 1.0f;
    xScaleModes[X_SCALE_MEDIUM] = 0.5f;
    xScaleModes[X_SCALE_SMALL] = 0.2f;
    processor.topoParams.xScaleMode = X_SCALE_FULL;

    addAndMakeVisible(&yRate);
    yRate.setSliderStyle(Slider::LinearBarVertical);
    yRate.setRange(0, 1000, 10);
    yRate.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    yRate.setPopupDisplayEnabled(false, false, this);
    yRate.setValue(200);

    addAndMakeVisible(&xScale);
    xScale.setSliderStyle(Slider::LinearBarVertical);
    xScale.setRange(0.01, 1, .01);
    xScale.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    xScale.setPopupDisplayEnabled(false, false, this);
    xScale.setValue(0.5);

    addAndMakeVisible(&yScale);
    yScale.setSliderStyle(Slider::LinearBarVertical);
    yScale.setRange(0.001, 1, .01);
    yScale.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    yScale.setPopupDisplayEnabled(false, false, this);
    yScale.setValue(0.5);

    addAndMakeVisible(&xPhase);
    xPhase.setSliderStyle(Slider::LinearBarVertical);
    xPhase.setRange(0.0, 0.99, .01);
    xPhase.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    xPhase.setPopupDisplayEnabled(false, false, this);
    xPhase.setValue(0.0);

    addAndMakeVisible(&yPhase);
    yPhase.setSliderStyle(Slider::LinearBarVertical);
    yPhase.setRange(0.0, 0.99, .01);
    yPhase.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    yPhase.setPopupDisplayEnabled(false, false, this);
    yPhase.setValue(0.0);

    addAndMakeVisible(&filterCutoff);
    filterCutoff.setSliderStyle(Slider::LinearBarVertical);
    filterCutoff.setRange(50.0, 20000.0, 5.0);
    filterCutoff.setSkewFactorFromMidPoint(800.0f);
    filterCutoff.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    filterCutoff.setPopupDisplayEnabled(true, false, this);
    filterCutoff.setValue(7000.0);
    
    addAndMakeVisible(&filterResonance);
    filterResonance.setSliderStyle(Slider::LinearBarVertical);
    filterResonance.setRange(0.01, 1.0, 0.01);
    filterResonance.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    filterResonance.setPopupDisplayEnabled(true, false, this);
    filterResonance.setValue(.3);
   

    addAndMakeVisible(sourceSelect);
    sourceSelect.addItem("Everest", 1);
    sourceSelect.addItem("Iron Mountain", 2);
    sourceSelect.addItem("South Saddle", 3);
    sourceSelect.addItem("The Long Dark", 4);
    sourceSelect.onChange = [this] { sourceChanged(); };
    sourceSelect.setSelectedId(1);

    
    Image normalButton = ImageCache::getFromMemory(BinaryData::button_OFF_png, 4096);
    Image overButton = ImageCache::getFromMemory(BinaryData::button_OFF_png, 4096);
    Image downButton = ImageCache::getFromMemory(BinaryData::button_ON_png, 4096);

    addAndMakeVisible(xScaleFull);
    xScaleFull.setImages(false, false, true, normalButton, 1.0f, {}, overButton, 1.0f, {}, downButton, 1.0f, {});
    xScaleFull.onClick = [this] { updateToggleState(X_SCALE_FULL);   };
    xScaleFull.setRadioGroupId(1001);
    xScaleFull.setClickingTogglesState(true);
    xScaleFull.setToggleState(true, false);

    addAndMakeVisible(xScaleMedium);
    xScaleMedium.setImages(false, false, true, normalButton, 1.0f, {}, overButton, 1.0f, {}, downButton, 1.0f, {});
    xScaleMedium.onClick = [this] { updateToggleState(X_SCALE_MEDIUM);   };
    xScaleMedium.setRadioGroupId(1001);
    xScaleMedium.setClickingTogglesState(true);

    addAndMakeVisible(xScaleSmall);
    xScaleSmall.setImages(false, false, true, normalButton, 1.0f, {}, overButton, 1.0f, {}, downButton, 1.0f, {});
    xScaleSmall.onClick = [this] { updateToggleState(X_SCALE_SMALL);   };
    xScaleSmall.setRadioGroupId(1001);
    xScaleSmall.setClickingTogglesState(true);

    
    xScale.addListener(this);
    xPhase.addListener(this);
    yRate.addListener(this);
    yScale.addListener(this);
    yPhase.addListener(this);
    filterCutoff.addListener(this);
    filterResonance.addListener(this);
}

TopoSynthAudioProcessorEditor::~TopoSynthAudioProcessorEditor()
{
}

//==============================================================================

void TopoSynthAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    //When a slider value changes, check which slider was changed
    //and update the correct processor variable accordingly.

    if (slider == &xScale)
        processor.topoParams.xScale = slider->getValue() * xScaleModes[processor.topoParams.xScaleMode];
    else if (slider == &xPhase)
        processor.topoParams.xPhase = slider->getValue();
    else if (slider == &yRate)
        processor.topoParams.yRate = slider->getValue();
    else if (slider == &yScale)
        processor.topoParams.yScale = slider->getValue();
    else if (slider == &yPhase)
        processor.topoParams.yPhase = slider->getValue();
    else if (slider == &filterCutoff)
        processor.topoParams.filterCutoff = slider->getValue();
    else if (slider == &filterResonance)
        processor.topoParams.filterResonance = slider->getValue();
}

void TopoSynthAudioProcessorEditor::sourceChanged()
{
    int choice = sourceSelect.getSelectedId() - 1;
    processor.topoSynth.changeTopoSource(choice);
}

void TopoSynthAudioProcessorEditor::updateToggleState(int mode)
{
    processor.topoParams.xScaleMode = mode;
    processor.topoParams.xScale = xScale.getValue() * xScaleModes[processor.topoParams.xScaleMode];
}

void TopoSynthAudioProcessorEditor::paint (Graphics& g)
{
    int x = 0;
    int y = getHeight() - 25;
    int width = 50;
    int height = 20;
    int spacing = width + 1;


    g.fillAll ((Colours::darkgrey).darker(1.0));
    g.setColour(Colours::white);

    g.setFont(20.0f);
    g.drawFittedText("X", x + 1  , 10, spacing*2, height, Justification::centred, 1);
    g.setFont(15.0f);


    g.drawFittedText("Phase", x + 0 * spacing, y, width, height, Justification::centred, 1);
    g.drawFittedText("Scale", x + 1 * spacing, y, width, height, Justification::centred, 1);

    x += 200;

    g.setFont(20.0f);
    g.drawFittedText("Y", x + 1, 10, spacing * 3, height, Justification::centred, 1);
    g.setFont(15.0f);

    g.drawFittedText("Rate", x + 0 * spacing, y, width, height, Justification::centred, 1);
    g.drawFittedText("Phase", x + 1 * spacing, y, width, height, Justification::centred, 1);
    g.drawFittedText("Scale", x + 2 * spacing, y, width, height, Justification::centred, 1);

    x += 200;

    g.setFont(20.0f);
    g.drawFittedText("Filter", x + 1, 10, spacing * 2, height, Justification::centred, 1);
    g.setFont(15.0f);

    g.drawFittedText("Cutoff", x + 0 * spacing, y, width, height, Justification::centred, 1);
    g.drawFittedText("Resonance", x + 1 * spacing, y, width, height, Justification::centred, 1);

}

void TopoSynthAudioProcessorEditor::resized()
{
    int width = 25;
    int height = getHeight() - 70;

    int sizeButton = 25;

    int spacing = width + 25;

    int xBottom = 40;
    int xLeft = 15;
    int yBottom = 40;
    int yLeft = xLeft + 200;

    int filterLeft = yLeft + 200;
    
    // sets the position and size of the slider with arguments (x, y, width, height)
    xPhase.setBounds(xLeft + 0*spacing, xBottom, width, height);
    xScale.setBounds(xLeft + 1*spacing, xBottom, width, height);

    
    xScaleFull.setBounds(  xLeft + 2 * spacing, xBottom,       sizeButton, sizeButton);
    xScaleMedium.setBounds(xLeft + 2 * spacing, xBottom + 50,  sizeButton, sizeButton);
    xScaleSmall.setBounds( xLeft + 2 * spacing, xBottom + 100, sizeButton, sizeButton);

    yRate.setBounds( yLeft + 0 * spacing, yBottom, width, height);
    yPhase.setBounds(yLeft + 1 * spacing, yBottom, width, height);
    yScale.setBounds(yLeft + 2 * spacing, yBottom, width, height);

    filterCutoff.setBounds(   filterLeft + 0 * spacing, yBottom, width, height);
    filterResonance.setBounds(filterLeft + 1 * spacing, yBottom, width, height);

    sourceSelect.setBounds(filterLeft + 2 * spacing, yBottom, 50, 25);
}