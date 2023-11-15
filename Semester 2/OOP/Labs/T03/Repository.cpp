#include "Repository.h"
#include "utility.h"

#include <fstream>
#include <iostream>

void Repository::readFile()
{
	std::ifstream inputFile{ filePath };

	string currentLine;

	while (std::getline(inputFile, currentLine))
	{
		vector<string> itemFields = splitString(currentLine, '|');

		if (itemFields.size() != 3)
			continue;

		Item currentItem{ itemFields[0], itemFields[1], std::stoi(itemFields[2]) };

		itemsDatabase.push_back(currentItem);
	}

	inputFile.close();
}

Repository::Repository(string filePath) : filePath{ filePath }
{
	this->readFile();
}

vector<Item> Repository::getAll()
{
	return itemsDatabase;
}
