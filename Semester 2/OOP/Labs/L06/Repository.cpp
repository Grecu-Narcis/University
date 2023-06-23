#include "Repository.h"

#include <stdexcept>

using namespace std;


void TutorialsRepository::addSampleData()
{
        Tutorial demoTutorial1("Learn C++", "some indian guy", "www.youtube.com", 1000, Duration(30, 15));
        Tutorial demoTutorial2("Make C++ easy", "Learn Together", "www.youtube.com", 657, Duration(120, 0));
        Tutorial demoTutorial3("Intro in C++", "Tech with Tim", "www.youtube.com", 2314, Duration(45, 35));
        Tutorial demoTutorial4("C++ for beginners", "Grecu Narcis", "www.freecodecamp.com", 1000, Duration(72, 55));
        Tutorial demoTutorial5("Advanced C++", "Bocicor Iuliana", "www.cs.ubbcluj.ro", 15240, Duration(90, 15));
        Tutorial demoTutorial6("Learn C++ with me!", "Mark Zuckenberg", "www.facebook.com", 12, Duration(15, 15));
        Tutorial demoTutorial7("C++ snake game", "Playin Around", "www.youtube.com", 512, Duration(10, 15));
        Tutorial demoTutorial8("Poweful C++ tricks", "Josh the Bosh", "www.youtube.com", 1000, Duration(30, 15));
        Tutorial demoTutorial9("Algorithms in C++", "another indian guy", "www.youtube.com", 4234, Duration(30, 15));
        Tutorial demoTutorial10("Hacking with C++", "Cool guy", "www.youtube.com", 5103, Duration(140, 23));

        this->addTutorial(demoTutorial1);
        this->addTutorial(demoTutorial2);
        this->addTutorial(demoTutorial3);
        this->addTutorial(demoTutorial4);
        this->addTutorial(demoTutorial5);
        this->addTutorial(demoTutorial6);
        this->addTutorial(demoTutorial7);
        this->addTutorial(demoTutorial8);
        this->addTutorial(demoTutorial9);
        this->addTutorial(demoTutorial10);
}

int TutorialsRepository::getSize()
{
    return this->tutorialsList.size();
}


int TutorialsRepository::findPosition(string tutorialTitle, string tutorialPresenter)
{
    /*
    * Function which checks if a tutorial is already in repository
    * <param tutorialToFind> tutorial we want to search in repository
    * <return> -1 if tutorial is not in repository, position of tutorial in repository otherwise
    */

    auto tutorialPosition = find_if(this->tutorialsList.begin(), 
                                    this->tutorialsList.end(),
                                    [tutorialTitle, tutorialPresenter](Tutorial tutorialToCkeck)
                                    {
                                        return tutorialToCkeck.getTitle() == tutorialTitle &&
                                            tutorialToCkeck.getPresenter() == tutorialPresenter; });

    
    if (tutorialPosition == this->tutorialsList.end())
        return -1;

    return tutorialPosition - this->tutorialsList.begin();
}


void TutorialsRepository::addTutorial(Tutorial tutorialToAdd)
{
    if (this->findPosition(tutorialToAdd.getTitle(), tutorialToAdd.getPresenter()) != -1)
        throw std::exception("Tutorial already in repository!");

    this->tutorialsList.push_back(tutorialToAdd);
}


void TutorialsRepository::deleteTutorial(string tutorialTitle, string tutorialPresenter)
{
    int tutorialPosition = this->findPosition(tutorialTitle, tutorialPresenter);

    if (tutorialPosition == -1)
        throw std::exception("Tutorial not in repository!");

    //this->tutorialsList.removeElementAtIndex(tutorialPosition);
    this->tutorialsList.erase(this->tutorialsList.begin() + tutorialPosition);
}

void TutorialsRepository::updateTutorial(Tutorial tutorialToUpdate)
{
    int tutorialPosition = this->findPosition(tutorialToUpdate.getTitle(), tutorialToUpdate.getPresenter());

    if (tutorialPosition == -1)
        throw std::exception("Tutorial not in repository!");

    this->tutorialsList[tutorialPosition] = tutorialToUpdate;
}

Tutorial& TutorialsRepository::getTutorialAtIndex(int index)
{
    if (index < 0 || index >= this->getSize())
        throw std::out_of_range("Index out of range! - Repository");

    return this->tutorialsList[index];
}

vector<Tutorial> TutorialsRepository::getAllTutorials()
{
    return this->tutorialsList;
}
