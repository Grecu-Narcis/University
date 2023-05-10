#include "UI.h"

#include <iostream>

using namespace std;


void UI::printMenu()
{
	cout << "Press 1 to add a new department.\n"
		<< "Press 2 to show all the departments.\n"
		<< "Press 3 to show all the efficients departments in the country.\n"
		<< "Press 4 to save all hospital departments to a file.\n"
		<< "Press 5 to exit.\n\n";

}

void UI::start()
{
	string userOption = "";

	while (true)
	{
		printMenu();

		cout << "Your option is: ";
		getline(cin, userOption);

		if (userOption == "1")
		{
			addDepartmentMenu();
		}

		else if (userOption == "2")
		{
			vector<HospitalDepartment*> allDepartments = departmentsController.getAllDepartments();

			for (const auto& department : allDepartments)
				cout << department->toString();

			cout << '\n';
		}

		else if (userOption == "3")
		{
			vector<HospitalDepartment*> allEfficientDepartments = departmentsController.getAllEfficientDepartments();

			for (const auto& department : allEfficientDepartments)
				cout << department->toString();

			cout << '\n';
		}

		else if (userOption == "4")
		{
			string fileName = "";

			cout << "Enter the file name: ";
			getline(cin, fileName);

			departmentsController.writeToFile(fileName);
		}

		else if (userOption == "5")
		{
			break;
		}

		else
			cout << "Invalid option.\n\n";
	}
}

void UI::addDepartmentMenu()
{
	string departmentType, hospitalName, numberOfDoctorsAsString;

	cout << "Enter the type of department to be added (Neonatal/Surgery): ";
	getline(cin, departmentType);

	cout << "Enter the name of the hospital: ";
	getline(cin, hospitalName);

	cout << "Enter the number of doctors in the hospital: ";
	getline(cin, numberOfDoctorsAsString);

	if (departmentType == "Neonatal")
	{
		string averageGradeAsString;

		cout << "Enter the average grade: ";
		getline(cin, averageGradeAsString);

		departmentsController.addDepartment(
			new NeonatalUnit{ hospitalName, 
			stoi(numberOfDoctorsAsString), 
			stod(averageGradeAsString) }
		);
	}

	else if (departmentType == "Surgery")
	{
		string numberOfPatientsAsString;

		cout << "Enter the number of patients: ";
		getline(cin, numberOfPatientsAsString);

		departmentsController.addDepartment(
			new Surgery{ hospitalName,
			stoi(numberOfDoctorsAsString),
			stoi(numberOfPatientsAsString) }
		);
	}
}
