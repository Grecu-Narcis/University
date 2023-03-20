#include "Product.h"
#include <stdlib.h>

Product* createProduct(char* productName, char* productCategory, int productQuantity, Date productExpirationDate)
{
	/*
	Function to create a new product

	<param productName> name of the product
	<param productCategory> category of the product
	<param productQuantity> quantity of the product
	<param productExpirationDate> date of expiration for the product
	*/

	Product* createdProduct = malloc(sizeof(Product));

	if (createdProduct == NULL)
		return NULL;

	createdProduct->name = malloc((strlen(productName) + 1) * sizeof(char));

	if (createdProduct->name == NULL)
	{
		free(createdProduct);
		return NULL;
	}

	strcpy(createdProduct->name, productName);

	createdProduct->category = malloc((strlen(productCategory) + 1) * sizeof(char));

	if (createdProduct->category == NULL)
	{
		free(createdProduct->name);
		free(createdProduct);

		return NULL;
	}

	strcpy(createdProduct->category, productCategory);

	createdProduct->quantity = productQuantity;
	createdProduct->expirationDate = productExpirationDate;

	return createdProduct;
}


int checkIfProductsAreSame(Product* firstProduct, Product* secondProduct)
{
	/*
	Function that checks if two products are identical based on name and category

	<param firstProduct> first product of the comparison
	<param secondProduct> second product of the comparison
	*/

	if (strcmp(firstProduct->name, secondProduct->name))
		return 0;

	if (strcmp(firstProduct->category, secondProduct->category))
		return 0;

	return 1;
}


void deleteProduct(Product* productToDelete)
{
	/*
	Function to free up the memory allocated for a product

	<param productToDelete> product for which we want to free the memory
	*/

	if (productToDelete == NULL)
		return;

	free(productToDelete->name);
	free(productToDelete->category);

	free(productToDelete);
}


Product* deepCopyProduct(Product* productToCopy)
{
	if (productToCopy == NULL)
		return NULL;

	Product* copyOfProduct = createProduct(productToCopy->name, productToCopy->category, 
										   productToCopy->quantity, productToCopy->expirationDate);

	return copyOfProduct;
}
