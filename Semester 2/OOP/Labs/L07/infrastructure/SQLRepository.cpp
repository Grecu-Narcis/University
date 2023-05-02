#include "SQLRepository.h"
#include "RepositoryException.h"

#include <exception>
#include <stdexcept>
#include <iostream>

#include "../sql/sqlite3.h"

SQLRepository::SQLRepository()
{
	int returnStatus = sqlite3_open("database.db", &tutorialsDatabase);

	if (returnStatus)
		throw std::runtime_error{ "Cannot connect to database!" };

	/*std::string createCommand =
		"CREATE TABLE TUTORIAL("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT DEFAULT -1, "
		"TITLE CHAR(256) NOT NULL, "
		"PRESENTER CHAR(256) NOT NULL, "
		"LINK CHAR(256) NOT NULL, "
		"NUMBER_OF_LIKES INTEGER NOT NULL, "
		"MINUTES_DURATION INTEGER, "
		"SECONDS_DURATION INTEGER)";

	char* messageError;

	returnStatus = sqlite3_exec(tutorialsDatabase, createCommand.c_str(), NULL, 0, &messageError);

	if (returnStatus != SQLITE_OK)
	{
		sqlite3_free(messageError);

		throw std::runtime_error{ "Cannot create table!" };
	}

	addSampleData();*/
}


static int getSizeCallback(void* data, int numberOfColumns, char** fieldsInRow, char** columnName)
{
	int* repositorySize = reinterpret_cast<int*>(data);

	(*repositorySize)++;

	return 0;
}


int SQLRepository::getSize()
{
	int repositorySize = 0;
	
	std::string commandToExecute = "SELECT * FROM TUTORIAL";

	char* messageError;

	int returnStatus = sqlite3_exec(tutorialsDatabase, commandToExecute.c_str(), getSizeCallback, &repositorySize, &messageError);

	if (returnStatus != SQLITE_OK)
	{
		sqlite3_free(messageError);

		throw RepositoryException{ "Failed to get size!" };
	}

	return repositorySize;
}


static int findPositionCallback(void* data, int numberOfColumns, char** fieldsInRow, char** columnName)
{
	int* tutorialPosition = reinterpret_cast<int*>(data);

	*tutorialPosition = stoi(string(fieldsInRow[0]));

	return 0;
}


int SQLRepository::findPosition(string tutorialTitle, string tutorialPresenter)
{
	int tutorialPosition = -1;

	std::string commandToExecute = "SELECT * FROM TUTORIAL WHERE TITLE = '" +
		tutorialTitle + "' AND PRESENTER = '" + tutorialPresenter + "';";

	char* messageError;

	int returnStatus = sqlite3_exec(tutorialsDatabase, commandToExecute.c_str(), findPositionCallback, &tutorialPosition, &messageError);

	if (returnStatus != SQLITE_OK)
	{
		sqlite3_free(messageError);

		throw RepositoryException{ "Failed to find position!" };
	}

	return tutorialPosition;
}


void SQLRepository::addTutorial(Tutorial tutorialToAdd)
{
	int tutorialPosition = findPosition(tutorialToAdd.getTitle(), tutorialToAdd.getPresenter());

	if (tutorialPosition != -1)
		throw RepositoryException{ "Tutorial already in repository!" };

	std::string commandToExecute = "INSERT INTO TUTORIAL (TITLE, PRESENTER, LINK, NUMBER_OF_LIKES, MINUTES_DURATION, SECONDS_DURATION)";
	commandToExecute += " VALUES (";
	commandToExecute += "'" + tutorialToAdd.getTitle() + "', ";
	commandToExecute += "'" + tutorialToAdd.getPresenter() + "', ";
	commandToExecute += "'" + tutorialToAdd.getLink() + "', ";
	commandToExecute += to_string(tutorialToAdd.getNumberOfLikes()) + ", ";
	commandToExecute += to_string(tutorialToAdd.getDuration().minutes) + ", ";
	commandToExecute += to_string(tutorialToAdd.getDuration().seconds) + ");";

	char* messageError;

	int returnStatus = sqlite3_exec(tutorialsDatabase, commandToExecute.c_str(), NULL, NULL, &messageError);

	if (returnStatus != SQLITE_OK)
	{
		sqlite3_free(messageError);
		throw RepositoryException{ "Failed to add tutorial!" };
	}
}


void SQLRepository::deleteTutorial(string tutorialTitle, string tutorialPresenter)
{
	int tutorialPosition = findPosition(tutorialTitle, tutorialPresenter);

	if (tutorialPosition == -1)
		throw RepositoryException{ "Tutorial not in repository!" };

	std::string commandToExecute =
		"DELETE FROM TUTORIAL WHERE TITLE = '" + 
		tutorialTitle + "' AND PRESENTER = '" + 
		tutorialPresenter +"';";

	char* messageError;

	int returnStatus = sqlite3_exec(tutorialsDatabase, commandToExecute.c_str(), NULL, NULL, &messageError);

	if (returnStatus != SQLITE_OK)
	{
		sqlite3_free(messageError);

		throw RepositoryException{ "Failed to delete tutorial!" };
	}
}


void SQLRepository::updateTutorial(Tutorial tutorialToUpdate)
{
	deleteTutorial(tutorialToUpdate.getTitle(), tutorialToUpdate.getPresenter());
	addTutorial(tutorialToUpdate);
}


static int getTutorialAtIndexCallback(void* data, int numberOfColumns, char** fieldsInRow, char** columnName)
{
	Tutorial* tutorialFound = reinterpret_cast<Tutorial*>(data);

	tutorialFound->setTitle(string(fieldsInRow[1]));
	tutorialFound->setPresenter(string(fieldsInRow[2]));
	tutorialFound->setLink(string(fieldsInRow[3]));
	tutorialFound->setNumberOfLikes(stoi(string(fieldsInRow[4])));

	Duration tutorialDuration(stoi(fieldsInRow[5]), stoi(fieldsInRow[6]));

	tutorialFound->setDuration(tutorialDuration);

	return 0;
}


Tutorial SQLRepository::getTutorialAtIndex(int index)
{
	//if (index < 0 || index >= this->getSize())
	//	throw RepositoryException{ "Index out of range! - Repository" };
	
	Tutorial tutorialFound;

	std::string commandToExecute =
		"SELECT * FROM TUTORIAL WHERE ID = " + to_string(index) + ";";

	char* messageError;

	int returnStatus = sqlite3_exec(tutorialsDatabase, commandToExecute.c_str(), getTutorialAtIndexCallback, &tutorialFound, &messageError);

	if (returnStatus != SQLITE_OK)
	{
		sqlite3_free(messageError);

		throw RepositoryException{ "Failed to get tutorial at index: " + to_string(index) + "!"};
	}

	if (tutorialFound.isNull())
		throw RepositoryException{ "Index out of range! - Repository" };

	return tutorialFound;
}


static int getAllTutorialsCallback(void* data, int numberOfColumns, char** fieldsInRow, char** columnName)
{
	std::vector<Tutorial>* tutorialsList = reinterpret_cast<std::vector<Tutorial>*>(data);

	Tutorial tutorialFound;

	tutorialFound.setTitle(fieldsInRow[1]);
	tutorialFound.setPresenter(fieldsInRow[2]);
	tutorialFound.setLink(fieldsInRow[3]);
	tutorialFound.setNumberOfLikes(stoi(string(fieldsInRow[4])));

	Duration tutorialDuration(stoi(fieldsInRow[5]), stoi(fieldsInRow[6]));
	tutorialFound.setDuration(tutorialDuration);

	tutorialsList->push_back(tutorialFound);

	return 0;
}


vector<Tutorial> SQLRepository::getAllTutorials()
{
	vector<Tutorial> tutorialsList;

	std::string commandToExecute = "SELECT * FROM TUTORIAL;";

	char* messageError;

	int returnStatus = sqlite3_exec(tutorialsDatabase, commandToExecute.c_str(),
		getAllTutorialsCallback, &tutorialsList, &messageError);

	if (returnStatus != SQLITE_OK)
	{
		sqlite3_free(messageError);

		throw RepositoryException{ "Failed to get all tutorials!" };
	}

	return tutorialsList;
}
