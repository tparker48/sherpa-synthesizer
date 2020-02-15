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

    File f = File::getCurrentWorkingDirectory().getChildFile("C:\\Users\\Tom\\Documents\\theMountain\\Images\\everest.jpg");
    img = ImageFileFormat::loadFrom(f);
    img = img.rescaled(300, 250);

    xRate.setSliderStyle(Slider::LinearBarVertical);
    xRate.setRange(256, 1024, 32);
    xRate.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    xRate.setPopupDisplayEnabled(false, false, this);
    xRate.setValue(256);

    yRate.setSliderStyle(Slider::LinearBarVertical);
    yRate.setRange(0, 1000, 10);
    yRate.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    yRate.setPopupDisplayEnabled(false, false, this);
    yRate.setValue(200);

    xScale.setSliderStyle(Slider::LinearBarVertical);
    xScale.setRange(0.001, 1, .01);
    xScale.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    xScale.setPopupDisplayEnabled(false, false, this);
    xScale.setValue(0.5);

    yScale.setSliderStyle(Slider::LinearBarVertical);
    yScale.setRange(0.001, 1, .01);
    yScale.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    yScale.setPopupDisplayEnabled(false, false, this);
    yScale.setValue(0.5);

    xPhase.setSliderStyle(Slider::LinearBarVertical);
    xPhase.setRange(0.0, 0.99, .01);
    xPhase.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    xPhase.setPopupDisplayEnabled(false, false, this);
    xPhase.setValue(0.0);

    yPhase.setSliderStyle(Slider::LinearBarVertical);
    yPhase.setRange(0.0, 0.99, .01);
    yPhase.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    yPhase.setPopupDisplayEnabled(false, false, this);
    yPhase.setValue(0.0);

    // this function adds the slider to the editor
    addAndMakeVisible(&xRate);
    addAndMakeVisible(&xScale);
    addAndMakeVisible(&xPhase);
    addAndMakeVisible(&yRate);
    addAndMakeVisible(&yScale);
    addAndMakeVisible(&yPhase);

    xRate.addListener(this);
    xScale.addListener(this);
    xPhase.addListener(this);
    yRate.addListener(this);
    yScale.addListener(this);
    yPhase.addListener(this);
}

TopoSynthAudioProcessorEditor::~TopoSynthAudioProcessorEditor()
{
}

//==============================================================================

void TopoSynthAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    //When a slider value changes, check which slider was changed
    //and update the correct processor variable accordingly.
    if (slider == &xRate)
        processor.topoParams.xRate = slider->getValue();
    else if (slider == &xScale)
        processor.topoParams.xScale = slider->getValue();
    else if (slider == &xPhase)
        processor.topoParams.xPhase = slider->getValue();
    else if (slider == &yRate)
        processor.topoParams.yRate = slider->getValue();
    else if (slider == &yScale)
        processor.topoParams.yScale = slider->getValue();
    else if (slider == &yPhase)
        processor.topoParams.yPhase = slider->getValue();
}

void TopoSynthAudioProcessorEditor::paint (Graphics& g)
{
    int x = 0;
    int y = getHeight() - 25;
    int width = 50;
    int height = 20;
    int spacing = width + 1;

    int visualizerX = 200;
    int visualizerY = 30;
    int visualizerW = img.getWidth();
    int visualizerH = img.getHeight();

    g.fillAll ((Colours::darkgrey).darker(1.0));
    g.setColour(Colours::white);

    g.setFont(20.0f);
    g.drawFittedText("X", x +1  , 10, spacing*3, height, Justification::centred, 1);
    g.drawFittedText("Y", x + 546 , 10, spacing*3, height, Justification::centred, 1);

    g.setFont (15.0f);

    g.drawFittedText("Rate", x +  0 * spacing, y, width, height, Justification::centred, 1);
    g.drawFittedText("Phase", x + 1 * spacing, y, width, height, Justification::centred, 1);
    g.drawFittedText("Scale", x + 2 * spacing, y, width, height, Justification::centred, 1);

    x += 545;
    g.drawFittedText("Rate", x + 0 * spacing, y, width, height, Justification::centred, 1);
    g.drawFittedText("Phase", x + 1 * spacing, y, width, height, Justification::centred, 1);
    g.drawFittedText("Scale", x + 2 * spacing, y, width, height, Justification::centred, 1);

    g.drawImageAt(img, visualizerX, visualizerY);
}

void TopoSynthAudioProcessorEditor::resized()
{
    int width = 25;
    int height = getHeight() - 70;
    int spacing = width + 25;

    int xBottom = 40;
    int xLeft = 15;
    int yBottom = 40;
    int yLeft = getWidth() - spacing*3 + 10;
    
    // sets the position and size of the slider with arguments (x, y, width, height)
    xRate.setBounds( xLeft + 0*spacing, xBottom, width, height);
    xPhase.setBounds(xLeft + 1*spacing, xBottom, width, height);
    xScale.setBounds(xLeft + 2*spacing, xBottom, width, height);

    yRate.setBounds( yLeft + 0 * spacing, yBottom, width, height);
    yPhase.setBounds(yLeft + 1 * spacing, yBottom, width, height);
    yScale.setBounds(yLeft + 2 * spacing, yBottom, width, height);
}
