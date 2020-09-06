#include "SourceChanger.h"

void SourceChanger::changeSource(std::string fileName, TopoData* data, bool* done)
{
	threadExists = true;
	dataLoaderThread = new DataLoaderThread(fileName, data, done);
	dataLoaderThread->startThread();
}

void SourceChanger::stop()
{
	if (threadExists)
	{
		dataLoaderThread->stopThread(10);
		threadExists = false;
	}
}
