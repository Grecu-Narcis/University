#include "Patient.h"

Patient::Patient(string name, string diagnosis, string specialisation, string doctor, string date) :
	name{ name }, diagnosis{ diagnosis }, specialisationNeeded{ specialisation }, doctor{ doctor }, admissionDate{ date }
{
}

string Patient::getName()
{
	return this->name;
}

string Patient::getDiagnosis()
{
	return this->diagnosis;
}

string Patient::getSpecialisation()
{
	return this->specialisationNeeded;
}

string Patient::getDoctor()
{
	return this->doctor;
}

string Patient::getDate()
{
	return this->admissionDate;
}

void Patient::setSpecialisation(string newSpecialisation)
{
	this->specialisationNeeded = newSpecialisation;
}

void Patient::setDiagnosis(string newDiagnosis)
{
	this->diagnosis = newDiagnosis;
}

void Patient::setDoctor(string newDoctor)
{
	this->doctor = newDoctor;
}

string Patient::toString()
{
	return this->name + " | " + this->diagnosis + " | " + this->specialisationNeeded + " | " +
		this->doctor + " | " + this->admissionDate;
}
