#pragma once

#include <vector>

#include "HospitalDepartment.h"
#include "NeonatalUnit.h"
#include "Surgery.h"

class Controller
{
private:
	vector<HospitalDepartment*> departments;

public:
	void addDepartment(HospitalDepartment* departmentToAdd);
	vector<HospitalDepartment*> getAllDepartments();
	vector<HospitalDepartment*> getAllEfficientDepartments();
	void writeToFile(string fileName);

	~Controller();
};

