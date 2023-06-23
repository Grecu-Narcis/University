#include "AdministratorService.h"


AdministratorService::AdministratorService(TutorialsRepository& tutorialsDatabase) : tutorialsList(tutorialsDatabase)
{
}


void AdministratorService::addTutorial(string tutorialTitle, string tutorialPresenter, string tutorialLink, int tutorialNumberOfLikes, int minutesDuration, int secondsDuration)
{
	Duration tutorialDuration(minutesDuration, secondsDuration);

	Tutorial tutorialToAdd(tutorialTitle, tutorialPresenter, tutorialLink, tutorialNumberOfLikes, tutorialDuration);

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

	this->tutorialsList.updateTutorial(tutorialToUpdate);
}


vector<Tutorial> AdministratorService::getAllTutorials()
{
	return this->tutorialsList.getAllTutorials();
}
