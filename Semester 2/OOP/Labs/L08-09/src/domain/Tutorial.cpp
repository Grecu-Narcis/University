#include "Tutorial.h"
#include "../utility/StringOperations.h"

#include <stdlib.h>
#include <cstring>
#include <iostream>


Tutorial::Tutorial()
{
	this->title = "";
	this->presenter = "";
	this->link = "";
	this->numberOfLikes = -1;
	this->duration = Duration(-1, -1);
}

Tutorial::Tutorial(string title, string presenter, string link, int numberOfLikes, Duration duration)
{
	this->title = title;
	this->presenter = presenter;
	this->link = link;
	this->numberOfLikes = numberOfLikes;
	this->duration = duration;
}

Tutorial::Tutorial(const Tutorial& other)
{
	this->title = other.title;
	this->presenter = other.presenter;
	this->link = other.link;
	this->numberOfLikes = other.numberOfLikes;
	this->duration = other.duration;
}

Tutorial& Tutorial::operator=(const Tutorial& other)
{
	Tutorial newTutorial(other);
	
	this->title = newTutorial.title;
	this->presenter = newTutorial.presenter;
	this->link = newTutorial.link;
	this->numberOfLikes = newTutorial.numberOfLikes;
	this->duration = other.duration;

	return *this;
}

bool Tutorial::operator==(const Tutorial& other)
{
	return (this->getTitle() == other.title &&
			this->getPresenter() == other.presenter);
}


string Tutorial::getTitle() const
{
	return this->title;
}

void Tutorial::setTitle(string newTitle)
{
	this->title = newTitle;
}

string Tutorial::getPresenter() const
{
	return this->presenter;
}

void Tutorial::setPresenter(string newPresenter)
{
	this->presenter = newPresenter;
}

string Tutorial::getLink() const
{
	return this->link;
}

void Tutorial::setLink(string newLink)
{
	this->link = newLink;
}

int Tutorial::getNumberOfLikes() const
{
	return this->numberOfLikes;
}

void Tutorial::setNumberOfLikes(int newNumberOfLikes)
{
	this->numberOfLikes = newNumberOfLikes;
}

Duration Tutorial::getDuration() const
{
	return this->duration;
}

void Tutorial::setDuration(Duration newDuration)
{
	this->duration = newDuration;
}

string Tutorial::toString() const
{
	string tutorialAsString = "";
	tutorialAsString += this->title + ",";
	tutorialAsString += this->presenter + ",";
	tutorialAsString += this->link + ",";
	tutorialAsString += std::to_string(this->numberOfLikes) + ",";
	tutorialAsString += this->duration.toString() + "\n";

	return tutorialAsString;
}

bool Tutorial::isNull() const
{
	if (this->getTitle() != "")
		return false;

	if (this->getPresenter() != "")
		return false;

	if (this->getLink() != "")
		return false;

	if (this->getNumberOfLikes() != -1)
		return false;

	if (this->getDuration().minutes != -1)
		return false;

	if (this->getDuration().seconds != -1)
		return false;

	return true;
}


std::ostream& operator<<(std::ostream& outputStream, const Tutorial& tutorialToPrint)
{
	outputStream << tutorialToPrint.toString();
	
	return outputStream;
}

std::istream& operator>>(std::istream& inputStream, Tutorial& tutorialRead)
{
	string tutorialAsString;
	getline(inputStream, tutorialAsString);

	vector<string> tutorialFields = splitString(tutorialAsString, ',');

	if (tutorialFields.size() != 6)
	{
		tutorialRead = Tutorial();
		return inputStream;
	}

	tutorialRead.setTitle(tutorialFields[0]);
	tutorialRead.setPresenter(tutorialFields[1]);
	tutorialRead.setLink(tutorialFields[2]);
	tutorialRead.setNumberOfLikes(stoi(tutorialFields[3]));
	tutorialRead.setDuration(Duration(stoi(tutorialFields[4]), stoi(tutorialFields[5])));
	
	return inputStream;
}