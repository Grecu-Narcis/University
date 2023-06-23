#pragma once

#include <QtWidgets/QWidget>
#include "ui_Window.h"

#include "Observer.h"
#include "Service.h"

class Window : public QWidget, public Observer
{
    Q_OBJECT

public:
    Window(Service& service, string doctorName, QWidget *parent = nullptr);
    ~Window();

    void update();

    void populateList(vector<Patient> patients);

    void addPatient();
    void handlePatientSelection();

    void updatePatient();

    void handleCheckBox();

private:
    Ui::WindowClass ui;

    Service& service;
    string doctorName;
};
