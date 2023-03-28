#pragma once

#include "Product.h"
#include "DynamicArray.h"

typedef struct
{
	DynamicArray* products;
	int size;
}Repository;

Repository* createRepository();
int findProductPositionInRepo(Repository* productsRepository, char* nameOfProductToFind, char* categoryOfProductToFind);
int addProductToRepository(Repository* productsRepository, Product* productToAdd);
int removeProductFromRepository(Repository* productsRepository, char* nameOfProductToRemove, char* categoryOfProductToRemove);
int updateProductInRepository(Repository* productsRepository, Product* productToUpdate);
void deleteRepository(Repository* repositoryToDelete);
DynamicArray* getAllProductsFromRepository(Repository* productsRepository);
void setRepositoryListOfProducts(Repository* productsRepository, DynamicArray* listOfProducts);
void addSampleProducts(Repository* productsRepository);
Product* findProductInRepository(Repository* productsRepository, char* nameOfProductToFind, char* categoryOfProductToFind);
