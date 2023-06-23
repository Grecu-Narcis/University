#include "Repository.h"
#include <stdlib.h>

Repository* createRepository()
{
	/*
	Function for creating a new repository

	<return> pointer to the new created repository
	*/

	Repository* createdRepo = malloc(sizeof(Repository));

	if (createdRepo == NULL)
		return NULL;

	createdRepo->products = createDynamicArray(2, deleteProduct);

	createdRepo->size = 0;

	return createdRepo;
}


int findProductPositionInRepo(Repository* productsRepository, char* nameOfProductToFind, char* categoryOfProductToFind)
{
	for (int i = 0; i < productsRepository->products->size; i++)
	{
		Product* currentProduct = getElementAtIndex(productsRepository->products, i);
		if (strcmp(currentProduct->name, nameOfProductToFind) == 0 &&
			strcmp(currentProduct->category, categoryOfProductToFind) == 0)
			return i;
	}
	return -1;
}


int addProductToRepository(Repository* productsRepository, Product* productToAdd)
{
	/*
	Function for adding a new product to repository

	<param productsRepository> repository in which we want to add
	<param productToAdd> product to be added

	<return> 1 if product is already in repo (therefore it's quantity is updated), 2 otherwise
	*/

	int productPositionInRepo = findProductPositionInRepo(productsRepository, productToAdd->name, productToAdd->category);

	if (productPositionInRepo != -1)
	{		
		Product* currentProduct = getElementAtIndex(productsRepository->products, productPositionInRepo);
		currentProduct->quantity += productToAdd->quantity;
		return 1;
	}

	addElement(productsRepository->products, productToAdd);

	return 2;
}


int removeProductFromRepository(Repository* productsRepository, char* nameOfProductToRemove, char* categoryOfProductToRemove)
{
	/*
	Function for removing a product from repository

	<param productsRepository> repository from which we remove
	<param nameOfProductToRemove> name of the product to be removed
	<param categoryOfProductToRemove> category of the product to be removed
	
	<return> returns -1 if the product is not in repository, 1 otherwise
	*/

	int productPositionInRepo = findProductPositionInRepo(productsRepository, nameOfProductToRemove, categoryOfProductToRemove);

	if (productPositionInRepo == -1)
		return -1;

	deleteElementAtIndex(productsRepository->products, productPositionInRepo);

	return 1;
}


int updateProductInRepository(Repository* productsRepository, Product* productToUpdate)
{
	/*
	Function to update a given product in repository

	<param productsRepository> repository in which we update the product
	<param productToUpdate> product to be updated

	<return> returns -1 if product is not in repository, otherwise returns 1
	*/

	int productPositionInRepository = findProductPositionInRepo(productsRepository, productToUpdate->name, productToUpdate->category);

	if (productPositionInRepository == -1)
		return -1;

	Product* productFromRepository = getElementAtIndex(productsRepository->products, productPositionInRepository);

	productFromRepository->expirationDate = productToUpdate->expirationDate;
	productFromRepository->quantity = productToUpdate->quantity;

	return 1;
}


void deleteRepository(Repository* repositoryToDelete)
{
	if (repositoryToDelete == NULL)
		return;

	deleteArray(repositoryToDelete->products);

	free(repositoryToDelete);
}


DynamicArray* getAllProductsFromRepository(Repository* productsRepository)
{
	return productsRepository->products;
}

void setRepositoryListOfProducts(Repository* productsRepository, DynamicArray* listOfProducts)
{
	if (productsRepository == NULL)
		return;

	productsRepository->products = listOfProducts;
}


void addSampleProducts(Repository* productsRepository)
{
	Product* productToAdd;

	productToAdd = createProduct("apples", "fruit", 3, createDate(5, 9, 2023));
	addProductToRepository(productsRepository, productToAdd);

	productToAdd = createProduct("pears", "fruit", 5, createDate(12, 4, 2023));
	addProductToRepository(productsRepository, productToAdd);

	productToAdd = createProduct("eggs", "dairy", 30, createDate(30, 10, 2023));
	addProductToRepository(productsRepository, productToAdd);

	productToAdd = createProduct("beef", "meat", 1, createDate(12, 12, 2023));
	addProductToRepository(productsRepository, productToAdd);

	productToAdd = createProduct("chocolate", "sweets", 5, createDate(5, 3, 2025));
	addProductToRepository(productsRepository, productToAdd);
}

Product* findProductInRepository(Repository* productsRepository, char* nameOfProductToFind, char* categoryOfProductToFind)
{
	if (productsRepository == NULL)
		return NULL;

	for (int i = 0; i < getSize(productsRepository->products); i++)
	{
		Product* currentProduct = getElementAtIndex(productsRepository->products, i);

		if (strcmp(currentProduct->name, nameOfProductToFind) == 0 &&
			strcmp(currentProduct->category, categoryOfProductToFind) == 0)
			return currentProduct;
	}

	return NULL;
}
