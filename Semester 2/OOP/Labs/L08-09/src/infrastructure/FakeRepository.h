#pragma once
#include "MemoryRepository.h"
class FakeRepository : public MemoryRepository
{
public:
	virtual vector<Tutorial> getAllTutorials() 
	{
		return vector<Tutorial>();
	};
};

