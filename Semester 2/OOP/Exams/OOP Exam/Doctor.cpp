#include "Doctor.h"

Doctor::Doctor(string name, string specialisation) : name { name }, specialisation { specialisation }
{
}

string Doctor::getName()
{
	return this->name;
}

string Doctor::getSpecialisation()
{
	return this->specialisation;
}
