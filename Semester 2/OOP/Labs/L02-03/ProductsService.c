#include "ProductsService.h"

#include <stdlib.h>
#include <stdio.h>

Service* createService(Repository* productsRepository, UndoService* undoService, RedoService* redoService)
{
	Service* createdService = malloc(sizeof(Service));

	if (createdService == NULL)
		return NULL;

	createdService->productsRepository = productsRepository;
	createdService->undoService = undoService;
	createdService->redoService = redoService;

	return createdService;
}


int serviceAddProduct(Service* productsService, char* productName, char* productCategory, int productQuantity, Date productExpirationDate)
{
	Product* productToAdd = createProduct(productName, productCategory, productQuantity, productExpirationDate);
	
	addUndoState(productsService->undoService, getAllProductsFromRepository(productsService->productsRepository));

	int executionStatus = addProductToRepository(productsService->productsRepository, productToAdd);

	return executionStatus;
}


int serviceDeleteProduct(Service* productsService, char* productName, char* productCategory)
{
	addUndoState(productsService->undoService, getAllProductsFromRepository(productsService->productsRepository));

	int executionStatus = removeProductFromRepository(productsService->productsRepository, productName, productCategory);

	return executionStatus;
}


int serviceUpdateProduct(Service* productsService, char* productName, char* productCategory, int newProductQuantity, Date newProductExpirationDate)
{
	Product* productToUpdate = createProduct(productName, productCategory, newProductQuantity, newProductExpirationDate);

	addUndoState(productsService->undoService, getAllProductsFromRepository(productsService->productsRepository));

	int executionStatus = updateProductInRepository(productsService->productsRepository, productToUpdate);

	deleteProduct(productToUpdate);

	return executionStatus;
}


int compareProductsByQuantity(Product* firstProduct, Product* secondProduct)
{
	if (firstProduct->quantity > secondProduct->quantity)
		return -1;

	return 1;
}


DynamicArray* getAllProductsContainingGivenString(Service* productsService, char* givenString, int (*checkIfProductContainString)(Product* productToCheck, char* stringToSearch))
{
	DynamicArray* productsInFridge = getAllProductsFromRepository(productsService->productsRepository);
	DynamicArray* productsContainingGivenString = createDynamicArray(2, deleteProduct);

	for (int i = 0; i < productsInFridge->size; i++)
	{
		Product* currentProduct = getElementAtIndex(productsInFridge, i);

		if (checkIfProductContainString(currentProduct, givenString))
			addElement(productsContainingGivenString, currentProduct);
	}

	sortArray(productsContainingGivenString, compareProductsByQuantity, 0);

	return productsContainingGivenString;
}


int checkIfProductContainStringInName(Product* productToCheck, char* stringToSearch)
{
	if (strlen(stringToSearch) == 0)
		return 1;

	return strstr(productToCheck->name, stringToSearch) != NULL;
}


int checkIfProductContainStringInCategory(Product* productToCheck, char* stringToSearch)
{
	if (strlen(stringToSearch) == 0)
		return 1;

	return strstr(productToCheck->category, stringToSearch) != NULL;
}


DynamicArray* getAllProductsContainingGivenStringInName(Service* productsService, char* givenString)
{
	return getAllProductsContainingGivenString(productsService, givenString, checkIfProductContainStringInName);
}


DynamicArray* getAllProductsContainingGivenStringInCategory(Service* productsService, char* givenString)
{
	return getAllProductsContainingGivenString(productsService, givenString, checkIfProductContainStringInCategory);
}


int checkIfProductIsFromCategoryAndExpiresInGivenNumberOfDays(Product* productForCheck, char* givenCategory, int numberOfDaysUntilExpiration)
{
	if (strlen(givenCategory) == 0)
	{
		if (getNumberOfDaysUntilCurrentDay(productForCheck->expirationDate) <= numberOfDaysUntilExpiration)
			return 1;

		return 0;
	}

	if (strcmp(productForCheck->category, givenCategory) == 0 &&
		getNumberOfDaysUntilCurrentDay(productForCheck->expirationDate) <= numberOfDaysUntilExpiration)
		return 1;

	return 0;
}


DynamicArray* getAllProductsOfGivenCategoryAndThatExpiresInGivenNumberOfDays(Service* productsService, char* givenCategory, int numberOfDaysUntilExpiration)
{
	DynamicArray* productsInFridge = getAllProductsFromRepository(productsService->productsRepository);
	DynamicArray* productsThatMeetTheRequirements = createDynamicArray(2, deleteProduct);

	for (int i = 0; i < productsInFridge->size; i++)
		if (checkIfProductIsFromCategoryAndExpiresInGivenNumberOfDays(productsInFridge->elements[i], givenCategory, numberOfDaysUntilExpiration))
			addElement(productsThatMeetTheRequirements, productsInFridge->elements[i]);

	return productsThatMeetTheRequirements;
}

void undo(Service* productsService)
{
	DynamicArray* productsFromUndoState = popUndoState(productsService->undoService);

	if (productsFromUndoState == NULL)
		return;

	DynamicArray* productsInFridge = getAllProductsFromRepository(productsService->productsRepository);

	addRedoState(productsService->redoService, productsInFridge);

	deleteArray(productsInFridge);
	// deleteArray(productsService->productsRepository->products);

	setRepositoryListOfProducts(productsService->productsRepository, productsFromUndoState);
	//productsService->productsRepository->products = state;
}


void redo(Service* productsService)
{
	DynamicArray* productsRedoState = popRedoState(productsService->redoService);

	if (productsRedoState == NULL)
	{
		printf("State is null in redo!\n\n\n");
		return;
	}

	DynamicArray* productsInFridge = getAllProductsFromRepository(productsService->productsRepository);

	addUndoState(productsService->undoService, productsInFridge);


	deleteArray(productsInFridge);

	setRepositoryListOfProducts(productsService->productsRepository, productsRedoState);
}


void deleteService(Service* serviceToDelete)
{
	if (serviceToDelete == NULL)
		return;

	deleteUndoService(serviceToDelete->undoService);
	deleteRedoService(serviceToDelete->redoService);

	free(serviceToDelete);
}
