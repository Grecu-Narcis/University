#include "UserService.h"


UserService::UserService(TutorialsRepository& tutorialsDatabase) : tutorialsDatabase(tutorialsDatabase)
{ 
}


DynamicArray<Tutorial> UserService::getTutorialsWithPresenter(string givenPresenter)
{
    DynamicArray<Tutorial> tutorialsInDatabase = this->getAllTutorialsFromDatabase();
    if (givenPresenter == "")
        return tutorialsInDatabase;

    DynamicArray<Tutorial> tutorialsWithGivenPresenter;

    for (int i = 0; i < tutorialsInDatabase.getSize(); i++)
        if (tutorialsInDatabase[i].getPresenter() == givenPresenter)
            tutorialsWithGivenPresenter.pushBack(tutorialsInDatabase[i]);

    return tutorialsWithGivenPresenter;
}


DynamicArray<Tutorial> UserService::getAllTutorialsFromDatabase()
{
    return this->tutorialsDatabase.getAllTutorials();
}


void UserService::addTutorialToWatchList(Tutorial tutorialToAdd)
{
    this->userWatchList.addTutorial(tutorialToAdd);
}


DynamicArray<Tutorial> UserService::getWatchList()
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
