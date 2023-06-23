#pragma once

#include "Subject.h"

#include "DoctorsRepository.h"
#include "PatientsRepository.h"

class Service : public Subject
{
private:
	DoctorsRepository& doctors;
	PatientsRepository& patients;

public:
	Service(DoctorsRepository& doctors, PatientsRepository& patients);

	vector<Patient> getPatientsWithSpecialisation(string specialisation);

	vector<Patient> getDoctorPatients(string doctorName);

	vector<Patient> getAllPatients();

	Doctor& getDoctorByName(string doctorName);
	Patient& getPatientByName(string patientName);

	string getDoctorWithSpecialisation(string specialisation);

	void updatePatientDiagnosisAndSpecialisation(string patientName, string newDiagnosis, string newSpecialisation, string doctorName);

	void addPatient(string name, string diagnosis, string specialisation, string doctor, string date);
};

