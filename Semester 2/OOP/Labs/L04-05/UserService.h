#ifndef __USER_SERVICE_H__
#define __USER_SERVICE_H__

#include "Repository.h"
#include "DynamicArray.h"

class UserService
{
private:
	TutorialsRepository& tutorialsDatabase;
	TutorialsRepository userWatchList;

public:
	UserService(TutorialsRepository& tutorialsDatabase);
	DynamicArray<Tutorial> getTutorialsWithPresenter(string givenPresenter);
	DynamicArray<Tutorial> getAllTutorialsFromDatabase();
	void addTutorialToWatchList(Tutorial tutorialToAdd);
	DynamicArray<Tutorial> getWatchList();
	void likeTutorial(Tutorial& likedTutorial);
	void deleteTutorialFromWatchList(string tutorialTitle, string tutorialPresenter, bool likedTutorial);
};

#endif
