#include "TopoDataLoader.h"

TopoDataLoader::TopoDataLoader(int choice)
{
    Image image;

    switch (choice)
    {
    case EVEREST:
        image = EVEREST_FILE;
        break;

    case IRON:
        image = IRON_FILE;
        break;

    case SOUTH:
        image = SOUTH_FILE;
        break;

    case HIMALAYAS:
        image = HIMALAYAS_FILE;
        break;

    case TIAN:
        image = TIAN_FILE;
        break;

    case RELIEF_2:
        image = RELIEF_2_FILE;
        break;

    case VICTOIRE:
        image = VICTOIRE_FILE;
        break;

    case SIERRA:
        image = SIERRA_FILE;
        break;

    case MOON:
        image = MOON_FILE;
        break;
    }

    int w = image.getWidth();
    int h = image.getHeight();

    td.data.resize(w);
    for (int x = 0; x < w; x++)
    {
        td.data[x].resize(h);


        for (int y = 0; y < h; y++)
        {
            td.data[x][y] = 2.0f * (image.getPixelAt(x, y).getBrightness()) - 1.0f;
        }
    }

    td.width = w;
    td.height = h;
}

TopoData TopoDataLoader::getData()
{
    return td;
}