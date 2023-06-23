#include "StringOperations.h"

#include <sstream>

using std::istringstream;


string stripString(string stringToStrip)
{
    int firstSpace = 0, lastSpace = stringToStrip.size() - 1;

    while (firstSpace < stringToStrip.size() && (stringToStrip[firstSpace] == ' ' || stringToStrip[firstSpace] == '\n'))
        firstSpace++;

    while (lastSpace >= 0 && (stringToStrip[lastSpace] == ' ' || stringToStrip[lastSpace] == '\n'))
        lastSpace--;

    return stringToStrip.substr(firstSpace, lastSpace - firstSpace + 1);
}


vector<string> splitString(const string stringToSplit, char delimiter)
{
	vector<string> tokens;
	istringstream stringStream(stringToSplit);
	string currentToken;

	while (getline(stringStream, currentToken, delimiter))
	{
		tokens.push_back(stripString(currentToken));
	}

	return tokens;
}

