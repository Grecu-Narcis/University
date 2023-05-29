#include "AdministratorService.h"
#include "../domain/TutorialValidator.h"


AdministratorService::AdministratorService(MemoryRepository& tutorialsDatabase) : tutorialsList(tutorialsDatabase)
{
}


void AdministratorService::addTutorial(string tutorialTitle, string tutorialPresenter, string tutorialLink, int tutorialNumberOfLikes, int minutesDuration, int secondsDuration)
{
	Duration tutorialDuration(minutesDuration, secondsDuration);

	Tutorial tutorialToAdd(tutorialTitle, tutorialPresenter, tutorialLink, tutorialNumberOfLikes, tutorialDuration);

	TutorialValidator::validate(tutorialToAdd);

	this->tutorialsList.addTutorial(tutorialToAdd);
}


void AdministratorService::deleteTutorial(string tutorialTitle, string tutorialPresenter)
{
	this->tutorialsList.deleteTutorial(tutorialTitle, tutorialPresenter);
}


void AdministratorService::updateTutorial(string tutorialTitle, string tutorialPresenter, string tutorialLink, int tutorialNumberOfLikes, int minutesDuration, int secondsDuration)
{
	Duration tutorialDuration(minutesDuration, secondsDuration);

	Tutorial tutorialToUpdate(tutorialTitle, tutorialPresenter, tutorialLink, tutorialNumberOfLikes, tutorialDuration);

	TutorialValidator::validate(tutorialToUpdate);

	this->tutorialsList.updateTutorial(tutorialToUpdate);
}


vector<Tutorial> AdministratorService::getAllTutorials()
{
	return this->tutorialsList.getAllTutorials();
}

std::map<string, int> AdministratorService::getTutorialsCountByPresenter()
{
	std::map<string, int> tutorialsNumberOfPresenter;

	std::vector<Tutorial> allTutorials = getAllTutorials();

	for (auto tutorial : allTutorials)
		if (tutorialsNumberOfPresenter.find(tutorial.getPresenter()) == tutorialsNumberOfPresenter.end())
			tutorialsNumberOfPresenter.insert(std::make_pair(tutorial.getPresenter(), 1));

		else
			tutorialsNumberOfPresenter[tutorial.getPresenter()]++;

	return tutorialsNumberOfPresenter;
}
