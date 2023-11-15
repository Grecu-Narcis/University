#include "utility.h"

vector<string> splitString(string stringToSplit, char delimiter)
{
    std::stringstream splitStream{ stringToSplit };
    vector<string> tokens;
    string currentToken;

    while (std::getline(splitStream, currentToken, delimiter))
        tokens.push_back(currentToken);

    return tokens;
}
