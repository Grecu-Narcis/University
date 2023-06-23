#include "UserService.h"

#include <algorithm>

using namespace std;


UserService::UserService(TutorialsRepository& tutorialsDatabase) : tutorialsDatabase(tutorialsDatabase)
{
    this->tutorialsDatabase = tutorialsDatabase;
}


vector<Tutorial> UserService::getTutorialsWithPresenter(string givenPresenter)
{
    vector<Tutorial> tutorialsInDatabase = this->getAllTutorialsFromDatabase();
    if (givenPresenter == "")
        return tutorialsInDatabase;

    int numberOfTutorialsWithGivenPresenter =
        count_if(tutorialsInDatabase.begin(),
            tutorialsInDatabase.end(),
            [givenPresenter](Tutorial tutorialToCheck)
            {
                return tutorialToCheck.getPresenter() == givenPresenter;
            });

    vector<Tutorial> tutorialsWithGivenPresenter(numberOfTutorialsWithGivenPresenter);

    copy_if(tutorialsInDatabase.begin(),
        tutorialsInDatabase.end(),
        tutorialsWithGivenPresenter.begin(),
        [givenPresenter](Tutorial tutorialToCheck)
        {return tutorialToCheck.getPresenter() == givenPresenter; }
    );

    return tutorialsWithGivenPresenter;
}


vector<Tutorial> UserService::getAllTutorialsFromDatabase()
{
    return this->tutorialsDatabase.getAllTutorials();
}


void UserService::addTutorialToWatchList(Tutorial tutorialToAdd)
{
    this->userWatchList.addTutorial(tutorialToAdd);
}


vector<Tutorial> UserService::getWatchList()
{
    return this->userWatchList.getAllTutorials();
}

void UserService::likeTutorial(Tutorial& likedTutorial)
{
    likedTutorial.setNumberOfLikes(likedTutorial.getNumberOfLikes() + 1);
}

void UserService::deleteTutorialFromWatchList(string tutorialTitle, string tutorialPresenter, bool likedTutorial)
{
    int tutorialIndex = this->tutorialsDatabase.findPosition(tutorialTitle, tutorialPresenter);

    if (tutorialIndex == -1)
        throw std::exception("Tutorial not in watch list!");

    if (likedTutorial)
        this->likeTutorial(this->tutorialsDatabase.getTutorialAtIndex(tutorialIndex));

    this->userWatchList.deleteTutorial(tutorialTitle, tutorialPresenter);
}
