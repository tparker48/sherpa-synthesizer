#pragma once

#define X_SCALE_FULL 0
#define X_SCALE_MEDIUM 1
#define X_SCALE_SMALL 2

#define ABS_PATH "C:\\Users\\Tom\\Documents\\JUCE Projects\\theMountain\\ImageHandler\\"

#define EVEREST  "everest.csv"
#define IRON     "ironMountain.csv"
#define SADDLE   "southSaddle.csv"
#define LONGDARK "theLongDark.csv"

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