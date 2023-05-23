#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

Node* SortedMultiMap::searchNodeKey(Node* currentNode, TKey keyToSearch) const
{
	if (currentNode == nullptr)
		return nullptr;

	if (currentNode->getKey() == keyToSearch)
		return currentNode;

	if (this->orderRelation(currentNode->getKey(), keyToSearch))
		return this->searchNodeKey(currentNode->getRightNode(), keyToSearch);

	return this->searchNodeKey(currentNode->getLeftNode(), keyToSearch);
}
// BC: Theta(1), WC: Theta(n), AC: O(n)


Node* SortedMultiMap::insertNode(Node* currentNode, Node* nodeToInsert) const
{
	if (currentNode == nullptr)
		currentNode = nodeToInsert;

	else if (this->orderRelation(currentNode->getKey(), nodeToInsert->getKey()))
		currentNode->setRightNode(this->insertNode(currentNode->getRightNode(), nodeToInsert));
	else
		currentNode->setLeftNode(this->insertNode(currentNode->getLeftNode(), nodeToInsert));

	return currentNode;
}
// BC: Theta(1), WC: Theta(n), AC: O(n)


void SortedMultiMap::removeNode(Node* currentNode, Node* nodeToRemove)
{
	Node* parent = nullptr;
	Node* current = root;

	while (current != nullptr && current != nodeToRemove) 
	{
		parent = current;
		
		if (this->orderRelation(nodeToRemove->getKey(), current->getKey()))
			current = current->getLeftNode();
		
		else
			current = current->getRightNode();
	}

	if (current == nullptr)
		return;

	// no descendants
	if (current->getLeftNode() == nullptr && current->getRightNode() == nullptr) 
	{
		if (current != root) 
		{
			if (parent->getLeftNode() == current)
				parent->setLeftNode(nullptr);

			else
				parent->setRightNode(nullptr);
		}

		else
			root = nullptr;

		delete current;
	}

	// both descendants
	else if (current->getLeftNode() && current->getRightNode()) 
	{
		Node* successor = findMin(current->getRightNode());
		Node* successorCopy = new Node{ successor };
		removeNode(root, successor); 
		current->copyNodeData(successorCopy);

	}

	// only one descendant
	else 
	{
		Node* childNode;
		if (current->getLeftNode() != nullptr)
			childNode = current->getLeftNode();

		else
			childNode = current->getRightNode();

		if (current != root)
		{
			if (current == parent->getLeftNode())
				parent->setLeftNode(childNode);

			else
				parent->setRightNode(childNode);
		}
		else
			root = childNode;	
		delete current;
	}
}
// BC: Theta(1), WC: Theta(n), AC: O(n)


Node* SortedMultiMap::findMin(Node* startNode)
{
	while (startNode->getLeftNode() != nullptr)
		startNode = startNode->getLeftNode();
	return startNode;
}
// BC: Theta(1), WC: Theta(n), AC: O(n)


int SortedMultiMap::getSize(Node* currentNode) const
{
	if (currentNode == nullptr)
		return 0;

	int result = currentNode->getSize();
	result += getSize(currentNode->getLeftNode());
	result += getSize(currentNode->getRightNode());

	return result;
}
// BC: Theta(n), WC: Theta(n), AC: Theta(n)


SortedMultiMap::SortedMultiMap(Relation r) {
	//TODO - Implementation
	this->root = nullptr;
	this->orderRelation = r;
}


void SortedMultiMap::add(TKey c, TValue v) {
	//TODO - Implementation

	if (this->root == nullptr)
	{
		this->root = new Node(c);
		this->root->addValue(v);
		return;
	}

	Node* checkNode = this->searchNodeKey(this->root, c);

	if (checkNode != nullptr)
	{
		checkNode->addValue(v);
		return;
	}

	Node* nodeToInsert = new Node(c);
	nodeToInsert->addValue(v);

	this->insertNode(this->root, nodeToInsert);
}
// BC: Theta(1), WC: Theta(n), AC: O(n)


vector<TValue> SortedMultiMap::search(TKey c) const {
	//TODO - Implementation
	Node* checkNode = this->searchNodeKey(this->root, c);

	vector<TValue> values;

	if (checkNode == nullptr)
		return values;

	TValue* keyValues = checkNode->getKeyValues();

	for (int i = 0; i < checkNode->getSize(); i++)
		values.push_back(keyValues[i]);

	return values;
}
// BC: Theta(N), WC: Theta(n + N), AC: O(n + N), where N=number of values associated to key c


bool SortedMultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
	Node* checkNode = this->searchNodeKey(this->root, c);

	if (checkNode == nullptr)
		return false;

	
	if (checkNode->removeValue(v) == false)
		return false;

	if (checkNode->getSize() != 0)
		return true;
	
	this->removeNode(this->root, checkNode);

	return true;
}
// BC: Theta(1), WC: Theta(n), AC: O(n)


int SortedMultiMap::size() const {
	//TODO - Implementation
	return this->getSize(this->root);
}
// BC: Theta(n), WC: Theta(n), AC: Theta(n)


bool SortedMultiMap::isEmpty() const {
	//TODO - Implementation
	return root == nullptr;
}
// BC: Theta(1), WC: Theta(1), AC: Theta(1)


SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	//TODO - Implementation
}



void Node::resize()
{
	int newCapacity = this->capacity * 2;
	TValue* newElements = new TValue[newCapacity];

	for (int i = 0; i < this->capacity; i++)
		newElements[i] = this->keyValues[i];

	delete[] this->keyValues;

	this->capacity = newCapacity;
	this->keyValues = newElements;
}


Node::Node(TKey key)
{
	this->nodeKey = key;

	this->leftNode = nullptr;
	this->rightNode = nullptr;

	this->keyValues = new TValue[2];
	this->capacity = 2;
	this->size = 0;
}


Node::Node(const Node* nodeToCopy)
{
	this->nodeKey = nodeToCopy->nodeKey;
	this->leftNode = nodeToCopy->leftNode;
	this->rightNode = nodeToCopy->rightNode;

	this->capacity = nodeToCopy->capacity;
	this->size = nodeToCopy->size;

	this->keyValues = new TValue[this->capacity];

	for (int i = 0; i < this->size; i++)
		this->keyValues[i] = nodeToCopy->keyValues[i];
}


void Node::setKey(TKey newKey)
{
	this->nodeKey = newKey;
}
// BC: Theta(1), WC: Theta(1), AC: Theta(1)


void Node::setLeftNode(Node* newLeftNode)
{
	this->leftNode = newLeftNode;
}
// BC: Theta(1), WC: Theta(1), AC: Theta(1)


void Node::setRightNode(Node* newRightNode)
{
	this->rightNode = newRightNode;
}
// BC: Theta(1), WC: Theta(1), AC: Theta(1)


void Node::copyNodeData(Node* nodeToCopy)
{
	this->nodeKey = nodeToCopy->nodeKey;
	this->capacity = nodeToCopy->capacity;
	this->size = nodeToCopy->size;

	this->keyValues = nodeToCopy->keyValues;
}
// BC: Theta(1), WC: Theta(1), AC: Theta(1)


void Node::addValue(TValue valueToAdd)
{
	if (this->size == this->capacity)
		this->resize();

	this->keyValues[this->size++] = valueToAdd;
}
// BC: Theta(1), WC: Theta(n), AC: Theta(1) amortized


bool Node::removeValue(TValue valueToRemove)
{
	int valueIndex;

	for (valueIndex = 0; valueIndex < this->size; valueIndex++)
		if (this->keyValues[valueIndex] == valueToRemove)
			break;

	if (valueIndex == this->size)
		return false;

	this->keyValues[valueIndex] = this->keyValues[this->size - 1];
	this->size--;

	return true;
}
// BC: Theta(1), WC: Theta(n), AC: O(n)


TKey Node::getKey()
{
	return this->nodeKey;
}
// BC: Theta(1), WC: Theta(1), AC: Theta(1)


Node* Node::getLeftNode()
{
	return this->leftNode;
}
// BC: Theta(1), WC: Theta(1), AC: Theta(1)


Node* Node::getRightNode()
{
	return this->rightNode;
}
// BC: Theta(1), WC: Theta(1), AC: Theta(1)


TValue* Node::getKeyValues()
{
	return this->keyValues;
}
// BC: Theta(1), WC: Theta(1), AC: Theta(1)


int Node::getSize()
{
	return this->size;
}
// BC: Theta(1), WC: Theta(1), AC: Theta(1)


TElem Node::getElementAtPosition(int position)
{
	return make_pair(this->nodeKey, this->keyValues[position]);
}
// BC: Theta(1), WC: Theta(1), AC: Theta(1)

