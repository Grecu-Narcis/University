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
}


Set& Set::operator=(const Set& s)
{
	// TODO: insert return statement here
	if (this == &s)
		return *this;

	TElem* newElements = new TElem[s.capacity];

	for (int i = 0; i < s.length; i++)
		newElements[i] = s.elements[i];

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
// BC: Theta(1), OC: O(n), WC: Theta(n)


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

	this->elements[indexOfElementInSet] = this->elements[this->length - 1];

	this->length--;

	if (this->length * 4 < this->capacity)
		this->resize(this->capacity / 2);

	return true;
}
// BC: Theta(1), OC: O(n), WC: Theta(n)


bool Set::search(TElem elem) const {
	//TODO - Implementation

	for (int i = 0; i < this->length; i++)
		if (this->elements[i] == elem)
			return true;

	return false;
}
// BC: Theta(1), AC: O(n), WC: Theta(n)
// 1/n+1 + 2/n+1 + ... + n/n+1 + 1 = n(n+1)/2(n+1) + 1 = n/2 + 1 

int Set::size() const {
	//TODO - Implementation
	return this->length;
}
// BC: Theta(1), AC: Theta(1), WC: Theta(1)


bool Set::isEmpty() const {
	//TODO - Implementation
	return this->length == 0;
}
// BC: Theta(1), AC: Theta(1), WC: Theta(1)


Set::~Set() {
	//TODO - Implementation

	delete[] this->elements;
}

void Set::filter(Condition cond)
{
	TElem* elementsToKeep = new TElem[this->capacity];
	int newLength = 0;

	SetIterator iterator = this->iterator();

	while (iterator.valid())
	{
		TElem currentElement = iterator.getCurrent();
		if (cond(currentElement))
			elementsToKeep[newLength++] = currentElement;

		iterator.next();
	}

	/*for (int i = 0; i < this->length; i++)
		if (cond(this->elements[i]))
			elementsToKeep[newLength++] = this->elements[i];*/

	delete[] this->elements;
	this->elements = elementsToKeep;
	this->length = newLength;
}
// BC: Theta(n), AC: Theta(n), WC: Theta(n)


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
// BC: Theta(n), AC: Theta(n), WC: Theta(n)

