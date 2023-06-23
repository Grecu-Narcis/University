#ifndef __STRING_OPERATIONS_H__
#define __STRING_OPERATIONS_H__

#include <vector>
#include <string>

using std::string;
using std::vector;


vector<string> splitString(const string stringToSplit, char delimiter=' ');
string stripString(const string stringToStrip);

#endif