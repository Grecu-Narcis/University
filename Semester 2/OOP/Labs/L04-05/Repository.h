#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__

#include "DynamicArray.h"
#include "Tutorial.h"

class TutorialsRepository
{
private:
	DynamicArray<Tutorial> tutorialsList;
	
public:
	void addSampleData();
	int getSize();
	int findPosition(string tutorialTitle, string tutorialPresenter);
	void addTutorial(Tutorial tutorialToAdd);
	void deleteTutorial(string tutorialTitle, string tutorialPresenter);
	void updateTutorial(Tutorial tutorialToUpdate);
	Tutorial& getTutorialAtIndex(int index);
	DynamicArray<Tutorial> getAllTutorials();
};

#endif