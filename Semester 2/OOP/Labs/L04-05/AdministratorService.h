#ifndef __ADMINISTRATOR_SERVICE_H__
#define __ADMINISTRATOR_SERVICE_H__

#include <string>

#include "Repository.h"
#include "Tutorial.h"

using std::string;

class AdministratorService
{
private:
	TutorialsRepository& tutorialsList;

public:
	AdministratorService(TutorialsRepository& appTutorialsRepository);

	void addTutorial(string tutorialTitle, string tutorialPresenter, string tutorialLink, int tutorialNumberOfLikes, int minutesDuration, int secondsDuration);
	void deleteTutorial(string tutorialTitle, string tutorialPresenter);
	void updateTutorial(string tutorialTitle, string tutorialPresenter, string tutorialLink, int tutorialNumberOfLikes, int minutesDuration, int secondsDuration);
	DynamicArray<Tutorial> getAllTutorials();
};

#endif