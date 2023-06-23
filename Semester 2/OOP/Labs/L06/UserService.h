#ifndef __USER_SERVICE_H__
#define __USER_SERVICE_H__

#include <vector>

#include "Repository.h"

using std::vector;

class UserService
{
private:
	TutorialsRepository& tutorialsDatabase;
	TutorialsRepository userWatchList;

public:
	UserService(TutorialsRepository& tutorialsDatabase);
	vector<Tutorial> getTutorialsWithPresenter(string givenPresenter);
	vector<Tutorial> getAllTutorialsFromDatabase();
	void addTutorialToWatchList(Tutorial tutorialToAdd);
	vector<Tutorial> getWatchList();
	void likeTutorial(Tutorial& likedTutorial);
	void deleteTutorialFromWatchList(string tutorialTitle, string tutorialPresenter, bool likedTutorial);
};

#endif
