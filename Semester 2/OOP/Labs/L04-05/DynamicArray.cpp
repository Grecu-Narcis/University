#include "DynamicArray.h"

#include <exception>
#include <stdexcept>

template<typename ElementType>
DynamicArray<ElementType>::DynamicArray()
{
	this->elements = new ElementType[2];
	this->capacity = 2;
	this->size = 0;
}


template <typename ElementType>
DynamicArray<ElementType>::DynamicArray(int capacity)
{
	this->elements = new ElementType[capacity];
	this->capacity = capacity;
	this->size = 0;
}


template<typename ElementType>
DynamicArray<ElementType>::DynamicArray(DynamicArray& arrayToCopy)
{
	this->elements = new ElementType[arrayToCopy.capacity];
	this->capacity = arrayToCopy.capacity;
	this->size = arrayToCopy.size;

	for (int i = 0; i < this->size; i++)
		this->elements[i] = arrayToCopy.elements[i];
}


template<typename ElementType>
DynamicArray<ElementType>& DynamicArray<ElementType>::operator=(DynamicArray& arrayToCopy)
{
	this->elements = new ElementType[arrayToCopy.capacity];
	this->capacity = arrayToCopy.capacity;
	this->size = arrayToCopy.size;

	for (int i = 0; i < this->size; i++)
		this->elements[i] = arrayToCopy.elements[i];

	return *this;
}


template<typename ElementType>
DynamicArray<ElementType>::~DynamicArray()
{
	delete[] this->elements;
}


template <typename ElementType>
int DynamicArray<ElementType>::getSize()
{
	return this->size;
}


template <typename ElementType>
int DynamicArray<ElementType>::getCapacity()
{
	return this->capacity;
}


template <typename ElementType>
ElementType& DynamicArray<ElementType>::getElementAtIndex(int index)
{
	if (index >= this->size)
		throw std::out_of_range("Index out of range!");

	return this->elements[index];
}


template <typename ElementType>
ElementType& DynamicArray<ElementType>::operator[](int index)
{
	if (index >= this->size)
		throw std::out_of_range("Index out of range!");

	return this->elements[index];
}


template <typename ElementType>
void DynamicArray<ElementType>::resize()
{
	int newCapacity = 2 * this->capacity;

	ElementType* newElements = new ElementType[newCapacity];

	for (int i = 0; i < this->size; i++)
		newElements[i] = this->elements[i];

	delete[] this->elements;
	this->capacity *= 2;

	this->elements = newElements;
}


template<typename ElementType>
void DynamicArray<ElementType>::pushBack(ElementType elementToAdd)
{
	if (this->size == this->capacity)
		this->resize();

	this->elements[this->size++] = elementToAdd;
}


template<typename ElementType>
void DynamicArray<ElementType>::removeElementAtIndex(int index)
{
	if (index >= this->size)
		throw std::out_of_range("Index out of range!");

	for (int i = index; i < this->size - 1; i++)
		this->elements[i] = this->elements[i + 1];

	this->size -= 1;
}
