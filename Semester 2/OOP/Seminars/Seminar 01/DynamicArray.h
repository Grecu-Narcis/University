#pragma once

typedef int TElem;

typedef struct
{
	TElem* elems;
	int size, capacity;
	void (*destroyElement)(TElem elementToDestroy);
} DynamicArray;

DynamicArray* createArray(int capacity, void (*destroyElement)(TElem));
void destroyArray(DynamicArray* arr);
int getCapacity(DynamicArray* arr);
int getSize(DynamicArray* arr);
void addElement(DynamicArray* arr, TElem element);

void testDynamicArray();
