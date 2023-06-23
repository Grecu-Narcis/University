#pragma once

#include "ProductsService.h"

typedef struct
{
	Service* productsService;
} UI;

UI* createUI(Service* productsService);

void printMainMenu();

void addProductMenu(UI* ui);
void deleteProductMenu(UI* ui);
void updateProductMenu(UI* ui);
void printAllProducts(UI* ui);
void printAllProductsWithGivenStringInName(UI* ui);
void printAllProductsWithGivenStringInCategory(UI* ui);
void printAllProductsFromCategoryWithExpirationDateClose(UI* ui);

void mainMenu(UI* ui);

void deleteUI(UI* uiToDelete);
