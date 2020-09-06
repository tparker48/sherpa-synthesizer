// Reads CSV file and outputs a 2D integer array
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


struct TopoData 
{
    std::vector<std::vector<float>> data;
    int width = 0, height = 0;
};

class TopoDataLoader
{
public:

    TopoDataLoader(std::string csvName);

    TopoData getData();
private:
    TopoData td;
};