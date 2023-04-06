#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__

#include <vector>
#include "Tutorial.h"

using std::vector;

class TutorialsRepository
{
private:
	vector<Tutorial> tutorialsList;
	
public:
	void addSampleData();
	int getSize();
	int findPosition(string tutorialTitle, string tutorialPresenter);
	void addTutorial(Tutorial tutorialToAdd);
	void deleteTutorial(string tutorialTitle, string tutorialPresenter);
	void updateTutorial(Tutorial tutorialToUpdate);
	Tutorial& getTutorialAtIndex(int index);
	vector<Tutorial> getAllTutorials();
};

#endif