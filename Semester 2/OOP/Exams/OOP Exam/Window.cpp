#include "Window.h"

#include <QMessageBox>

#include "StringOperations.h"

Window::Window(Service& service, string doctorName, QWidget* parent)
    : QWidget(parent), service{ service }, doctorName{ doctorName }
{
    ui.setupUi(this);

    this->setWindowTitle(QString::fromStdString(doctorName));
    this->update();

    connect(ui.addDoctorButton, &QPushButton::clicked, this, &Window::addPatient);
    connect(ui.filterCheckBox, &QCheckBox::stateChanged, this, &Window::handleCheckBox);
    connect(ui.patientsList, &QListWidget::itemClicked, this, &Window::handlePatientSelection);
    connect(ui.updateDiagnosisButton, &QPushButton::clicked, this, &Window::updatePatient);
}

Window::~Window()
{}

void Window::update()
{
    Doctor& currentDoctor = service.getDoctorByName(this->doctorName);
    this->populateList(service.getPatientsWithSpecialisation(currentDoctor.getSpecialisation()));

    this->handleCheckBox();
}

void Window::populateList(vector<Patient> patients)
{
    ui.patientsList->clear();

    for (auto patient : patients)
    {
        QListWidgetItem* currentPatient = new QListWidgetItem{ QString::fromStdString(patient.toString()) };
        
        if (patient.getDoctor() == this->doctorName)
            currentPatient->setBackground(Qt::green);

        ui.patientsList->addItem(currentPatient);
    }
}

void Window::addPatient()
{
    string name, diagnosis, specialisation, doctor, date;

    name = ui.nameInput->text().toStdString();
    diagnosis = ui.diagnosisInput->text().toStdString();
    specialisation = ui.specialisationInput->text().toStdString();
    doctor = ui.doctorInput->text().toStdString();
    date = ui.dateInput->text().toStdString();

    try
    {
        service.addPatient(name, diagnosis, specialisation, doctor, date);
    }

    catch (std::exception& e)
    {
        QMessageBox alert;
        alert.setText(e.what());

        alert.exec();
    }
}

void Window::handlePatientSelection()
{
    string patientText = ui.patientsList->selectedItems().at(0)->text().toStdString();
    string patientName = splitString(patientText, '|').at(0);

    Patient& selectedPatient = service.getPatientByName(patientName);

    ui.nameInput->setText(QString::fromStdString(selectedPatient.getName()));
    ui.diagnosisInput->setText(QString::fromStdString(selectedPatient.getDiagnosis()));
    ui.specialisationInput->setText(QString::fromStdString(selectedPatient.getSpecialisation()));
    ui.doctorInput->setText(QString::fromStdString(selectedPatient.getDoctor()));
    ui.dateInput->setText(QString::fromStdString(selectedPatient.getDate()));
}

void Window::updatePatient()
{
    string patientName = ui.nameInput->text().toStdString();
    string newDiagnosis = ui.diagnosisInput->text().toStdString();
    string newSpecialisation = ui.specialisationInput->text().toStdString();

    try
    {
        this->service.updatePatientDiagnosisAndSpecialisation(patientName, newDiagnosis, newSpecialisation, this->doctorName);
    }

    catch (std::exception& e)
    {
        QMessageBox alert;
        alert.setText(e.what());

        alert.exec();
    }
}


void Window::handleCheckBox()
{
    if (ui.filterCheckBox->checkState() == Qt::Checked)
    {
        vector<Patient> patients = service.getDoctorPatients(this->doctorName);

        this->populateList(patients);
    }

    else
    {
        Doctor& currentDoctor = service.getDoctorByName(this->doctorName);
        this->populateList(service.getPatientsWithSpecialisation(currentDoctor.getSpecialisation()));
    }
}

