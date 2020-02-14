// Reads CSV file and outputs a 2D integer array
#include <string>

struct TopoData 
{
    int* data;
    int width, height;
};

class TopoDataLoader
{
public:

    TopoDataLoader(std::string csvName);
    ~TopoDataLoader();

    TopoData getData();
private:
    TopoData td;
};