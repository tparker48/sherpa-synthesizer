#include "TopoDataLoader.h"

TopoDataLoader::TopoDataLoader(std::string csvName)
{
        std::ifstream file(csvName);
        std::string line;
        float temp;
        int i = 0;
        while (std::getline(file, line))
        {
            td.data.push_back({});
            std::stringstream iss(line);
            std::string val;
            while (std::getline(iss, val, ','))
            {
                std::stringstream convertor(val);
                convertor >> temp;
                td.data.at(i).push_back(temp/180.0);
            }
            i++;
        }

        td.width = td.data.size();
        td.height = (td.data[0]).size();
}

TopoData TopoDataLoader::getData()
{
    return td;
}