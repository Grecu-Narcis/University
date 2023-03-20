#include "Set.h"
#include "SetITerator.h"

#include <algorithm>

Set::Set() {
	//TODO - Implementation
	this->elements = new TElem[2];
	this->capacity = 2;
	this->length = 0;
}

Set::Set(const Set& s)
{
	this->capacity = s.capacity;
	this->length = s.length;

	this->elements = new TElem[s.capacity];

	for (int i = 0; i < s.length; i++)
		this->elements[i] = s.elements[i];

	// std::copy(s.elements, s.elements + s.length, this->elements);
}

Set& Set::operator=(const Set& s)
{
	// TODO: insert return statement here
	if (this == &s)
		return *this;

	TElem* newElements = new TElem[s.capacity];

	for (int i = 0; i < s.length; i++)
		newElements[i] = s.elements[i];

	// std::copy(s.elements, s.elements + s.size(), newElements);

	delete[] elements;

	elements = newElements;
	length = s.length;

	return *this;
}


bool Set::add(TElem elem) {
	for (int i = 0; i < this->length; i++)
		if (this->elements[i] == elem)
			return false;

	if (this->length == this->capacity)
		this->resize(2 * this->capacity);

	this->elements[this->length++] = elem;

	return true;
}


bool Set::remove(TElem elem) {
	//TODO - Implementation

	int indexOfElementInSet = -1;

	for (int i = 0; i < this->length; i++)
		if (this->elements[i] == elem)
		{
			indexOfElementInSet = i;
			break;
		}

	if (indexOfElementInSet == -1)
		return false;

	for (int i = indexOfElementInSet; i < this->length - 1; i++)
		this->elements[i] = this->elements[i + 1];

	this->length--;

	return true;
}

bool Set::search(TElem elem) const {
	//TODO - Implementation

	for (int i = 0; i < this->length; i++)
		if (this->elements[i] == elem)
			return true;

	return false;
}


int Set::size() const {
	//TODO - Implementation
	return this->length;
}


bool Set::isEmpty() const {
	//TODO - Implementation
	return this->length == 0;
}


Set::~Set() {
	//TODO - Implementation

	delete[] this->elements;
}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}

void Set::resize(int newCapacity) {
	TElem* newArray = new TElem[newCapacity];

	for (int i = 0; i < newCapacity && i < this->length; i++)
		newArray[i] = this->elements[i];

	this->capacity = newCapacity;

	if (this->length > newCapacity)
		this->length = newCapacity;

	delete[] this->elements;

	this->elements = newArray;
}


