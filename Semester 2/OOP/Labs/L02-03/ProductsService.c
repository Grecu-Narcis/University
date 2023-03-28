#include "ProductsService.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Service* createService(Repository* productsRepository, UndoService* undoService, RedoService* redoService, EfficientUndoService* efficientUndoService, EfficientRedoService* efficientRedoService)
{
	Service* createdService = malloc(sizeof(Service));

	if (createdService == NULL)
		return NULL;

	createdService->productsRepository = productsRepository;
	createdService->undoService = undoService;
	createdService->redoService = redoService;
	createdService->efficientUndoService = efficientUndoService;
	createdService->efficientRedoService = efficientRedoService;

	return createdService;
}


int serviceAddProduct(Service* productsService, char* productName, char* productCategory, int productQuantity, Date productExpirationDate)
{
	Product* productToAdd = createProduct(productName, productCategory, productQuantity, productExpirationDate);
	
	addUndoState(productsService->undoService, getAllProductsFromRepository(productsService->productsRepository));
	
	Operation* currentOperation = createOperation(serviceDeleteProduct, serviceAddProduct, deepCopyProduct(productToAdd));
	addUndoOperation(productsService->efficientUndoService, currentOperation);

	int executionStatus = addProductToRepository(productsService->productsRepository, productToAdd);

	return executionStatus;
}


int serviceDeleteProduct(Service* productsService, char* productName, char* productCategory)
{
	addUndoState(productsService->undoService, getAllProductsFromRepository(productsService->productsRepository));

	Product* affectedProduct = findProductInRepository(productsService->productsRepository, productName, productCategory);

	if (affectedProduct != NULL)
	{
		Operation* currentOperation = createOperation(serviceAddProduct, serviceDeleteProduct, deepCopyProduct(affectedProduct));
		addUndoOperation(productsService->efficientUndoService, currentOperation);
	}

	int executionStatus = removeProductFromRepository(productsService->productsRepository, productName, productCategory);

	return executionStatus;
}


int serviceUpdateProduct(Service* productsService, char* productName, char* productCategory, int newProductQuantity, Date newProductExpirationDate)
{
	Product* productToUpdate = createProduct(productName, productCategory, newProductQuantity, newProductExpirationDate);

	addUndoState(productsService->undoService, getAllProductsFromRepository(productsService->productsRepository));

	Product* affectedProduct = findProductInRepository(productsService->productsRepository, productName, productCategory);

	if (affectedProduct != NULL)
	{
		Operation* currentOperation = createOperation(serviceUpdateProduct, serviceUpdateProduct, deepCopyProduct(affectedProduct));
		addUndoOperation(productsService->efficientUndoService, currentOperation);
	}

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


DynamicArray* getAllProductsContainingString(Service* productsService, char* givenString, int (*checkIfProductContainString)(Product* productToCheck, char* stringToSearch))
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


DynamicArray* getAllProductsContainingStringInName(Service* productsService, char* givenString)
{
	return getAllProductsContainingString(productsService, givenString, checkIfProductContainStringInName);
}


DynamicArray* getAllProductsContainingStringInCategory(Service* productsService, char* givenString)
{
	return getAllProductsContainingString(productsService, givenString, checkIfProductContainStringInCategory);
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


DynamicArray* getAllProductsFromCategoryWithExpirationClose(Service* productsService, char* givenCategory, int numberOfDaysUntilExpiration, int reverseOrder)
{
	DynamicArray* productsInFridge = getAllProductsFromRepository(productsService->productsRepository);
	DynamicArray* productsThatMeetTheRequirements = createDynamicArray(2, deleteProduct);

	for (int i = 0; i < productsInFridge->size; i++)
		if (checkIfProductIsFromCategoryAndExpiresInGivenNumberOfDays(productsInFridge->elements[i], givenCategory, numberOfDaysUntilExpiration))
			addElement(productsThatMeetTheRequirements, productsInFridge->elements[i]);

	sortArray(productsThatMeetTheRequirements, compareProductsByQuantity, reverseOrder);

	return productsThatMeetTheRequirements;
}

void undoLastOperation(Service* productsService)
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


void redoLastOperation(Service* productsService)
{
	DynamicArray* productsRedoState = popRedoState(productsService->redoService);

	if (productsRedoState == NULL)
	{
		return;
	}

	DynamicArray* productsInFridge = getAllProductsFromRepository(productsService->productsRepository);

	addUndoState(productsService->undoService, productsInFridge);


	deleteArray(productsInFridge);

	setRepositoryListOfProducts(productsService->productsRepository, productsRedoState);
}

void undoLastOperationEfficient(Service* productsService)
{
	Operation* lastOperation = getLastUndoOperation(productsService->efficientUndoService);

	if (lastOperation == NULL)
		return;

	addRedoOperation(productsService->efficientRedoService, deepCopyOperation(lastOperation));

	if (lastOperation->functionForUndo == serviceAddProduct)
	{
		// product was removed during the last operation

		Product* productToAdd = lastOperation->affectedProduct;
		serviceAddProduct(productsService, productToAdd->name, productToAdd->category, productToAdd->quantity, productToAdd->expirationDate);
		removeLastUndoOperation(productsService->efficientUndoService);
	}

	else if (lastOperation->functionForUndo == serviceDeleteProduct)
	{
		Product* productToRemove = lastOperation->affectedProduct;

		serviceDeleteProduct(productsService, productToRemove->name, productToRemove->category);
		removeLastUndoOperation(productsService->efficientUndoService);
	}

	else if (lastOperation->functionForUndo == serviceUpdateProduct)
	{
		Product* productToUpdate = lastOperation->affectedProduct;

		serviceUpdateProduct(productsService, productToUpdate->name, productToUpdate->category, productToUpdate->quantity, productToUpdate->expirationDate);
		removeLastUndoOperation(productsService->efficientUndoService);
	}

	removeLastUndoOperation(productsService->efficientUndoService);
}


void redoLastOperationEfficient(Service* productsService)
{
	Operation* lastOperation = getLastUndoOperation(productsService->efficientRedoService);

	if (lastOperation == NULL)
		return;

	addUndoOperation(productsService->efficientUndoService, deepCopyOperation(lastOperation));

	if (lastOperation->functionForRedo == serviceAddProduct)
	{
		// product was removed during the last operation

		Product* productToAdd = lastOperation->affectedProduct;
		serviceAddProduct(productsService, productToAdd->name, productToAdd->category, productToAdd->quantity, productToAdd->expirationDate);
		removeLastUndoOperation(productsService->efficientUndoService);
	}

	else if (lastOperation->functionForRedo == serviceDeleteProduct)
	{
		Product* productToRemove = lastOperation->affectedProduct;

		serviceDeleteProduct(productsService, productToRemove->name, productToRemove->category);
		removeLastUndoOperation(productsService->efficientUndoService);
	}

	else if (lastOperation->functionForRedo == serviceUpdateProduct)
	{
		Product* productToUpdate = lastOperation->affectedProduct;

		serviceUpdateProduct(productsService, productToUpdate->name, productToUpdate->category, productToUpdate->quantity, productToUpdate->expirationDate);
		removeLastUndoOperation(productsService->efficientUndoService);
	}

	removeLastRedoOperation(productsService->efficientRedoService);
}


void deleteService(Service* serviceToDelete)
{
	if (serviceToDelete == NULL)
		return;

	deleteUndoService(serviceToDelete->undoService);
	deleteRedoService(serviceToDelete->redoService);
	destroyEfficientUndoService(serviceToDelete->efficientUndoService);
	destroyEfficientRedoService(serviceToDelete->efficientRedoService);
	free(serviceToDelete);
}
