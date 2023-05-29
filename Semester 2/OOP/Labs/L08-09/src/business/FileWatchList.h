#ifndef __FILE_WATCH_LIST_H__
#define __FILE_WATCH_LIST_H__

#include "../infrastructure/MemoryRepository.h"

class FileWatchList : public MemoryRepository
{
protected:
	std::string pathToFile;

public:
	FileWatchList(const std::string& pathToFile);
	virtual void writeToFile() = 0;
	virtual void displayFile() = 0;

	virtual ~FileWatchList() {};
};

#endif