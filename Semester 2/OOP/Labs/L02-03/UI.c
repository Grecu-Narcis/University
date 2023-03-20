#include "UI.h"
#include <stdio.h>
#include <stdlib.h>

UI* createUI(Service* productsService)
{
	UI* uiCreated = malloc(sizeof(UI));

	if (uiCreated == NULL)
		return NULL;

	uiCreated->productsService = productsService;

	return uiCreated;
}


void printMainMenu()
{
	printf("Enter 1 to add a new product.\n");
	printf("Enter 2 to remove a product.\n");
	printf("Enter 3 to update a product.\n");
	printf("Enter 4 to display all products in the fridge.\n");
	printf("Enter 5 to display all products whose name contain a given string.\n");
	printf("Enter 6 to display all products whose category contain a given string.\n");
	printf("Enter 7 to display all products from specific category and that expires in given number of days.\n");
	printf("Enter 8 to undo.\n");
	printf("Enter 9 to redo.\n");
	printf("Enter 10 to exit.\n");
}


Date readDateFromConsole()
{
	Date dateRead;

	printf("Day: ");
	scanf("%d", &dateRead.day);

	printf("Month: ");
	scanf("%d", &dateRead.month);

	printf("Year: ");
	scanf("%d", &dateRead.year);

	return dateRead;
}


void addProductMenu(UI* ui)
{
	char productName[101], productCategory[101];
	int productQuantity;
	Date productExpirationDate;

	printf("Enter product name: ");
	gets(productName);

	printf("Enter product category (one of dairy, sweets, meat or fruit): ");
	gets(productCategory);

	printf("Enter product quantity: ");
	scanf("%d", &productQuantity);

	printf("Enter expiration date:\n");
	productExpirationDate = readDateFromConsole();

	int executionStatus = serviceAddProduct(ui->productsService, productName, productCategory, productQuantity, productExpirationDate);

	if (executionStatus == 1)
		printf("\nProduct is already in fridge. Its quantity was updated!\n\n");
	
	else if (executionStatus == 2)
		printf("\nProduct added successfully!\n\n");
}


void deleteProductMenu(UI* ui)
{
	char productName[101], productCategory[101];

	printf("Enter name of product you want to remove: ");
	gets(productName);

	printf("Enter category of product (one of dairy, sweets, meat or fruit): ");
	gets(productCategory);

	int executionStatus = serviceDeleteProduct(ui->productsService, productName, productCategory);

	if (executionStatus == -1)
		printf("\nProduct is not in fridge! Can't remove something that doesn't exists! :)\n\n");
	
	else if (executionStatus == 1)
		printf("\nProduct removed successfully!\n\n");
}


void updateProductMenu(UI* ui)
{
	char productName[101], productCategory[101];
	int productQuantity;
	Date productExpirationDate;

	printf("Enter product name: ");
	gets(productName);

	printf("Enter product category (one of dairy, sweets, meat or fruit): ");
	gets(productCategory);

	printf("Enter new product quantity: ");
	scanf("%d", &productQuantity);

	printf("Enter new expiration date:\n");
	productExpirationDate = readDateFromConsole();

	int executionStatus;
	
	executionStatus = serviceUpdateProduct(ui->productsService, productName, productCategory, productQuantity, productExpirationDate);

	if (executionStatus == -1)
		printf("\nProduct is not in the fridge!\n\n");

	else if (executionStatus == 1)
		printf("\nProduct updated successfully!\n\n");
}


void printProduct(Product* productToPrint)
{
	printf("Product name: %s\n", productToPrint->name);
	printf("Product category: %s\n", productToPrint->category);
	printf("Product quantity: %d\n", productToPrint->quantity);
	printf("Product expiration date (DD MM YYYY): %d %d %d\n",
		productToPrint->expirationDate.day,
		productToPrint->expirationDate.month,
		productToPrint->expirationDate.year);

	printf("\n");
}


void printAllProducts(UI* ui)
{
	if (ui == NULL)
		return;

	DynamicArray* allProductsInFridge = getAllProductsFromRepository(ui->productsService->productsRepository);

	if (allProductsInFridge->size == 0)
	{
		printf("\nThere are no products in the fridge at the moment!\n");
		return;
	}

	printf("\nProducts in the fridge are:\n\n");
	for (int i = 0; i < allProductsInFridge->size; i++)
	{
		Product* currentProduct = getElementAtIndex(allProductsInFridge, i);

		printf("Product no. %d:\n", i + 1);
		printProduct(currentProduct);
	}
	printf("\n");
}


void printAllProductsWithGivenStringInName(UI* ui)
{
	char givenString[101];

	printf("Enter the string to be found in products name: ");
	gets(givenString);

	DynamicArray* productsWithGivenString = getAllProductsContainingGivenStringInName(ui->productsService, givenString);

	if (productsWithGivenString->size == 0)
	{
		free(productsWithGivenString->elements);
		free(productsWithGivenString);

		printf("\nThere is no product in fridge that matches your wished string:)\n\n");
		return;
	}

	printf("\nThe products in the fridge are:\n\n");

	for (int i = 0; i < productsWithGivenString->size; i++)
	{
		Product* currentProduct = getElementAtIndex(productsWithGivenString, i);
		printProduct(currentProduct);
	}

	free(productsWithGivenString->elements);
	free(productsWithGivenString);
}


void printAllProductsWithGivenStringInCategory(UI* ui)
{
	char givenString[101];

	printf("Enter the string to be found in products name: ");
	gets(givenString);

	DynamicArray* productsWithGivenString = getAllProductsContainingGivenStringInCategory(ui->productsService, givenString);

	if (productsWithGivenString->size == 0)
	{
		free(productsWithGivenString->elements);
		free(productsWithGivenString);

		printf("\nThere is no product in fridge that matches your wished string:)\n\n");
		return;
	}

	printf("\nThe products in the fridge are:\n\n");

	for (int i = 0; i < productsWithGivenString->size; i++)
	{
		Product* currentProduct = getElementAtIndex(productsWithGivenString, i);
		printProduct(currentProduct);
	}

	free(productsWithGivenString->elements);
	free(productsWithGivenString);
}


void printAllProductsFromCategoryWithExpirationDateClose(UI* ui)
{
	char category[50] = "";
	int numberOfDaysUntilExpiration;

	printf("Enter the category for filtering: ");
	gets(category);

	printf("Enter the number of days until expiration: ");
	scanf("%d", &numberOfDaysUntilExpiration);

	DynamicArray* productsWithGivenRequirements = getAllProductsOfGivenCategoryAndThatExpiresInGivenNumberOfDays(ui->productsService, category, numberOfDaysUntilExpiration);

	if (productsWithGivenRequirements->size == 0)
		printf("\nThere is no product with the given requirements! :(\n\n");

	else
	{
		printf("\nProducts from category %s and that expires in %d days are:\n", category, numberOfDaysUntilExpiration);
		
		for (int i = 0; i < productsWithGivenRequirements->size; i++)
		{
			printProduct(productsWithGivenRequirements->elements[i]);
		}
	}

	free(productsWithGivenRequirements->elements);
	free(productsWithGivenRequirements);
}


void readOptionFromUserConsole(char optionRead[50])
{
	strcpy(optionRead, "");

	do
	{
		gets(optionRead);
	} while (strlen(optionRead) == 0);
}


void mainMenu(UI* ui)
{
	char option[50] = "";

	while (1)
	{
		printMainMenu();

		printf("Your option is: ");
		readOptionFromUserConsole(option);

		printf("\n");

		if (strcmp(option, "1") == 0)
		{
			addProductMenu(ui);
		}

		else if (strcmp(option, "2") == 0)
		{
			deleteProductMenu(ui);
		}

		else if (strcmp(option, "3") == 0)
		{
			updateProductMenu(ui);
		}

		else if (strcmp(option, "4") == 0)
		{
			printAllProducts(ui);
		}

		else if (strcmp(option, "5") == 0)
		{
			printAllProductsWithGivenStringInName(ui);
		}

		else if (strcmp(option, "6") == 0)
		{
			printAllProductsWithGivenStringInCategory(ui);
		}

		else if (strcmp(option, "7") == 0)
		{
			printAllProductsFromCategoryWithExpirationDateClose(ui);
		}

		else if (strcmp(option, "8") == 0)
		{
			undo(ui->productsService);
		}

		else if (strcmp(option, "9") == 0)
		{
			redo(ui->productsService);
		}

		else if (strcmp(option, "10") == 0)
		{
			break;
		}

		else
		{
			printf("Invalid option!\n");
			continue;
		}
	}
}


void deleteUI(UI* uiToDelete)
{
	if (uiToDelete == NULL)
		return;

	// deleteService(uiToDelete->productsService);

	free(uiToDelete);
}
