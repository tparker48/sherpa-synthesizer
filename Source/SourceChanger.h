#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TopoDataLoader.h"
#include <string>

class SourceChanger {
public:
	void changeSource(std::string fileName, TopoData* data, bool* stillWorking);
	void stop();

private:

	class DataLoaderThread: public Thread {
	public:
		DataLoaderThread(std::string fileName, TopoData* data, bool* stillWorking) : Thread("Loading...")
		{ 
			this->fileName = fileName;
			dataPtr = data;
			this->stillWorking = stillWorking;
		}

		void run() override
		{
			TopoDataLoader t(fileName);
			*dataPtr = t.getData();
			*stillWorking = false;
		}

	private:
		std::string fileName;
		TopoData* dataPtr;
		bool* stillWorking;
	};

	DataLoaderThread* dataLoaderThread;
	bool threadExists = false;

};