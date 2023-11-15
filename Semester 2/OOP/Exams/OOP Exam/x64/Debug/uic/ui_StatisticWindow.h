/********************************************************************************
** Form generated from reading UI file 'StatisticWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTICWINDOW_H
#define UI_STATISTICWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatisticWindowClass
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *mainLayout;

    void setupUi(QWidget *StatisticWindowClass)
    {
        if (StatisticWindowClass->objectName().isEmpty())
            StatisticWindowClass->setObjectName("StatisticWindowClass");
        StatisticWindowClass->resize(600, 400);
        horizontalLayout_2 = new QHBoxLayout(StatisticWindowClass);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        mainLayout = new QVBoxLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName("mainLayout");

        horizontalLayout_2->addLayout(mainLayout);


        retranslateUi(StatisticWindowClass);

        QMetaObject::connectSlotsByName(StatisticWindowClass);
    } // setupUi

    void retranslateUi(QWidget *StatisticWindowClass)
    {
        StatisticWindowClass->setWindowTitle(QCoreApplication::translate("StatisticWindowClass", "StatisticWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StatisticWindowClass: public Ui_StatisticWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTICWINDOW_H
