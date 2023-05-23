#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

int SortedMultiMap::hashFunction(TKey k) const
{
	int result = k % m;
	if (result < 0)
		result += m;

	return result;
}

//BC: Theta(1), WC: Theta(1), AC: Theta(1)


void SortedMultiMap::resizeAndRehash()
{
	int oldCapacity = this->m;
	this->m = 2 * this->m;

	TElem* newElems = new TElem[this->m];
	int* newNext = new int[this->m];

	// Initialize the new hash table and next array
	for (int i = 0; i < this->m; i++)
	{
		newElems[i] = NULL_TELEM;
		newNext[i] = -1;
	}

	for (int i = 0; i < oldCapacity; i++)
	{
		if (isNull(elems[i]))
			continue;

		TElem currentElement = this->elems[i];
		int currentPosition = hashFunction(currentElement.first);

		if (isNull(newElems[currentPosition]))
		{
			newElems[currentPosition] = currentElement;
			continue;
		}

		int prev = -1, current = currentPosition;

		while (current != -1 && r(newElems[current].first, currentElement.first))
		{
			prev = current;
			current = newNext[current];
		}

		int positionToInsert = -1;

		for (int j = 0; j < this->m; j++)
		{
			if (isNull(newElems[j]))
			{
				positionToInsert = j;
				break;
			}
		}

		if (prev == -1)
		{
			TElem aux = newElems[current];
			int nextAux = newNext[current];
			newElems[current] = currentElement;
			newElems[positionToInsert] = aux;
			newNext[positionToInsert] = nextAux;
			newNext[current] = positionToInsert;
		}
		else if (current == -1)
		{
			newElems[positionToInsert] = currentElement;
			newNext[prev] = positionToInsert;
		}
		else
		{
			TElem aux = newElems[current];
			int nextAux = newNext[current];
			newElems[current] = currentElement;
			newElems[positionToInsert] = aux;
			newNext[current] = positionToInsert;
			newNext[positionToInsert] = nextAux;
		}
	}

	delete[] this->elems;
	delete[] this->next;

	this->elems = newElems;
	this->next = newNext;
}
//BC: Theta(newCapacity), WC: Theta(newCapacity * oldCapacity), AC: O(newCapacity * oldCapacity)


int SortedMultiMap::firstEmpty()
{
	for (int i = 0; i < this->m; i++)
		if (isNull(this->elems[i]))
			return i;

	return -1;
}
// //BC: Theta(1), WC: Theta(n), AC: O(n)


bool SortedMultiMap::isNull(TElem elemToCheck) const
{
	return elemToCheck.first == NULL_TKEY &&
		elemToCheck.second == NULL_TVALUE;
}
//BC: Theta(1), WC: Theta(1), AC: Theta(1)


int SortedMultiMap::getKeyRange() const
{
	if (this->isEmpty())
		return -1;

	int i = 0;

	while (i < m && isNull(elems[i]))
		i++;

	int minKey = elems[i].first;
	int maxKey = elems[i].first;

	while (i < m)
	{
		if (isNull(elems[i]))
		{
			i++;
			continue;
		}

		if (elems[i].first < minKey)
			minKey = elems[i].first;

		if (elems[i].first > maxKey)
			maxKey = elems[i].first;

		i++;
	}

	return maxKey - minKey;
}
//BC: Theta(1), WC: Theta(n), AC: O(n)



SortedMultiMap::SortedMultiMap(Relation r) {
	//TODO - Implementation
	this->m = 2;
	this->length = 0;
	this->elems = new TElem[this->m];
	this->next = new int[this->m];

	this->r = r;

	for (int i = 0; i < this->m; i++)
	{
		this->elems[i] = NULL_TELEM;
		this->next[i] = -1;
	}

	loadFactor = 0.7;
}

void SortedMultiMap::add(TKey c, TValue v) {
	//TODO - Implementation

	if (1. * (this->length + 1) / this->m >= this->loadFactor)
		this->resizeAndRehash();

	this->length++;

	int position = hashFunction(c);

	if (isNull(elems[position]))
	{
		elems[position] = std::make_pair(c, v);
		return;
	}

	int prev = -1, current = position;

	while (r(elems[current].first, c) && current != -1)
	{
		prev = current;
		current = next[current];
	}

	if (prev == -1)
	{
		TElem aux = elems[current];
		int nextAux = next[current];
		elems[current] = std::make_pair(c, v);

		int positionToInsert = firstEmpty();

		elems[positionToInsert] = aux;
		next[positionToInsert] = nextAux;
		next[current] = positionToInsert;

		return;
	}

	if (current == -1)
	{
		int positionToInsert = firstEmpty();
		elems[positionToInsert] = std::make_pair(c, v);
		next[prev] = positionToInsert;
		return;
	}

	TElem aux = elems[current];
	int nextAux = next[current];
	elems[current] = std::make_pair(c, v);
	int positionToInsert = firstEmpty();

	elems[positionToInsert] = aux;
	next[current] = positionToInsert;
	next[positionToInsert] = nextAux;
}
//BC: Theta(1), WC: Theta(newCapacity * oldCapacity), AC: O(newCapacity * oldCapacity)


vector<TValue> SortedMultiMap::search(TKey c) const {
	//TODO - Implementation
	vector<TValue> values;

	int currentPosition = hashFunction(c);
	TElem currentElement = this->elems[currentPosition];

	if (this->isNull(currentElement))
		return values;

	while (currentPosition != -1)
	{
		if (elems[currentPosition].first == c)
			values.push_back(elems[currentPosition].second);
		
		currentPosition = next[currentPosition];
	}

	return values;
}
//BC: Theta(1), WC: Theta(capacity), AC: O(capacity)


bool SortedMultiMap::remove(TKey c, TValue v) {
	int current = hashFunction(c);
	int prev = -1;

	while (current != -1) {
		if (elems[current].first == c && elems[current].second == v) {
			if (prev == -1) {
				// Removing the first element in the chain
				if (next[current] == -1) {
					// Only one element in the chain
					elems[current] = NULL_TELEM;
				}
				else {
					int nextElement = next[current];
					elems[current] = elems[nextElement];
					next[current] = next[nextElement];
					elems[nextElement] = NULL_TELEM;
					next[nextElement] = -1;
				}
			}
			else {
				// Removing an element in the middle or end of the chain
				int prevElement = prev;
				while (next[prevElement] != current) {
					prevElement = next[prevElement];
				}
				next[prevElement] = next[current];
				elems[current] = NULL_TELEM;
				next[current] = -1;
			}

			return true;
		}

		prev = current;
		current = next[current];
	}

	return false; 
}
//BC: Theta(1), WC: Theta(capacity), AC: O(capacity)


int SortedMultiMap::size() const {
	//TODO - Implementation
	int count = 0;
	for (int i = 0; i < m; i++)
		if (!isNull(elems[i]))
			count++;
	
	return count;
}
//BC: Theta(1), WC: Theta(capacity), AC: O(capacity)


bool SortedMultiMap::isEmpty() const {
	//TODO - Implementation
	return size() == 0;
}
//BC: Theta(1), WC: Theta(capacity), AC: O(capacity)


SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	//TODO - Implementation

	/*delete[] this->elems;
	delete[] this->next;*/
}




































































//SortedMultiMap::SortedMultiMap(Relation r) {
//	//TODO - Implementation
//	this->m = 1000000;
//	this->length = 0;
//	this->elems = new TElem[this->m];
//	this->next = new int[this->m];
//
//	this->r = r;
//
//	for (int i = 0; i < this->m; i++)
//	{
//		this->elems[i] = NULL_TELEM;
//		this->next[i] = -1;
//	}
//
//	loadFactor = 0.7;
//}