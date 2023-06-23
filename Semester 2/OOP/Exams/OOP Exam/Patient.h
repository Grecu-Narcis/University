#pragma once

#include <string>

using std::string;

class Patient
{
private:
	string name, diagnosis, specialisationNeeded, doctor, admissionDate;

public:
	Patient(string name, string diagnosis, string specialisation, string doctor, string date);

	string getName();
	string getDiagnosis();
	string getSpecialisation();
	string getDoctor();
	string getDate();

	void setSpecialisation(string newSpecialisation);
	void setDiagnosis(string newDiagnosis);
	void setDoctor(string newDoctor);

	string toString();
};

