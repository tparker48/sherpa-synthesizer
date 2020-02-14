#include "TopoDataLoader.h"

TopoDataLoader::TopoDataLoader(std::string csvName)
{
    // TODO: construct td from csv
}

TopoDataLoader::~TopoDataLoader()
{
    if(td.data != NULL) delete[] td.data;
}

TopoData TopoDataLoader::getData()
{
    return td;
}