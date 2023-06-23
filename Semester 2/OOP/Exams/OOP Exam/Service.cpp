#include "Service.h"

#include <iterator>
#include <algorithm>

Service::Service(DoctorsRepository& doctors, PatientsRepository& patients) :
	doctors{ doctors }, patients{ patients }
{
}

vector<Patient> Service::getPatientsWithSpecialisation(string specialisation)
{
	vector<Patient> requiredPatients;
	vector<Patient> allPatients = patients.getAll();

	copy_if(allPatients.begin(), allPatients.end(), back_inserter(requiredPatients),
		[&specialisation](Patient currentPatient)
		{
			return currentPatient.getSpecialisation() == specialisation ||
				currentPatient.getDiagnosis() == "undiagnosed";
		});

	return requiredPatients;
}

vector<Patient> Service::getDoctorPatients(string doctorName)
{
	vector<Patient> requiredPatients;
	vector<Patient> allPatients = patients.getAll();

	copy_if(allPatients.begin(), allPatients.end(), back_inserter(requiredPatients),
		[&doctorName](Patient currentPatient)
		{
			return currentPatient.getDoctor() == doctorName;
		});

	return requiredPatients;
}

vector<Patient> Service::getAllPatients()
{
	return patients.getAll();
}

Doctor& Service::getDoctorByName(string doctorName)
{
	return doctors.getDoctorByName(doctorName);
}

Patient& Service::getPatientByName(string patientName)
{
	return patients.getPatientByName(patientName);
}

string Service::getDoctorWithSpecialisation(string specialisation)
{
	for (auto& doctor : doctors.getAll())
		if (doctor.getSpecialisation() == specialisation)
			return doctor.getName();

	return "";
}

void Service::updatePatientDiagnosisAndSpecialisation(string patientName, string newDiagnosis, string newSpecialisation, string doctorName)
{
	Patient& requiredPatient = patients.getPatientByName(patientName);

	if (!(requiredPatient.getDiagnosis() == "undiagnosed" || requiredPatient.getDoctor() == doctorName))
		throw std::exception{ "Cannot update!" };

	if (newDiagnosis == "undiagnosed")
		throw std::exception{ "Diagnosis not valid!" };

	requiredPatient.setDiagnosis(newDiagnosis);
	requiredPatient.setSpecialisation(newSpecialisation);
	requiredPatient.setDoctor(this->getDoctorWithSpecialisation(newSpecialisation));

	this->notify();
}

void Service::addPatient(string name, string diagnosis, string specialisation, string doctor, string date)
{
	if (diagnosis == "")
		diagnosis = "undiagnosed";

	if (name == "")
		throw std::exception{ "Name cannot be empty!" };

	if (date < "2023.06.16")
		throw std::exception{ "Date is in the past!" };

	if (specialisation == "")
		specialisation = "None";

	if (doctor == "")
		doctor = "None";

	Patient patientToAdd{ name, diagnosis, specialisation, doctor, date };

	this->patients.add(patientToAdd);

	this->notify();
}
