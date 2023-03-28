#include "DynamicArray.h"
#include <stdlib.h>

DynamicArray* createDynamicArray(int arrayCapacity, void (*destroyElement)(ElementType))
{
	/*
	Function that creates a new dynamic array
	<param arrayCapacity> the capacity of the array

	<return> pointer to the created dynamic array
	*/

	DynamicArray* createdArray = malloc(sizeof(DynamicArray));

	if (createdArray == NULL)
		return NULL;

	createdArray->elements = malloc(arrayCapacity * sizeof(ElementType));

	if (createdArray->elements == NULL)
		return NULL;

	createdArray->size = 0;
	createdArray->capacity = arrayCapacity;
	createdArray->destroyElement = destroyElement;

	return createdArray;
}


ElementType getElementAtIndex(DynamicArray* arrayToFindElement, int indexOfElement)
{
	/*
	Function that returns the element from specific position

	<param arrayToFindElement> the dynamic array from which we retrieve the element
	<param indexOfElement> position of the element in the array

	<return> element found on position 'indexOfElement'
	*/

	return arrayToFindElement->elements[indexOfElement];
}


void deleteArray(DynamicArray* arrayToDelete)
{
	/*
	Function to deallocate a dynamic array

	<param arrayToDelete> the array which is to be deallocated
	<param elementFreeFunction> function for deallocating an element from the array (if it's allocated dynamic)
	*/

	if (arrayToDelete == NULL)
		return;

	for (int i = 0; i < arrayToDelete->size; i++)
		arrayToDelete->destroyElement(getElementAtIndex(arrayToDelete, i));

	free(arrayToDelete->elements);
	free(arrayToDelete);
}


void sortArray(DynamicArray* arrayToSort, int(*compareFunction)(ElementType, ElementType), int reverseOrder)
{
	/*
	Function to sort a dynamic array

	<param arrayToSort> the array we want to sort
	<param compareFunction> the function used for comparing two elements (if the return value > 0 then first element should go after the second one in the array)
	<param reverseOrder> flag for the order of sorting (if equal to 1 the array will be sorted in reverse, otherwise it will be in ascending order)
	*/

	for (int i = 0; i < arrayToSort->size; i++)
		for (int j = i + 1; j < arrayToSort->size; j++)
			if (compareFunction(arrayToSort->elements[i], arrayToSort->elements[j]) < 0)
			{
				ElementType aux = arrayToSort->elements[i];
				arrayToSort->elements[i] = arrayToSort->elements[j];
				arrayToSort->elements[j] = aux;
			}

	if (reverseOrder == 1)
	{
		int startIndex = 0, endIndex = arrayToSort->size - 1;

		while (startIndex < endIndex)
		{
			ElementType aux = arrayToSort->elements[startIndex];
			arrayToSort->elements[startIndex] = arrayToSort->elements[endIndex];
			arrayToSort->elements[endIndex] = aux;
			startIndex++; endIndex--;
		}
	}
}


DynamicArray* deepCopyArrayOfProducts(DynamicArray* arrayToCopy)
{
	DynamicArray* copyArray = createDynamicArray(arrayToCopy->capacity, arrayToCopy->destroyElement);

	for (int i = 0; i < arrayToCopy->size; i++)
		addElement(copyArray, deepCopyProduct(arrayToCopy->elements[i]));

	return copyArray;
}

int getSize(DynamicArray* arrayToFindSize)
{
	if (arrayToFindSize == NULL)
		return 0;

	return arrayToFindSize->size;
}


void addElement(DynamicArray* arrayForAdding, ElementType elementToAdd)
{
	/*
	Function to add an element at the end of an array
	
	<param arrayForAdding> the array in which we add the new element
	<param elementToAdd> the element we want to add
	*/

	if (arrayForAdding->size == arrayForAdding->capacity)
		resizeArray(arrayForAdding);

	arrayForAdding->elements[arrayForAdding->size++] = elementToAdd;
}


void deleteElementAtIndex(DynamicArray* arrayForDelete, int indexOfElementToRemove)
{
	/*
	Function which removes an element from a given position in the array

	<param arrayForDelete> the array from which we remove the element
	<param indexOfElementToRemove> the position of the element we want to remove
	<param elementFreeFunction> function for freeing the memory allocated for the element to be removed
	*/

	arrayForDelete->destroyElement(arrayForDelete->elements[indexOfElementToRemove]);

	for (int i = indexOfElementToRemove; i < arrayForDelete->size - 1; i++)
		arrayForDelete->elements[i] = arrayForDelete->elements[i + 1];

	arrayForDelete->size -= 1;
}


void updateElementAtIndex(DynamicArray* arrayForUpdate, int indexOfElementToUpdate, ElementType newElement)
{
	/*
	Function for updating an element from a specific index

	<param arrayForUpdate> array in which we want to update
	<indexOfElementToUpdate> the index of the element to be updated
	<param newElement> the new value for the element at position 'indexOfElementToUpdate'
	*/

	arrayForUpdate->elements[indexOfElementToUpdate] = newElement;
}


void resizeArray(DynamicArray* arrayToResize)
{
	/*
	Function for resizing an array to a higher size

	<param arrayToResize> the array we want to resize
	*/

	if (arrayToResize == NULL)
		return;

	arrayToResize->capacity *= 2;
	
	ElementType* newArrayOfElements = realloc(arrayToResize->elements, arrayToResize->capacity * sizeof(ElementType));
	arrayToResize->elements = newArrayOfElements;
}
