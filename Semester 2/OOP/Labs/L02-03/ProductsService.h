#pragma once

#include "Repository.h"
#include "UndoService.h"
#include "RedoService.h"

typedef struct
{
	Repository* productsRepository;
	UndoService* undoService;
	RedoService* redoService;
} Service;

Service* createService(Repository* productsRepository, UndoService* undoService, RedoService* redoService);
int serviceAddProduct(Service* productsService, char* productName, char* productCategory, int productQuantity, Date productExpirationDate);
int serviceDeleteProduct(Service* productsService, char* productName, char* productCategory);
int serviceUpdateProduct(Service* productsService, char* productName, char* productCategory, int newProductQuantity, Date newProductExpirationDate);
DynamicArray* getAllProductsContainingGivenString(Service* productsService, char* givenString, int (*checkIfProductContainString)(Product* productToCheck, char* stringToSearch));
DynamicArray* getAllProductsContainingGivenStringInName(Service* productsService, char* givenString);
DynamicArray* getAllProductsContainingGivenStringInCategory(Service* productsService, char* givenString);
DynamicArray* getAllProductsOfGivenCategoryAndThatExpiresInGivenNumberOfDays(Service* productsService, char* givenCategory, int numberOfDaysUntilExpiration);

void undo(Service* productsService);
void redo(Service* productsService);

void deleteService(Service* serviceToDelete);
