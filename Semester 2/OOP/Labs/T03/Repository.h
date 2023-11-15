#pragma once

#include <vector>

#include "Item.h"

using std::vector;

class Repository
{
private:
	vector<Item> itemsDatabase;
	string filePath;

	void readFile();

public:
	Repository(string filePath);

	vector<Item> getAll();
};

