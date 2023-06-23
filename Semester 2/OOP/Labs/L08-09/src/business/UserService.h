#ifndef __USER_SERVICE_H__
#define __USER_SERVICE_H__

#include <vector>

#include "../infrastructure/MemoryRepository.h"
#include "FileWatchList.h"


using std::vector;

class UserService
{
private:
	MemoryRepository& tutorialsDatabase;
	FileWatchList* userWatchList;


public:
	UserService(MemoryRepository& tutorialsDatabase, FileWatchList* userWatchList);
	vector<Tutorial> getTutorialsWithPresenter(string givenPresenter);
	vector<Tutorial> getAllTutorialsFromDatabase();
	void addTutorialToWatchList(Tutorial tutorialToAdd);
	vector<Tutorial> getWatchList();
	void likeTutorial(Tutorial likedTutorial);
	void deleteTutorialFromWatchList(string tutorialTitle, string tutorialPresenter, bool likedTutorial);
	void openWatchList();
	void setCSVFileWatchList();
	void setHTMLFileWatchList();
};

#endif
