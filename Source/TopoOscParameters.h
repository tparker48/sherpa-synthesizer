#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#define X_SCALE_FULL 3
#define X_SCALE_MEDIUM 2
#define X_SCALE_SMALL 1

#define EVEREST 0
#define IRON 1
#define SOUTH 2
#define CASCADES 3
#define LONGDARK 4

#define NUM_SOURCES 5


struct TopoOscParameters
{
    int sourceSelection;
    float gain;
    float xScale, xPhase, xTuning;
    int xScaleMode;
    float yRate, yScale, yPhase;

    AudioProcessorValueTreeState* vts;
};