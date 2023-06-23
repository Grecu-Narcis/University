#include "NeonatalUnit.h"

bool NeonatalUnit::isEfficient()
{
    return averageGrade > 8.5;
}

string NeonatalUnit::toString()
{
    string neonatalUnitAsString =
        "Neonatal | " + hospitalName + " | " + to_string(numberOfDoctors)
        + " | " + to_string(averageGrade) + " | ";

    if (isEfficient())
        neonatalUnitAsString += "1\n";
    else
        neonatalUnitAsString += "0\n";

    return neonatalUnitAsString;
}
