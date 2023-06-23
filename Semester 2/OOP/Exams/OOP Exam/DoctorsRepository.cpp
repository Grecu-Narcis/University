#include "DoctorsRepository.h"

#include <exception>
#include <fstream>

#include "StringOperations.h"

DoctorsRepository::DoctorsRepository(string filePath) : filePath { filePath }
{
	this->readFile();
}

void DoctorsRepository::readFile()
{
	std::ifstream inputFile{ this->filePath };

	if (!inputFile.is_open())
		throw std::exception{ "File not open!" };

	string currentDoctor;

	while (getline(inputFile, currentDoctor))
	{
		vector<string> fields = splitString(currentDoctor, '|');

		if (fields.size() != 2)
			continue;

		Doctor doctorToAdd{ fields[0], fields[1] };

		this->add(doctorToAdd);
	}

	inputFile.close();

}

int DoctorsRepository::findPosition(string doctorName)
{
	auto position = find_if(doctors.begin(), doctors.end(),
		[&doctorName](Doctor currentDoctor)
		{
			return currentDoctor.getName() == doctorName;
		});

	if (position == doctors.end())
		return -1;

	return position - doctors.begin();
}

Doctor& DoctorsRepository::getDoctorByName(string doctorName)
{
	int position = this->findPosition(doctorName);

	if (position == -1)
		throw std::exception{ "Doctor not found!" };

	return doctors[position];
}

void DoctorsRepository::add(Doctor doctorToAdd)
{
	if (this->findPosition(doctorToAdd.getName()) != -1)
		throw std::exception{ "Doctor already in repo!" };

	this->doctors.push_back(doctorToAdd);
}

vector<Doctor>& DoctorsRepository::getAll()
{
	return this->doctors;
}
