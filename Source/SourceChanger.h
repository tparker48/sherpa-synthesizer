#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TopoDataLoader.h"
#include <string>

class SourceChanger {
public:
	void changeSource(std::string fileName, TopoData* data, bool* done);
	void stop();

private:

	class DataLoaderThread: public Thread {
	public:
		DataLoaderThread(std::string fileName, TopoData* data, bool* done) : Thread("Loading...") 
		{ 
			this->fileName = fileName;
			dataPtr = data;
			this->done = done;
		}

		void run() override
		{
			TopoDataLoader t(fileName);
			*dataPtr = t.getData();
			*done = true;

			while (!threadShouldExit())
			{
				sleep(15);
			}
		}

	private:
		std::string fileName;
		TopoData* dataPtr;
		bool* done;
	};

	DataLoaderThread* dataLoaderThread;

};