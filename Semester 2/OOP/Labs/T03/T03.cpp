#include "T03.h"

T03::T03(Service& itemsService, QWidget *parent)
    : itemsService{ itemsService }, QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.categoryOrNameInput, &QLineEdit::textChanged, this, &T03::displayItemsWithGivenCategoryOrName);
    connect(ui.filterButton, &QPushButton::clicked, this, &T03::displayAllItemFromCategory);

    this->displayAllItems();
}

T03::~T03()
{}

void T03::displayAllItems()
{
    ui.allItemsList->clear();

    vector<Item> allItems = this->itemsService.getAllSortedByCategoryAndName();

    for (auto item : allItems)
    {
        QListWidgetItem* currentItem = new QListWidgetItem{ QString::fromStdString(item.toString()) };

        ui.allItemsList->addItem(currentItem);
    }
}

void T03::displayItemsWithGivenCategoryOrName()
{
    ui.allItemsList->clear();

    string requiredString = ui.categoryOrNameInput->text().toStdString();
    vector<Item> requiredItems = this->itemsService.getAllItemsWithGivenCategoryOrName(requiredString);

    if (requiredItems.size() == 0)
    {
        QListWidgetItem* currentItem = new QListWidgetItem{ "No item found!" };

        ui.allItemsList->addItem(currentItem);
        return;
    }

    for (auto item : requiredItems)
    {
        QListWidgetItem* currentItem = new QListWidgetItem{ QString::fromStdString(item.toString()) };

        ui.allItemsList->addItem(currentItem);
    }
}

void T03::displayAllItemFromCategory()
{
    ui.filteredItemsList->clear();

    string requiredCategory = ui.categoryInput->text().toStdString();
    vector<Item> requiredItems = this->itemsService.getAllItemsFromCategory(requiredCategory);

    if (requiredItems.size() == 0)
    {
        QListWidgetItem* currentItem = new QListWidgetItem{ "No item found!" };

        ui.filteredItemsList->addItem(currentItem);
        return;
    }

    for (auto item : requiredItems)
    {
        QListWidgetItem* currentItem = new QListWidgetItem{ QString::fromStdString(item.toString()) };

        ui.filteredItemsList->addItem(currentItem);
    }
}

