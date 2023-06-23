#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__

#include "Product.h"

typedef void* ElementType;

typedef struct
{
	ElementType* elements;
	int size, capacity;

	void (*destroyElement)(ElementType);
} DynamicArray;

DynamicArray* createDynamicArray(int arrayCapacity, void (*destroyElement)(ElementType));
ElementType getElementAtIndex(DynamicArray* arrayToFindElement, int indexOfElement);
void addElement(DynamicArray* arrayForAdding, ElementType elementToAdd);
void deleteElementAtIndex(DynamicArray* arrayForRemove, int indexOfElementToRemove);
void updateElementAtIndex(DynamicArray* arrayForUpdate, int indexOfElementToUpdate, ElementType newElement);
void resizeArray(DynamicArray* arrayToResize);
void deleteArray(DynamicArray* arrayToDelete);
void sortArray(DynamicArray* arrayToSort, int (*compareFunction)(ElementType, ElementType), int reverseOrder);
DynamicArray* deepCopyArrayOfProducts(DynamicArray* arrayToCopy);
int getSize(DynamicArray* arrayToFindSize);

#endif