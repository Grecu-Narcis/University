#include "Map.h"
#include "MapIterator.h"

Map::Map() {
	this->head = nullptr;
	this->tail = nullptr;
}

Map::~Map() {
	if (head == nullptr && tail == nullptr)
		return;

	Node* current = head, * next;

	while (current != nullptr)
	{
		next = current->next;

		delete current;

		current = next;
	}
}

TValue Map::add(TKey c, TValue v){
	Node* nodeToAdd = new Node(c, v);

	if (head == nullptr)
	{
		head = nodeToAdd;
		tail = nodeToAdd;

		return NULL_TVALUE;
	}

	if (head->info.first == c)
	{
		TValue aux = head->info.second;
		head->info.second = v;

		return aux;
	}

	if (tail->info.first == c)
	{
		TValue aux = tail->info.second;
		tail->info.second = v;

		return aux;
	}

	Node* prev = nullptr, * current = this->head;

	while (current != nullptr)
	{
		if (current->info.first == c)
		{
			TValue aux = current->info.second;
			current->info.second = v;

			return aux;
		}
		prev = current;
		current = current->next;
	}

	tail->next = nodeToAdd;
	nodeToAdd->prev = tail;
	
	tail = nodeToAdd;

	return NULL_TVALUE;
}
// BC: Theta(1), WC: Theta(n), OC: O(n)


TValue Map::search(TKey c) const{
	if (head == nullptr)
		return NULL_TVALUE;

	if (head->info.first == c)
		return head->info.second;

	if (tail->info.first == c)
		return tail->info.second;

	Node* prev = nullptr, * current = this->head;

	while (current != nullptr)
	{
		if (current->info.first == c)
			return current->info.second;
		
		prev = current;
		current = current->next;
	}

	return NULL_TVALUE;
}
// BC: Theta(1), WC: Theta(n), OC: O(n)


TValue Map::remove(TKey c){
	Node *prev = nullptr, *current = this->head;

	if (this->head == nullptr)
		return NULL_TVALUE;

	
	if (head->info.first == c)
	{
		if (head == tail)
		{
			TValue returnValue = head->info.second;

			head = tail = nullptr;
			delete current;

			return returnValue;
		}

		head = head->next;
		head->prev = nullptr;

		TValue returnValue = current->info.second;

		delete current;
		return returnValue;
	}

	if (tail->info.first == c)
	{
		tail = tail->prev;
		current = tail->next;
		tail->next = nullptr;

		TValue returnValue = current->info.second;
		delete current;

		return returnValue;
	}

	while (current != nullptr)
	{
		if (current->info.first == c)
			break;

		prev = current;
		current = current->next;
	}

	if (current == nullptr)
		return NULL_TVALUE;

	TValue returnValue = current->info.second;

	prev->next = current->next;
	current->next->prev = prev;

	delete current;

	return returnValue;
}
// BC: Theta(1), WC: Theta(n), OC: O(n)


int Map::size() const {
	Node* current = head;
	int mapSize = 0;

	while (current != nullptr)
	{
		mapSize++;
		current = current->next;
	}

	return mapSize;
}
// BC: Theta(n), WC: Theta(n), OC: Theta(n)


bool Map::isEmpty() const{
	return head == nullptr;
}
// BC: Theta(1), WC: Theta(1), OC: Theta(1)


MapIterator Map::iterator() const {
	return MapIterator(*this);
}



