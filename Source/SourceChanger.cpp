#include "SourceChanger.h"

void SourceChanger::changeSource(std::string fileName, TopoData* data, bool* done)
{
	dataLoaderThread = new DataLoaderThread(fileName, data, done);
	dataLoaderThread->startThread();
}

void SourceChanger::stop()
{
	dataLoaderThread->stopThread(10);
}
