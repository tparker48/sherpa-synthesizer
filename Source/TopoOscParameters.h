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
    int xScaleMode;
    float xScale, xPhase;
    float yRate, yScale, yPhase;
    float filterCutoff, filterResonance;

    int sourceSelection;
    bool sourceLoading = false;
};