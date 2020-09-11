#include "TopoDataLoader.h"

TopoDataLoader::TopoDataLoader(int choice)
{
    Image image;

    switch (choice)
    {
    case EVEREST:
        image = ImageCache::getFromMemory(BinaryData::everest_jpg, BinaryData::everest_jpgSize);
        break;

    case IRON:
        image = ImageCache::getFromMemory(BinaryData::ironMountain_jpg, BinaryData::ironMountain_jpgSize);
        break;

    case SOUTH:
        image = ImageCache::getFromMemory(BinaryData::southSaddle_jpg, BinaryData::southSaddle_jpgSize);
        break;

    case LONGDARK:
        image = ImageCache::getFromMemory(BinaryData::theLongDark_jpg, BinaryData::theLongDark_jpgSize);
        break;

    case CASCADES:
        image = ImageCache::getFromMemory(BinaryData::cascade_jpg, BinaryData::cascade_jpgSize);
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