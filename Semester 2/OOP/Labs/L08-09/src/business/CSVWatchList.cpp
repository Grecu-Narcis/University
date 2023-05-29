#include "CSVWatchList.h"

#include <fstream>
#include <Windows.h>


CSVWatchList::CSVWatchList(const std::string& pathToFile) : FileWatchList {pathToFile}
{
}


void CSVWatchList::writeToFile()
{
	std::ofstream outputFile{ this->pathToFile };

	if (!outputFile.is_open())
		throw std::runtime_error{ "Cannot open file!" };

	for (const auto& tutorial : getAllTutorials())
		outputFile << tutorial;

	outputFile.close();
}


void CSVWatchList::displayFile()
{
	ShellExecuteA(NULL, "open", "C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE", pathToFile.c_str(), NULL, 3);
}
