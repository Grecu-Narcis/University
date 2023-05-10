#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0


struct Node
{
	TElem info;
	int column;
	int line;
};


class Matrix {

private:
	//TODO - Representation
	Node* nodes;
	int* next;
	int* prev;

	int capacity;
	int head, tail;

	int firstEmpty;
	int numberOfLines, numberOfCols;

	void resize();
	int allocate();
	void free(int position);

	int getPositionForInsert(int line, int column);

	void insert(int line, int column, TElem elementToInsert);
	void deleteElement(int line, int column);
	void sort(int start, int end, int size);
	void merge(int start, int end, int mid, int size);
	int numberOfNonZero();

	bool compareNodes(Node n1, Node n2);


public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	void transpose();
};
