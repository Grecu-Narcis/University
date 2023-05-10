#include "Surgery.h"

bool Surgery::isEfficient()
{
    return 1. * numberOfPatients / numberOfDoctors >= 2;
}

string Surgery::toString()
{
    string surgeryAsString =
        "Surgery | " + hospitalName + " | " + to_string(numberOfDoctors) 
        + " | " + to_string(numberOfPatients) + " | ";

    if (isEfficient())
        surgeryAsString += "1\n";
    else
        surgeryAsString += "0\n";

    return surgeryAsString;
}

