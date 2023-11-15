/********************************************************************************
** Form generated from reading UI file 'Window.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowClass
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QListWidget *patientsList;
    QCheckBox *filterCheckBox;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *nameInput;
    QLabel *label_2;
    QLineEdit *diagnosisInput;
    QLabel *label_3;
    QLineEdit *specialisationInput;
    QLabel *label_4;
    QLineEdit *doctorInput;
    QLabel *label_5;
    QLineEdit *dateInput;
    QHBoxLayout *horizontalLayout;
    QPushButton *addDoctorButton;
    QPushButton *updateDiagnosisButton;

    void setupUi(QWidget *WindowClass)
    {
        if (WindowClass->objectName().isEmpty())
            WindowClass->setObjectName("WindowClass");
        WindowClass->resize(523, 398);
        horizontalLayout_2 = new QHBoxLayout(WindowClass);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        patientsList = new QListWidget(WindowClass);
        patientsList->setObjectName("patientsList");

        verticalLayout_2->addWidget(patientsList);

        filterCheckBox = new QCheckBox(WindowClass);
        filterCheckBox->setObjectName("filterCheckBox");

        verticalLayout_2->addWidget(filterCheckBox);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName("formLayout");
        label = new QLabel(WindowClass);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        nameInput = new QLineEdit(WindowClass);
        nameInput->setObjectName("nameInput");

        formLayout->setWidget(0, QFormLayout::FieldRole, nameInput);

        label_2 = new QLabel(WindowClass);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        diagnosisInput = new QLineEdit(WindowClass);
        diagnosisInput->setObjectName("diagnosisInput");

        formLayout->setWidget(1, QFormLayout::FieldRole, diagnosisInput);

        label_3 = new QLabel(WindowClass);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        specialisationInput = new QLineEdit(WindowClass);
        specialisationInput->setObjectName("specialisationInput");

        formLayout->setWidget(2, QFormLayout::FieldRole, specialisationInput);

        label_4 = new QLabel(WindowClass);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        doctorInput = new QLineEdit(WindowClass);
        doctorInput->setObjectName("doctorInput");

        formLayout->setWidget(3, QFormLayout::FieldRole, doctorInput);

        label_5 = new QLabel(WindowClass);
        label_5->setObjectName("label_5");

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        dateInput = new QLineEdit(WindowClass);
        dateInput->setObjectName("dateInput");

        formLayout->setWidget(4, QFormLayout::FieldRole, dateInput);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        addDoctorButton = new QPushButton(WindowClass);
        addDoctorButton->setObjectName("addDoctorButton");

        horizontalLayout->addWidget(addDoctorButton);

        updateDiagnosisButton = new QPushButton(WindowClass);
        updateDiagnosisButton->setObjectName("updateDiagnosisButton");

        horizontalLayout->addWidget(updateDiagnosisButton);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(WindowClass);

        QMetaObject::connectSlotsByName(WindowClass);
    } // setupUi

    void retranslateUi(QWidget *WindowClass)
    {
        WindowClass->setWindowTitle(QCoreApplication::translate("WindowClass", "Window", nullptr));
        filterCheckBox->setText(QCoreApplication::translate("WindowClass", "Filter", nullptr));
        label->setText(QCoreApplication::translate("WindowClass", "Name:", nullptr));
        label_2->setText(QCoreApplication::translate("WindowClass", "Diagnosis:", nullptr));
        label_3->setText(QCoreApplication::translate("WindowClass", "Specialisation:", nullptr));
        label_4->setText(QCoreApplication::translate("WindowClass", "Doctor:", nullptr));
        label_5->setText(QCoreApplication::translate("WindowClass", "Date:", nullptr));
        addDoctorButton->setText(QCoreApplication::translate("WindowClass", "Add", nullptr));
        updateDiagnosisButton->setText(QCoreApplication::translate("WindowClass", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowClass: public Ui_WindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
