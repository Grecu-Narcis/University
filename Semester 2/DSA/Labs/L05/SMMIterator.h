#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	//TODO - Representation
	Node** nodesInOrder, *currentNode;
	int currentPosition;


	int size, capacity;

	void resize();

	void push(Node* nodeToPush);
	Node* pop();
	Node* top();

	bool empty();

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

