#pragma once
#include <vector>

using namespace std;

class Variable
{
public:
	int value;
	vector<int> subscribers;
};

