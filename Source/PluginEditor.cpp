#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TopoSynthAudioProcessorEditor::TopoSynthAudioProcessorEditor (TopoSynthAudioProcessor& p, AudioProcessorValueTreeState& valTreeState)
    : AudioProcessorEditor (&p), processor (p), vts(valTreeState)
{
    double ratio = 7.0 / 3.5;
    setResizeLimits(400, 400 / ratio, 1600, 1600 / ratio);
    getConstrainer()->setFixedAspectRatio(ratio);
    setSize(1000.0, 1000.0 / ratio);

    vstLogo = ImageCache::getFromMemory(BinaryData::VST_Compatible_Logo_Steinberg_with_TM_png, BinaryData::VST_Compatible_Logo_Steinberg_with_TM_pngSize);

    Grey = Colour(60, 60, 60);

    // default
    Colors[0][0] = Colour(214, 40, 40);
    Colors[0][1] = Colour(247, 127, 0);
    Colors[0][2] = Colour(252, 191, 73);
    Colors[0][3] = Colour(95, 198, 148);
    
    // altI
    Colors[1][0] = Colour(140, 126, 182);
    Colors[1][1] = Colour(192, 108, 132);
    Colors[1][2] = Colour(246, 114, 128);
    Colors[1][3] = Colour(248, 177, 149);

    // altII
    //Colors[2][0] = Colour(129, 108, 154);
    //Colors[2][1] = Colour(177, 92, 111);
    //Colors[2][2] = Colour(236, 114, 99);
    //Colors[2][3] = Colour(254, 190, 126);

    scheme = 0;
    numColorSchemes = 2;


    // color scheme state
    addAndMakeVisible(colorChoice);
    colorChoice.addItem("I", 1);
    colorChoice.addItem("II", 2);
    colorChoice.addItem("III", 3);
    colorChoice.onChange = [this] {colorsChanged(); };
    colorChoiceP.reset(new ComboBoxAttachment(vts, "colorScheme", colorChoice));


    divisionWidthRatio = 0.014;
    divisionHeightRatio = 0.028;
    smallSectionWidthRatio = 0.185;
    largeSectionWidthRatio = 0.28;
    sectionHeightRatio = 0.94;
   
    this->addMouseListener(new MouseListener, false);
    
    customSlider = new SliderLookAndFeel(Grey, Colours::white);
    customDial = new DialLookAndFeel(Grey, Colours::white);
    customButton = new ButtonLookAndFeel(Grey, Colours::white);
    customToggleButton = new ToggleButtonLookAndFeel(Grey, Colours::white);
    customCloseButton = new CloseButtonLookAndFeel(Grey, Colours::white);
    customRightButton = new NextButtonLookAndFeel(true, Grey, Colours::white);
    customLeftButton = new NextButtonLookAndFeel(false, Grey, Colours::white);

    getLookAndFeel().setColour(PopupMenu::ColourIds::backgroundColourId, Grey);
    getLookAndFeel().setColour(PopupMenu::ColourIds::highlightedBackgroundColourId, (Colours::darkgrey));
    getLookAndFeel().setColour(PopupMenu::ColourIds::textColourId, (Colours::white));
    getLookAndFeel().setColour(PopupMenu::ColourIds::highlightedTextColourId, (Colours::white));
    sourceSelect.setColour(ComboBox::ColourIds::backgroundColourId, Grey);
    sourceSelect.setColour(ComboBox::ColourIds::textColourId, (Colours::white));
    sourceSelect.setColour(ComboBox::ColourIds::outlineColourId, Grey);
    

    // Source Select Combo Box
    addAndMakeVisible(sourceSelect);

    sourceSelect.addItem("Everest", 1);
    sourceSelect.addItem("Iron Mountain", 2);
    sourceSelect.addItem("South Saddle", 3);
    sourceSelect.addItem("Himalayas", 4);
    sourceSelect.addItem("Tian Shan", 5);
    sourceSelect.addItem("Relief", 6);
    sourceSelect.addItem("Sante-Victoire", 7);
    sourceSelect.addItem("Moon", 8);
    sourceSelect.addItem("Sierras", 9);

    sourceSelect.onChange = [this] { sourceChanged(); };
    sourceSelectionP.reset(new ComboBoxAttachment(vts, "sourceSelection", sourceSelect));
    
    // Gain Knob
    addAndMakeVisible(&gain);
    gain.setSliderStyle(Slider::LinearBarVertical);
    gainP.reset(new SliderAttachment(vts, "gain", gain));
    gain.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    gain.setPopupDisplayEnabled(false, false, this);
    gain.setLookAndFeel(customDial);
    gain.setVelocityBasedMode(true);


    // X Phase Slider
    addAndMakeVisible(&xPhase);
    xPhaseP.reset(new SliderAttachment(vts, "xPhase", xPhase));
    xPhase.setSliderStyle(Slider::LinearBarVertical);
    xPhase.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    xPhase.setPopupDisplayEnabled(false, false, this);
    xPhase.setLookAndFeel(customSlider);

    // X Scale Slider
    addAndMakeVisible(&xScale);
    xScaleP.reset(new SliderAttachment(vts, "xScale", xScale));
    xScale.setSliderStyle(Slider::LinearBarVertical);
    xScale.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    xScale.setPopupDisplayEnabled(false, false, this);
    xScale.setLookAndFeel(customSlider);

    // X Tuning Dial
    addAndMakeVisible(&xTuning);
    xTuningP.reset(new SliderAttachment(vts, "xTuning", xTuning));
    xTuning.setSliderStyle(Slider::LinearBarVertical);
    xTuning.setTextBoxStyle(Slider::NoTextBox, false, 70, 30);
    xTuning.setPopupDisplayEnabled(false, false, this);
    xTuning.setLookAndFeel(customDial);
    xTuning.setVelocityBasedMode(true);
    xTuning.setDoubleClickReturnValue(true, 0.5);

    // X Scale Buttons
    addAndMakeVisible(buttonState);
    buttonState.addItem("small", 1);
    buttonState.addItem("medium", 2);
    buttonState.addItem("full", 3);
    buttonState.onChange = [this] {buttonStateChanged(); };
    buttonStateP.reset(new ComboBoxAttachment(vts, "xScaleRange", buttonState));

    // Full
    addAndMakeVisible(&xScaleFull);
    xScaleFull.onClick = [this] { updateToggleState(X_SCALE_FULL);   };
    xScaleFull.setRadioGroupId(1001);
    xScaleFull.setClickingTogglesState(true);
    xScaleFull.setLookAndFeel(customButton);

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
    yPhaseP.reset(new SliderAttachment(vts, "yPhase", yPhase));
    yPhase.setSliderStyle(Slider::LinearBarVertical);
    yPhase.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    yPhase.setPopupDisplayEnabled(false, false, this);
    yPhase.setLookAndFeel(customSlider);

    // Y Rate
    addAndMakeVisible(&yRate);
    yRateP.reset(new SliderAttachment(vts, "yRate", yRate));
    yRate.setSliderStyle(Slider::LinearBarVertical);
    yRate.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    yRate.setPopupDisplayEnabled(false, false, this);
    yRate.setLookAndFeel(customSlider);

    // Y Scale
    addAndMakeVisible(&yScale);
    yScaleP.reset(new SliderAttachment(vts, "yScale", yScale));
    yScale.setSliderStyle(Slider::LinearBarVertical);
    yScale.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    yScale.setPopupDisplayEnabled(false, false, this);
    yScale.setLookAndFeel(customSlider);

    // "I / II"
    addAndMakeVisible(&filterTypeToggle);
    //filterTypeToggle.setClickingTogglesState(true);
    filterTypeToggle.setLookAndFeel(customToggleButton);
    filterTypeP.reset(new ButtonAttachment(vts, "filterType", filterTypeToggle));

    // Filter Cutoff
    addAndMakeVisible(&filterCutoff);
    filterCutoffP.reset(new SliderAttachment(vts, "filterCutoff", filterCutoff));
    filterCutoff.setSliderStyle(Slider::LinearBarVertical);
    filterCutoff.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    filterCutoff.setPopupDisplayEnabled(false, false, this);
    filterCutoff.setLookAndFeel(customDial);
    filterCutoff.setVelocityBasedMode(true);

    // Filter Resonance
    addAndMakeVisible(&filterResonance);
    filterResonanceP.reset(new SliderAttachment(vts, "filterResonance", filterResonance));
    filterResonance.setSliderStyle(Slider::LinearBarVertical);
    filterResonance.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    filterResonance.setPopupDisplayEnabled(false, false, this);
    filterResonance.setLookAndFeel(customDial);
    filterResonance.setVelocityBasedMode(true);


    gain.setVelocityModeParameters(1.0, 0, gainSensitivity, false);
    xTuning.setVelocityModeParameters(1.0, 0, xTuningSensitivity, false);
    filterCutoff.setVelocityModeParameters(1.0, 0, filterCutoffSensitivity, false);
    filterResonance.setVelocityModeParameters(1.0, 0, filterResonanceSensitivity, false);

    PopupMenu::Item about;
    about.itemID = 1;
    about.text = "about";
    about.action = [this] {openAboutMenu(); };
    rightClickMenu.addItem(about);

    initializeAboutMenuUI();

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
    filterTypeToggle.setLookAndFeel(nullptr);

    leftButton.setLookAndFeel(nullptr);
    rightButton.setLookAndFeel(nullptr);
    closeAboutMenuButton.setLookAndFeel(nullptr);
    
    delete customSlider;
    delete customDial;
    delete customButton;
    delete customToggleButton;
    delete customCloseButton;
}

//==============================================================================
void TopoSynthAudioProcessorEditor::paint (Graphics& g)
{
    // Draw each background pannel

    g.fillAll(Grey);

    if (aboutMenuOpen)
    {
        paintAboutMenu(g);
        return;
    }

    float x = divisionW;
    float y = divisionH;

    g.setColour(Colors[scheme][0]);
    g.fillRect(x, y , smallSectionW, sectionH);

    x += divisionW + smallSectionW ;


    g.setColour(Colors[scheme][1]);
    g.fillRect(x, y, largeSectionW, sectionH);

    x += divisionW + largeSectionW;


    g.setColour(Colors[scheme][2]);
    g.fillRect(x, y, largeSectionW, sectionH);

    x += divisionW + largeSectionW;


    g.setColour(Colors[scheme][3]);
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

    c = &filterTypeToggle;
    x = c->getX() + (c->getWidth() / 2) - textW / 2;
    y = c->getBottom() -0.5f * buttonLabelPaddingFactor;;
    g.drawFittedText("a   b", x, y, textW, textH, Justification::centred, 1);
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
    
    // Colors[scheme][0] Pannel 
    int x = divisionW;
    int y = divisionH;

    comboX = x + comboXPadding;
    comboY = y + comboYPadding;
    sourceSelect.setBounds(x + comboXPadding ,y + comboYPadding, comboW, comboH);

    int gainXPadding = (smallSectionW - largeDialSize) / 2.0;
    int gainYPadding = sectionH * .55;
    gain.setBounds(x + gainXPadding, y + gainYPadding, largeDialSize, largeDialSize);

    // Colors[scheme][1] Pannel
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
    
    // Colors[scheme][2] Pannel
    x += divisionW + largeSectionW;
    sliderXPadding = sliderXPadding * 1.25;

    yPhase.setBounds(x + sliderXPadding, y + (sectionH - sliderH) / 2, sliderW, sliderH);

    int yRateXPadding = (largeSectionW - sliderW) / 2;
    yRate.setBounds(x + yRateXPadding, y + (sectionH - sliderH) / 2, sliderW, sliderH);

    int yScaleXPadding = largeSectionW - sliderW - sliderXPadding;
    yScale.setBounds(x + yScaleXPadding, y + (sectionH - sliderH) / 2, sliderW, sliderH);

    // Colors[scheme][3] Pannel
    x += divisionW + largeSectionW;


    int toggleH = buttonSize * .6f;
    int toggleW = buttonSize * 1.6f;
    int fButtonYPadding = sectionH * .8325;
    int fButtonXSpacing = buttonSize * 1.75f;
    int fButtonXPadding = (smallSectionW - toggleW)/2.0f;
   
    filterTypeToggle.setBounds(x + fButtonXPadding, y + fButtonYPadding, toggleW, toggleH);

    int cutoffXPadding = (smallSectionW - largeDialSize) / 2;
    int cutoffYPadding = sectionH * .15;
    filterCutoff.setBounds(x + cutoffXPadding, y + cutoffYPadding, largeDialSize, largeDialSize);

    int resonanceXPadding = (smallSectionW - smallDialSize) / 2;
    int resonanceYPadding = sectionH * .51;
    filterResonance.setBounds(x + resonanceXPadding, y + resonanceYPadding, smallDialSize, smallDialSize);

    resizedAboutMenu();
}


void TopoSynthAudioProcessorEditor::sourceChanged()
{
    int choice = sourceSelect.getSelectedId() - 1;
    processor.topoSynth.changeTopoSource(choice);
}

void TopoSynthAudioProcessorEditor::updateToggleState(int mode)
{
    buttonState.setSelectedId(mode);
}

void TopoSynthAudioProcessorEditor::buttonStateChanged()
{
    int active = buttonState.getSelectedId();
    xScaleFull.setToggleState( active == 3 , NotificationType::dontSendNotification);
    xScaleMedium.setToggleState(active == 2, NotificationType::dontSendNotification);
    xScaleSmall.setToggleState(active == 1, NotificationType::dontSendNotification);
}

void TopoSynthAudioProcessorEditor::filterToggle()
{
    filterTypeToggle.setToggleState(!filterTypeToggle.getToggleState(), NotificationType::dontSendNotification);
}



void TopoSynthAudioProcessorEditor::initializeAboutMenuUI()
{
    addAndMakeVisible(&closeAboutMenuButton);
    closeAboutMenuButton.onClick = [this] { closeAboutMenu(); };
    closeAboutMenuButton.setLookAndFeel(customCloseButton);
    closeAboutMenuButton.setVisible(false);

    addAndMakeVisible(&rightButton);
    rightButton.onClick = [this] { cycleColorScheme(1); };
    rightButton.setLookAndFeel(customRightButton);
    rightButton.setVisible(false);

    addAndMakeVisible(&leftButton);
    leftButton.onClick = [this] { cycleColorScheme(-1); };
    leftButton.setLookAndFeel(customLeftButton);
    leftButton.setVisible(false);
}


void TopoSynthAudioProcessorEditor::mouseUp(const MouseEvent& event)
{
    if (event.mods.testFlags(ModifierKeys::rightButtonModifier))
    {
        rightClickMenu.show();
    }
}

void TopoSynthAudioProcessorEditor::openAboutMenu()
{
    aboutMenuOpen = true;
    setAboutVisibility(true);
    repaint();
}

void TopoSynthAudioProcessorEditor::closeAboutMenu()
{
    aboutMenuOpen = false;
    setAboutVisibility(false);
    repaint();
}

void TopoSynthAudioProcessorEditor::paintAboutMenu(Graphics& g)
{
    int w = getWidth();
    int h = getHeight();

    // Dark grey background
    g.setColour(Grey.darker(0.85f));
    g.fillRect(divisionW, divisionH, w - 2*divisionW, h - 2*divisionH);

    // color strip
    int stripY = h * .3f;
    int stripH = divisionH * 1.2f;
    Rectangle<int> colorStrip(divisionW, stripY, w - 2 * divisionW, stripH);

    g.setColour(Colors[scheme][3]);
    g.fillRect(colorStrip);
    colorStrip.setCentre(colorStrip.getCentreX(), colorStrip.getCentreY() + stripH);

    g.setColour(Colors[scheme][2]);
    g.fillRect(colorStrip);
    colorStrip.setCentre(colorStrip.getCentreX(), colorStrip.getCentreY() + stripH);

    g.setColour(Colors[scheme][1]);
    g.fillRect(colorStrip);
    colorStrip.setCentre(colorStrip.getCentreX(), colorStrip.getCentreY() + stripH);

    g.setColour(Colors[scheme][0]);
    g.fillRect(colorStrip);
    colorStrip.setCentre(colorStrip.getCentreX(), colorStrip.getCentreY() + stripH);

    // Steinberg VST logo
    int vstW = w * 0.18f;
    int vstH = h * 0.26f;
    Rectangle<float> vstArea((w - vstW)/2.0f, h - vstH - (2*divisionH),vstW,vstH);
    g.drawImage(vstLogo, vstArea);
}

void TopoSynthAudioProcessorEditor::resizedAboutMenu()
{
    int w = getWidth();
    int h = getHeight();

    int buttonSize = 1.5f * divisionW;
    int closeX = w - (2 * divisionW) - buttonSize;
    int closeY = (2 * divisionH);

    closeAboutMenuButton.setBounds(closeX,closeY,buttonSize,buttonSize);

    buttonSize = divisionW * 2.0f;
    int y = h * 0.475f;
    int spacing = divisionW * 2.0f;
    int x = (w - (2.0f * buttonSize) - spacing) / 2.0f;

    leftButton.setBounds(x, y, buttonSize, buttonSize);
    x += spacing + buttonSize;
    rightButton.setBounds(x, y, buttonSize, buttonSize);
}

void TopoSynthAudioProcessorEditor::setAboutVisibility(bool aboutVisible)
{
    sourceSelect.setVisible(!aboutVisible);
    gain.setVisible(!aboutVisible);
    xTuning.setVisible(!aboutVisible);
    xScale.setVisible(!aboutVisible);
    xPhase.setVisible(!aboutVisible);
    yRate.setVisible(!aboutVisible);
    yScale.setVisible(!aboutVisible);
    yPhase.setVisible(!aboutVisible);
    filterCutoff.setVisible(!aboutVisible);
    filterResonance.setVisible(!aboutVisible);
    xScaleFull.setVisible(!aboutVisible);
    xScaleMedium.setVisible(!aboutVisible);
    xScaleSmall.setVisible(!aboutVisible);
    filterTypeToggle.setVisible(!aboutVisible);

    closeAboutMenuButton.setVisible(aboutVisible);
    rightButton.setVisible(aboutVisible);
    leftButton.setVisible(aboutVisible);
}

void TopoSynthAudioProcessorEditor::cycleColorScheme(int dir)
{
    scheme += dir;
    if (scheme < 0)
    {
        scheme = numColorSchemes - 1;
    }
    scheme %= numColorSchemes;

    colorChoice.setSelectedId(scheme + 1);

}

void TopoSynthAudioProcessorEditor::colorsChanged()
{
    scheme = colorChoice.getSelectedId() - 1;
    repaint();
}