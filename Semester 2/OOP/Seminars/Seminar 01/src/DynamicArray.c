#include "DynamicArray.h"
#include <stdlib.h>
#include <assert.h>

DynamicArray* createArray(int capacity, void (*destroyElement))
{
	DynamicArray* arr = malloc(sizeof(DynamicArray));

	if (arr == NULL)
		return NULL;

	arr->elems = malloc(sizeof(TElem) * capacity);

	if (arr->elems == NULL)
		return NULL;

	arr->size = 0;
	arr->capacity = capacity;

	arr->destroyElement = destroyElement;

	return arr;
}

void destroyArray(DynamicArray* arr)
{
	if (arr == NULL)
		return;

	free(arr->elems);
	free(arr);
}

int getCapacity(DynamicArray* arr)
{
	if (arr == NULL)
		return -1;

	return arr->capacity;
}

int getSize(DynamicArray* arr)
{
	if (arr == NULL)
		return -1;

	return arr->size;
}

void resizeDynamicArray(DynamicArray* arr)
{
	if (arr == NULL)
		return;

	arr->capacity *= 2;
	TElem* aux = realloc(arr->elems, arr->capacity * sizeof(TElem));
	arr->elems = aux;
}

void addElement(DynamicArray* arr, TElem element)
{
	if (arr == NULL)
		return;

	if (arr->size == arr->capacity)
		resizeDynamicArray(arr);

	arr->elems[arr->size++] = element;
}

void testDynamicArray()
{
	/*DynamicArray* arr = createArray(2, );

	assert(getSize(arr) == 0);
	assert(getCapacity(arr) == 2);*/



}
