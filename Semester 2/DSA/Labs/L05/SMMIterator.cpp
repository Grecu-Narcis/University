#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	//TODO - Implementation

	first();
}

void SMMIterator::resize()
{
	int newCapacity = this->capacity * 2;
	Node** newElements = new Node*[newCapacity];

	for (int i = 0; i < this->capacity; i++)
		newElements[i] = this->nodesInOrder[i];

	delete[] this->nodesInOrder;

	this->capacity = newCapacity;
	this->nodesInOrder = newElements;
}
// BC: Theta(capacity), WC: Theta(capacity), AC: Theta(capacity)


void SMMIterator::push(Node* nodeToPush)
{
	if (this->size == this->capacity)
		this->resize();

	this->nodesInOrder[this->size++] = nodeToPush;
}
// BC: Theta(1), WC: Theta(capacity), AC: Theta(1) amortized


Node* SMMIterator::pop()
{
	if (this->size == 0)
		return nullptr;

	this->size--;
	return this->nodesInOrder[this->size];
}
// BC: Theta(1), WC: Theta(1), AC: Theta(1)


Node* SMMIterator::top()
{
	if (this->size == 0)
		return nullptr;

	return this->nodesInOrder[this->size - 1];
}
// BC: Theta(1), WC: Theta(1), AC: Theta(1)


bool SMMIterator::empty()
{
	return this->size == 0;
}
// BC: Theta(1), WC: Theta(1), AC: Theta(1)


void SMMIterator::first(){
	//TODO - Implementation
	this->nodesInOrder = new Node * [2];
	this->size = 0;
	this->capacity = 2;

	Node* parseNode = map.root;

	while (parseNode != nullptr)
	{
		this->push(parseNode);
		parseNode = parseNode->getLeftNode();
	}

	if (!empty())
		currentNode = top();

	else
		currentNode = nullptr;

	this->currentPosition = 0;
}
// BC: Theta(1), WC: Theta(n), AC: O(n)


void SMMIterator::next(){
	//TODO - Implementation
	if (!this->valid())
		throw std::exception();

	if (this->currentPosition >= currentNode->getSize() - 1)
	{
		Node* parseNode = pop();

		if (parseNode->getRightNode() != nullptr)
		{
			parseNode = parseNode->getRightNode();

			while (parseNode != nullptr)
			{
				push(parseNode);
				parseNode = parseNode->getLeftNode();
			}
		}
		
		if (!empty())
			this->currentNode = top();

		else
			this->currentNode = nullptr;

		currentPosition = 0;
		return;
	}

	this->currentPosition++;
}
// BC: Theta(1), WC: Theta(n), AC: O(n)


bool SMMIterator::valid() const{
	//TODO - Implementation
	return this->currentNode != nullptr;
}
// BC: Theta(1), WC: Theta(1), AC: Theta(1)


TElem SMMIterator::getCurrent() const{
	//TODO - Implementation
	if (!this->valid())
		throw std::exception();

	return currentNode->getElementAtPosition(currentPosition);
}
// BC: Theta(1), WC: Theta(1), AC: Theta(1)
