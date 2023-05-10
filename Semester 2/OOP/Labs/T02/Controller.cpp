#include "Controller.h"

#include <algorithm>
#include <fstream>

using namespace std;

void Controller::addDepartment(HospitalDepartment* departmentToAdd)
{
	departments.push_back(departmentToAdd);
}

vector<HospitalDepartment*> Controller::getAllDepartments()
{
	return departments;
}

vector<HospitalDepartment*> Controller::getAllEfficientDepartments()
{
	int numberOfEfficientDepartments =
		count_if(
			departments.begin(), departments.end(),
			[](HospitalDepartment* currentDepartment)
			{
				return currentDepartment->isEfficient();
			});

	vector<HospitalDepartment*> efficientDepartments;
	efficientDepartments.resize(numberOfEfficientDepartments);

	copy_if(departments.begin(), departments.end(), efficientDepartments.begin(),
		[](HospitalDepartment* currentDepartment)
		{
			return currentDepartment->isEfficient();
		});

	return efficientDepartments;
}

void Controller::writeToFile(string fileName)
{
	sort(departments.begin(), departments.end(),
		[](HospitalDepartment* firstDepartment, HospitalDepartment* secondDepartment)
		{
			return firstDepartment->getHospitalName() <= secondDepartment->getHospitalName();
		});

	ofstream outputFile(fileName);

	for (const auto& department : departments)
		outputFile << department->toString();
}

Controller::~Controller()
{
	for (int i = 0; i < departments.size(); i++)
		delete departments[i];
}
