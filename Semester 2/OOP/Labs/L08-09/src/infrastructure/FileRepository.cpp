#include "FileRepository.h"

#include <exception>
#include <fstream>


FileRepository::FileRepository(string filePath) : filePath(filePath)
{
	this->tutorialsList.clear();
	this->loadFile();
}

FileRepository::~FileRepository()
{
	this->saveFile();
}


void FileRepository::addTutorial(Tutorial tutorialToAdd)
{
	MemoryRepository::addTutorial(tutorialToAdd);

	this->saveFile();
}


void FileRepository::deleteTutorial(string tutorialTitle, string tutorialPresenter)
{
	MemoryRepository::deleteTutorial(tutorialTitle, tutorialPresenter);

	this->saveFile();
}


void FileRepository::updateTutorial(Tutorial tutorialToUpdate)
{
	MemoryRepository::updateTutorial(tutorialToUpdate);

	this->saveFile();
}


void FileRepository::loadFile()
{
	this->tutorialsList.clear();

	std::ifstream file(this->filePath);

	if (file.fail())
		return;

	Tutorial currentTutorial;
	while (file >> currentTutorial)
	{
		if (currentTutorial.isNull())
			continue;

		MemoryRepository::addTutorial(currentTutorial);
	}

	file.close();
}


void FileRepository::saveFile()
{
	try
	{
		std::ofstream file(this->filePath);

		for (auto tutorial : this->getAllTutorials())
			file << tutorial;

		file.close();
	}

	catch(std::exception& e)
	{}
}
