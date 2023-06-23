#include "HTMLWatchList.h"

#include <fstream>
#include <Windows.h>


std::ostream& HTMLWatchList::writeTutorialToFile(std::ostream& outputStream, const Tutorial& tutorialToWrite)
{
	outputStream << "<tr>\n";

	outputStream << "\t<td>" << tutorialToWrite.getTitle() << "</td>\n";
	outputStream << "\t<td>" << tutorialToWrite.getPresenter() << "</td>\n";
	outputStream << "\t<td><a href=\"" << tutorialToWrite.getLink() << "\">Link</a></td>\n";
	outputStream << "\t<td>" << tutorialToWrite.getNumberOfLikes() << "</td>\n";
	outputStream << "\t<td>" << tutorialToWrite.getDuration().minutes << ":" << tutorialToWrite.getDuration().seconds << "</td>\n";

	outputStream << "</tr>\n";

	return outputStream;
}


HTMLWatchList::HTMLWatchList(const std::string& pathToFile) : FileWatchList {pathToFile}
{
}


void HTMLWatchList::writeToFile()
{
	std::ofstream outputFile{ pathToFile };

	if (!outputFile.is_open())
		throw std::exception{ "Cannot open HTML file!" };

	outputFile << "<!DOCTYPE html>\n";
	outputFile << "<html>\n";
	outputFile << "<head>\n";
	outputFile << "\t<title>Watch List</title>\n";
	outputFile << "</head>\n";

	outputFile << "<body>\n";
	outputFile << "<table border=\"1\">\n";
	outputFile << "\t<tr>\n";

	outputFile << "\t\t<td>Title</td>\n";
	outputFile << "\t\t<td>Presenter</td>\n";
	outputFile << "\t\t<td>Youtube link</td>\n";
	outputFile << "\t\t<td>Number of likes</td>\n";
	outputFile << "\t\t<td>Duration</td>\n";

	outputFile << "\t</tr>\n";

	for (const auto& tutorial : tutorialsList)
		writeTutorialToFile(outputFile, tutorial);

	outputFile << "</table>\n";
	outputFile << "</body>\n";
	outputFile << "</html>\n";

	outputFile.close();
}


void HTMLWatchList::displayFile()
{
	ShellExecuteA(NULL, "open", pathToFile.c_str(), NULL, NULL, 3);
}
