#pragma once

#include <vector>
#include "Patient.h"

using std::vector;

class PatientsRepository
{
private:
	vector<Patient> patients;
	string filePath;

public:
	PatientsRepository(string filePath);

	void readFile();

	int findPosition(string patientName);
	Patient& getPatientByName(string patientName);

	void add(Patient patientToAdd);

	void saveFile();

	vector<Patient>& getAll();

	~PatientsRepository()
	{
		this->saveFile();
	}
};

