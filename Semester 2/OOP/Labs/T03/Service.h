#pragma once

#include "Repository.h"

class Service
{
private:
	Repository& itemsRepository;

public:
	Service(Repository& itemsRepository);

	vector<Item> getAll();
	vector<Item> getAllSortedByCategoryAndName();

	vector<Item> getAllItemsWithGivenCategoryOrName(string requiredString);
	vector<Item> getAllItemsFromCategory(string requiredCategory);
};

