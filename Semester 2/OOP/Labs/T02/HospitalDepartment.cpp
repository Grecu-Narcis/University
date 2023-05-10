#include "HospitalDepartment.h"

string HospitalDepartment::getHospitalName()
{
    return hospitalName;
}

string HospitalDepartment::toString()
{
    return hospitalName + " " + to_string(numberOfDoctors) + "\n";
}
