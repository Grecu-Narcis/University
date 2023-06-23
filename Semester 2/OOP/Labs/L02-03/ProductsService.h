#pragma once

#include "Repository.h"
#include "UndoService.h"
#include "RedoService.h"
#include "UndoServiceEfficient.h"
#include "RedoServiceEfficient.h"

typedef struct
{
	Repository* productsRepository;
	UndoService* undoService;
	RedoService* redoService;
	EfficientUndoService* efficientUndoService;
	EfficientRedoService* efficientRedoService;
} Service;

Service* createService(Repository* productsRepository, UndoService* undoService, RedoService* redoService, EfficientUndoService* efficientUndoService, EfficientRedoService* efficientRedoService);
int serviceAddProduct(Service* productsService, char* productName, char* productCategory, int productQuantity, Date productExpirationDate);
int serviceDeleteProduct(Service* productsService, char* productName, char* productCategory);
int serviceUpdateProduct(Service* productsService, char* productName, char* productCategory, int newProductQuantity, Date newProductExpirationDate);
DynamicArray* getAllProductsContainingString(Service* productsService, char* givenString, int (*checkIfProductContainString)(Product* productToCheck, char* stringToSearch));
DynamicArray* getAllProductsContainingStringInName(Service* productsService, char* givenString);
DynamicArray* getAllProductsContainingStringInCategory(Service* productsService, char* givenString);
DynamicArray* getAllProductsFromCategoryWithExpirationClose(Service* productsService, char* givenCategory, int numberOfDaysUntilExpiration, int reverseOrder);

int checkIfProductContainStringInName(Product* productToCheck, char* stringToSearch);

void undoLastOperation(Service* productsService);
void redoLastOperation(Service* productsService);

void undoLastOperationEfficient(Service* productsService);
void redoLastOperationEfficient(Service* productsService);

void deleteService(Service* serviceToDelete);
