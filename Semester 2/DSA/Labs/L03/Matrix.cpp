#include "Matrix.h"
#include <exception>
using namespace std;


void Matrix::resize()
{
	int newCapacity = this->capacity * 2;

	Node* newNodes = new Node[newCapacity];
	int* newNext = new int[newCapacity];
	int* newPrev = new int[newCapacity];

	for (int i = 0; i < this->capacity; i++)
	{
		newNodes[i] = this->nodes[i];
		newNext[i] = this->next[i];
		newPrev[i] = this->prev[i];
	}

	for (int i = this->capacity; i < newCapacity - 1; i++)
		newNext[i] = i + 1;

	newNext[newCapacity - 1] = -1;

	for (int i = this->capacity; i < newCapacity; i++)
		newPrev[i] = i - 1;

	newPrev[this->capacity] = -1;

	delete[] this->nodes;
	delete[] this->next;
	delete[] this->prev;

	this->nodes = newNodes;
	this->next = newNext;
	this->prev = newPrev;
	this->firstEmpty = this->capacity;
	this->capacity = newCapacity;
}


int Matrix::allocate()
{
	int newElem = this->firstEmpty;

	if (newElem == -1)
	{
		this->resize();
		newElem = this->firstEmpty;
	}

	this->firstEmpty = next[this->firstEmpty];

	if (this->firstEmpty != -1)
		this->prev[this->firstEmpty] = -1;

	this->next[newElem] = -1;
	this->prev[newElem] = -1;

	return newElem;
}
// BC: Theta(1), WC: Theta(n), OC: Theta(1) amortized


void Matrix::free(int position)
{	
	this->next[position] = this->firstEmpty;
	this->prev[position] = -1;

	if (this->firstEmpty != -1)
		this->prev[this->firstEmpty] = position;

	this->firstEmpty = position;
}
// BC: Theta(1), WC: Theta(1), OC: Theta(1)


int Matrix::getPositionForInsert(int line, int column)
{
	int previous = -1;

	int current = this->head;

	while (current != -1 && nodes[current].line < line)
	{
		previous = current;
		current = next[current];
	}

	if (current == -1 || nodes[current].line != line)
		return previous;

	while (current != -1 && nodes[current].column < column)
	{
		previous = current;
		current = next[current];
	}

	return previous;
}
// BC: Theta(1), WC: Theta(n), OC: O(n), where n is the number of elements in the list


void Matrix::insert(int line, int column, TElem elementToInsert)
{
	int newPosition = allocate();

	this->nodes[newPosition].info = elementToInsert;
	this->nodes[newPosition].line = line;
	this->nodes[newPosition].column = column;

	this->next[newPosition] = -1;
	this->prev[newPosition] = -1;

	if (this->head == -1)
	{
		// no element in list
		this->head = this->tail = newPosition;
		return;
	}

	int positionForInsert = getPositionForInsert(line, column);
	
	if (positionForInsert == -1)
	{
		// insert before head
		this->next[newPosition] = head;
		this->prev[newPosition] = -1;
		head = newPosition;
	
		return;
	}

	if (positionForInsert == tail)
	{
		// insert at the end

		this->next[newPosition] = -1;
		this->prev[newPosition] = tail;
		this->next[tail] = newPosition;

		tail = newPosition;

		return;
	}

	// insert in between

	this->next[newPosition] = next[positionForInsert];
	this->prev[newPosition] = positionForInsert;
	next[positionForInsert] = newPosition;

	return;
}
// BC: Theta(1), WC: Theta(n), OC: O(n), where n is the number of elements in the list


void Matrix::deleteElement(int line, int column)
{
	int current = head, previous = -1;

	while (current != -1)
	{
		if (nodes[current].line == line && nodes[current].column == column)
			break;

		previous = current;
		current = next[current];
	}

	if (current != -1)
	{
		if (current == head)
			head = next[head];

		else
			next[previous] = next[current];

		free(current);
	}
}
// BC: Theta(1), WC: Theta(n), OC: O(n), where n is the number of elements in the list


void Matrix::sort(int start, int end, int size)
{
	if (start >= end)
		return;

	int mid = (start + end) / 2;

	sort(start, mid, size);
	sort(mid + 1, end, size);

	merge(start, end, mid, size);
}


void Matrix::merge(int start, int end, int mid, int size)
{
	int i = start, j = mid;

	Node* auxNode = new Node[size];
	int* newNext = new int[size];
	int* newPrev = new int[size];

	int k = 0;

	while (i < mid && j <= end)
	{
		if (compareNodes(this->nodes[i], this->nodes[j]))
		{
			auxNode[k] = this->nodes[i];
			newNext[k] = this->next[i];
			newPrev[k] = this->prev[i];

			i++;
			k++;
		}

		else
		{
			auxNode[k] = this->nodes[j];
			newNext[k] = this->next[j];
			newPrev[k] = this->prev[j];

			j++;
			k++;
		}
	}

	while (i < mid)
	{
		auxNode[k] = this->nodes[i];
		newNext[k] = this->next[i];
		newPrev[k] = this->prev[i];

		i++;
		k++;
	}

	while (j <= end)
	{
		auxNode[k] = this->nodes[j];
		newNext[k] = this->next[j];
		newPrev[k] = this->prev[j];

		j++;
		k++;
	}

	for (i = start, k = 0; i <= end; i++, k++)
	{
		this->nodes[i] = auxNode[k];
		this->next[i] = newNext[k];
		this->prev[i] = newPrev[k];
	}

	delete[] auxNode;
	delete[] newNext;
	delete[] newPrev;
}


int Matrix::numberOfNonZero()
{
	int current = head, count = 0;

	while (current != -1)
	{
		count++;
		current = next[current];
	}

	return count;
}

bool Matrix::compareNodes(Node n1, Node n2)
{
	if (n1.line < n2.line)
		return true;

	if (n1.line == n2.line)
		return n1.column <= n2.column;

	return false;
}


Matrix::Matrix(int nrLines, int nrCols) {
	   
	//TODO - Implementation

	this->numberOfLines = nrLines;
	this->numberOfCols = nrCols;

	this->capacity = 2;

	this->nodes = new Node[this->capacity];
	this->next = new int[this->capacity];
	this->prev = new int[this->capacity];

	this->head = this->tail = -1;
	this->firstEmpty = 0;

	for (int i = 0; i < this->capacity - 1; i++)
		this->next[i] = i + 1;

	this->next[this->capacity - 1] = -1;

	for (int i = 0; i < this->capacity; i++)
		this->prev[i] = i - 1;
}


int Matrix::nrLines() const {
	//TODO - Implementation
	return this->numberOfLines;
}
// BC: Theta(1), WC: Theta(1), OC: Theta(1)



int Matrix::nrColumns() const {
	//TODO - Implementation
	return this->numberOfCols;
}
// BC: Theta(1), WC: Theta(1), OC: Theta(1)


TElem Matrix::element(int i, int j) const {
	//TODO - Implementation
	if (i < 0 || i >= numberOfLines)
		throw std::exception{};

	if (j < 0 || j >= numberOfCols)
		throw std::exception{};

	int current = this->head;

	while (current != -1)
	{
		if (nodes[current].line == i && nodes[current].column == j)
			return nodes[current].info;

		current = next[current];
	}

	return NULL_TELEM;
}
// BC: Theta(1), WC: Theta(n), OC: O(n), where n is the number of elements in the list


TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation

	if (i < 0 || i >= numberOfLines)
		throw std::exception{};

	if (j < 0 || j >= numberOfCols)
		throw std::exception{};
	
	int current = this->head;

	while (current != -1)
	{
		if (nodes[current].line == i && nodes[current].column == j)
		{
			TElem valueToReturn = nodes[current].info;

			if (e == NULL_TELEM)
				deleteElement(i, j);
		
			nodes[current].info = e;

			return valueToReturn;
		}

		current = next[current];
	}

	insert(i, j, e);
	return NULL_TELEM;
}
// BC: Theta(1), WC: Theta(n), OC: O(n), where n is the number of elements in the list


void Matrix::transpose()
{
	int current = this->head;

	while (current != -1)
	{
		int aux = this->nodes[current].line;
		this->nodes[current].line = this->nodes[current].column;
		this->nodes[current].column = aux;

		current = next[current];
	}

	int aux = this->numberOfLines;
	this->numberOfLines = this->numberOfCols;
	this->numberOfCols = aux;

	int listSize = this->numberOfNonZero();

	Node headNode = this->nodes[this->head];
	Node tailNode = this->nodes[this->tail];

	sort(0, listSize - 1, listSize);

	for (int i = 0; i < listSize - 1; i++)
		next[i] = i + 1;

	next[listSize - 1] = -1;
	this->head = 0;
}

// BC: Theta(1), WC: Theta(numberOfLines*numberOfCols), OC: O(numberOfLines*numberOfCols)
