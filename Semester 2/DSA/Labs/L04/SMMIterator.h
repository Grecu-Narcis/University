#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	//TODO - Representation
	int position;
	int size;

	TElem* elements;

	void mergeSort(TElem* arr, int left, int right);
	void merge(TElem* arr, int left, int mid, int right);
	void sortElements();


public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

