#ifndef __SQL_REPOSITORY_H__
#define __SQL_REPOSITORY_H__


#include "MemoryRepository.h"

#include "../sql/sqlite3.h"


class SQLRepository : public MemoryRepository
{
	sqlite3* tutorialsDatabase;

public:
	SQLRepository();

	int getSize() override;
	int findPosition(string tutorialTitle, string tutorialPresenter) override;
	void addTutorial(Tutorial tutorialToAdd) override;
	void deleteTutorial(string tutorialTitle, string tutorialPresenter) override;
	void updateTutorial(Tutorial tutorialToUpdate) override;
	Tutorial getTutorialAtIndex(int index) override;
	vector<Tutorial> getAllTutorials() override;
};

#endif