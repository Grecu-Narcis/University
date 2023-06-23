#pragma once
#include "HospitalDepartment.h"

class NeonatalUnit :
    public HospitalDepartment
{
public:
    double averageGrade;

    NeonatalUnit(string hospitalName, int numberOfDoctors, double averageGrade) :
        HospitalDepartment{ hospitalName, numberOfDoctors }, averageGrade{ averageGrade } {};

    bool isEfficient() override;
    string toString() override;
};

