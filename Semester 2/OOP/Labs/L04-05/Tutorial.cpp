#include "Tutorial.h"

#include <stdlib.h>
#include <cstring>


Tutorial::Tutorial()
{
	this->title = "";
	this->presenter = "";
	this->link = "";
	this->numberOfLikes = 0;
	this->duration = Duration(0, 0);
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


string Tutorial::getTitle()
{
	return this->title;
}

void Tutorial::setTitle(string newTitle)
{
	this->title = newTitle;
}

string Tutorial::getPresenter()
{
	return this->presenter;
}

void Tutorial::setPresenter(string newPresenter)
{
	this->presenter = newPresenter;
}

string Tutorial::getLink()
{
	return this->link;
}

void Tutorial::setLink(string newLink)
{
	this->link = newLink;
}

int Tutorial::getNumberOfLikes()
{
	return this->numberOfLikes;
}

void Tutorial::setNumberOfLikes(int newNumberOfLikes)
{
	this->numberOfLikes = newNumberOfLikes;
}

Duration Tutorial::getDuration()
{
	return this->duration;
}

void Tutorial::setDuration(Duration newDuration)
{
	this->duration = newDuration;
}
