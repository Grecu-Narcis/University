#ifndef __ADMINISTRATOR_SERVICE_H__
#define __ADMINISTRATOR_SERVICE_H__

#include <string>
#include <vector>
#include <map>

#include "../infrastructure/MemoryRepository.h"
#include "../domain/Tutorial.h"

class AdministratorService
{
private:
	MemoryRepository& tutorialsList;

public:
	AdministratorService(MemoryRepository& tutorialsDatabase);

	void addTutorial(string tutorialTitle, string tutorialPresenter, string tutorialLink, int tutorialNumberOfLikes, int minutesDuration, int secondsDuration);
	void deleteTutorial(string tutorialTitle, string tutorialPresenter);
	void updateTutorial(string tutorialTitle, string tutorialPresenter, string tutorialLink, int tutorialNumberOfLikes, int minutesDuration, int secondsDuration);
	std::vector<Tutorial> getAllTutorials();
	std::map<string, int> getTutorialsCountByPresenter();
};

#endif