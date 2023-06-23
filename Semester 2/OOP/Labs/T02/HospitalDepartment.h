#pragma once
#include <string>

using namespace std;

class HospitalDepartment
{
protected:
	string hospitalName;
	int numberOfDoctors;

public:
	HospitalDepartment(string hospitalName, int numberOfDoctors) :
		hospitalName{ hospitalName }, numberOfDoctors{ numberOfDoctors } {};

	string getHospitalName();
	virtual bool isEfficient() = 0;
	virtual string toString();
	
	virtual ~HospitalDepartment() {};
};

