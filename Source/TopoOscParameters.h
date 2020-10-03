#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#define X_SCALE_FULL 3
#define X_SCALE_MEDIUM 2
#define X_SCALE_SMALL 1

#define FILTER_BPF 2
#define FILTER_LPF 1

#define NUM_SOURCES 9

#define EVEREST    0
#define IRON       1
#define SOUTH      2
#define HIMALAYAS  3
#define TIAN       4
#define RELIEF_2   5
#define VICTOIRE   6
#define MOON       7
#define SIERRA     8

#define EVEREST_FILE    ImageCache::getFromMemory(BinaryData::everest_jpg, BinaryData::everest_jpgSize)
#define IRON_FILE       ImageCache::getFromMemory(BinaryData::ironMountain_jpg, BinaryData::ironMountain_jpgSize)
#define SOUTH_FILE      ImageCache::getFromMemory(BinaryData::southSaddle_jpg, BinaryData::southSaddle_jpgSize)
#define HIMALAYAS_FILE  ImageCache::getFromMemory(BinaryData::himalayas_jpg, BinaryData::himalayas_jpgSize)
#define TIAN_FILE       ImageCache::getFromMemory(BinaryData::tianShan_png, BinaryData::tianShan_pngSize)
#define RELIEF_2_FILE   ImageCache::getFromMemory(BinaryData::unknownRelief21_jpg, BinaryData::unknownRelief21_jpgSize)
#define VICTOIRE_FILE    ImageCache::getFromMemory(BinaryData::saintevictoire_jpg, BinaryData::saintevictoire_jpgSize)
//#define MOON_FILE       ImageCache::getFromMemory(BinaryData::moon_jpg, BinaryData::moon_jpgSize)
#define MOON_FILE     ImageCache::getFromMemory(BinaryData::moon_jpg, BinaryData::moon_jpgSize)
#define SIERRA_FILE     ImageCache::getFromMemory(BinaryData::sierra_jpg, BinaryData::sierra_jpgSize)


struct TopoOscParameters
{
    int sourceSelection;
    float gain;
    double xScale, xPhase, xTuning;
    int xScaleMode;
    double yRate, yScale, yPhase;

    AudioProcessorValueTreeState* vts;
};