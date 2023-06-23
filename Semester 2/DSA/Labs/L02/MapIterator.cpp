#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d), currentNode(nullptr)
{
	currentNode = map.head;
}


void MapIterator::first() 
{
	currentNode = map.head;
}


void MapIterator::next() 
{
	if (!valid())
		throw std::exception();

	currentNode = currentNode->next;
}

void MapIterator::previous()
{
	if (!valid())
		throw std::exception();

	currentNode = currentNode->prev;
}


TElem MapIterator::getCurrent()
{
	if (!valid())
		throw std::exception();

	return currentNode->info;
}


bool MapIterator::valid() const 
{
	return currentNode != nullptr;
}



