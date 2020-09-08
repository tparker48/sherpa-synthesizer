#pragma once

#define X_SCALE_FULL 0
#define X_SCALE_MEDIUM 1
#define X_SCALE_SMALL 2

#define EVEREST 0
#define IRON 1
#define SOUTH 2
#define LONGDARK 3


struct TopoOscParameters
{
    int sourceSelection;
    bool sourceLoading = false;

    float gain;

    float xScale, xPhase, xTuning;

    int xScaleMode;
    
    float yRate, yScale, yPhase;
    float filterCutoff, filterResonance;
};