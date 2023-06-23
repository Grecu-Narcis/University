#pragma once

#include "Date.h"

typedef struct
{
	char* name;
	char* category;
	int quantity;
	Date expirationDate;
} Product;

Product* createProduct(char* productName, char* productCategory, int productQuantity, Date productExpirationDate);
int checkIfProductsAreSame(Product* firstProduct, Product* secondProduct);
void deleteProduct(Product* productToDelete);
Product* deepCopyProduct(Product* productToCopy);