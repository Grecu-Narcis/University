#pragma once

#include <vector>

#include "Doctor.h"


using std::vector;
class DoctorsRepository
{
private:
	vector<Doctor> doctors;
	string filePath;

public:
	DoctorsRepository(string filePath);

	void readFile();

	int findPosition(string doctorName);
	Doctor& getDoctorByName(string doctorName);

	void add(Doctor doctorToAdd);

	vector<Doctor>& getAll();
};

