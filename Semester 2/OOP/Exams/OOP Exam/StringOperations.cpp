#include "StringOperations.h"

#include <sstream>

vector<string> splitString(string stringToSplit, char delimiter)
{
    vector<string> tokens;

    stringstream splitStream{ stringToSplit };
    string token;

    while (getline(splitStream, token, delimiter))
        tokens.push_back(stripString(token));

    return tokens;
}

string stripString(string stringToStrip)
{
    int firstNonSpace = 0, lastNonSpace = stringToStrip.size() - 1;

    while (firstNonSpace < stringToStrip.size() - 1 && stringToStrip[firstNonSpace] == ' ')
        firstNonSpace++;

    while (lastNonSpace >= 0 && stringToStrip[lastNonSpace] == ' ')
        lastNonSpace--;

    return stringToStrip.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
}
