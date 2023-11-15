#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_T03.h"

#include "Service.h"

class T03 : public QMainWindow
{
    Q_OBJECT

public:
    T03(Service& itemsService, QWidget *parent = nullptr);
    ~T03();

    void displayAllItems();
    void displayItemsWithGivenCategoryOrName();
    void displayAllItemFromCategory();

private:
    Ui::T03Class ui;

    Service& itemsService;
};
