#ifndef __FILE_REPOSITORY_H__
#define __FILE_REPOSITORY_H__

#include "MemoryRepository.h"

class FileRepository : public MemoryRepository
{
private:
	string filePath;

public:
	FileRepository(string filePath);
	~FileRepository();

	void addTutorial(Tutorial tutorialToAdd) override;
	void deleteTutorial(string tutorialTitle, string tutorialPresenter) override;
	void updateTutorial(Tutorial tutorialToUpdate) override;

	void loadFile();
	void saveFile();
};
#endif
