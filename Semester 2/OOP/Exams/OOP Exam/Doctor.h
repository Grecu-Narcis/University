#pragma once

#include <string>

using std::string;

class Doctor
{
private:
	string name, specialisation;

public:
	Doctor(string name, string specialisation);

	string getName();
	string getSpecialisation();
};

