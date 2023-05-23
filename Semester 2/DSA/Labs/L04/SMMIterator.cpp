#include "SMMIterator.h"
#include "SortedMultiMap.h"

#include <cassert>
#include <iostream>

void swap(TElem& a, TElem& b)
{
	TElem aux = a;
	a = b;
	b = aux;
}


void SMMIterator::mergeSort(TElem* arr, int left, int right) {
    if (left < right) {
        int mid = (right + left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void SMMIterator::merge(TElem* arr, int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    TElem* leftArr = new TElem[leftSize];
    TElem* rightArr = new TElem[rightSize];

    for (int i = 0; i < leftSize; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < rightSize; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    int i = 0; 
    int j = 0; 
    int k = left; 

    while (i < leftSize && j < rightSize) {
        if (map.r(leftArr[i].first, rightArr[j].first)) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < leftSize) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < rightSize) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void SMMIterator::sortElements() {
    mergeSort(elements, 0, size - 1);
}


SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	//TODO - Implementation
	size = 0;

	for (int i = 0; i < map.m; i++) {
		if (!map.isNull(map.elems[i])) {
			size++;
		}
	}

	elements = new TElem[size];

	int k = 0;

	for (int i = 0; i < map.m; i++) {
		if (!map.isNull(map.elems[i])) {
			elements[k++] = map.elems[i];
		}
	}

    sortElements();

	first();
}

void SMMIterator::first(){
	//TODO - Implementation
	if (map.size() == 0)
	{
		position = -1;
		return;
	}

	position = 0;
}

void SMMIterator::next(){
	//TODO - Implementation
	if (!valid())
		throw exception();

	position++;

	if (position >= size)
		position = -1;
}

bool SMMIterator::valid() const{
	//TODO - Implementation
	return position != -1;
}

TElem SMMIterator::getCurrent() const{
	//TODO - Implementation

	if (!valid())
		throw exception();

	return map.elems[position];
}


