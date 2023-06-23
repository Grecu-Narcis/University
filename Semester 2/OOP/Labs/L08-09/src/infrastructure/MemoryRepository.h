#ifndef __MEMORY_REPOSITORY_H__
#define __MEMORY_REPOSITORY_H__

#include <vector>
#include "../domain/Tutorial.h"

using std::vector;
using std::string;

class MemoryRepository
{
protected:
	vector<Tutorial> tutorialsList;

public:
	MemoryRepository();

	virtual int getSize();
	virtual int findPosition(string tutorialTitle, string tutorialPresenter);
	virtual void addTutorial(Tutorial tutorialToAdd);
	virtual void deleteTutorial(string tutorialTitle, string tutorialPresenter);
	virtual void updateTutorial(Tutorial tutorialToUpdate);
	virtual Tutorial getTutorialAtIndex(int index);
	virtual vector<Tutorial> getAllTutorials();
	void addSampleData();

	virtual ~MemoryRepository() {};
};

#endif