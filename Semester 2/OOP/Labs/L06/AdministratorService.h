#ifndef __ADMINISTRATOR_SERVICE_H__
#define __ADMINISTRATOR_SERVICE_H__

#include <string>
#include <vector>

#include "Repository.h"
#include "Tutorial.h"

using std::string;
using std::vector;

class AdministratorService
{
private:
	TutorialsRepository& tutorialsList;

public:
	AdministratorService(TutorialsRepository& tutorialsDatabase);

	void addTutorial(string tutorialTitle, string tutorialPresenter, string tutorialLink, int tutorialNumberOfLikes, int minutesDuration, int secondsDuration);
	void deleteTutorial(string tutorialTitle, string tutorialPresenter);
	void updateTutorial(string tutorialTitle, string tutorialPresenter, string tutorialLink, int tutorialNumberOfLikes, int minutesDuration, int secondsDuration);
	vector<Tutorial> getAllTutorials();
};

#endif