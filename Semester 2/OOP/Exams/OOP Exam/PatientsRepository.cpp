#include "PatientsRepository.h"
#include "StringOperations.h"

#include <fstream>

#include <algorithm>

PatientsRepository::PatientsRepository(string filePath) : filePath{ filePath }
{
	this->readFile();
}

void PatientsRepository::readFile()
{
	std::ifstream inputFile{ this->filePath };

	if (!inputFile.is_open())
		throw std::exception{ "File not open!" };

	string currentPatient;

	while (std::getline(inputFile, currentPatient))
	{
		vector<string> fields = splitString(currentPatient, '|');

		if (fields.size() == 2)
		{
			Patient patientToAdd{ fields[0], fields[1], "", "", "" };
			this->add(patientToAdd);

			continue;
		}

		Patient patientToAdd{ fields[0], fields[1], fields[2], fields[3], fields[4] };

		this->add(patientToAdd);
	}

	inputFile.close();
}

int PatientsRepository::findPosition(string patientName)
{
	auto position = find_if(patients.begin(), patients.end(),
		[&patientName](Patient currentPatient)
		{
			return currentPatient.getName() == patientName;
		});

	if (position == patients.end())
		return -1;

	return position - patients.begin();
}

Patient& PatientsRepository::getPatientByName(string patientName)
{
	int position = this->findPosition(patientName);

	if (position == -1)
		throw std::exception{ "Patient not found!" };

	return patients[position];
}

void PatientsRepository::add(Patient patientToAdd)
{
	if (findPosition(patientToAdd.getName()) != -1)
		throw std::exception{ "Patient already in repository!" };

	patients.push_back(patientToAdd);

	sort(patients.begin(), patients.end(),
		[](Patient p1, Patient p2)
		{
			return p1.getDate() < p2.getDate();
		});
}

void PatientsRepository::saveFile()
{
	std::ofstream outputFile{ this->filePath };

	for (auto patient : patients)
	{
		outputFile << patient.toString() << "\n";
	}
}

vector<Patient>& PatientsRepository::getAll()
{
	return this->patients;
}

/*
Narcis|diagnosis 1|heart|John|2023.12.23
Ben|undiagnosed
*/