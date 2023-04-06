#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__

template <typename ElementType>
class DynamicArray
{
private:
	ElementType* elements;
	int size, capacity;

public:
	DynamicArray();
	DynamicArray(int capacity);
	DynamicArray(DynamicArray& arrayToCopy);
	DynamicArray& operator=(DynamicArray& arrayToCopy);
	~DynamicArray();
	
	int getSize();
	int getCapacity();
	ElementType& getElementAtIndex(int index);
	ElementType& operator[](int index);
	void resize();
	void pushBack(ElementType elementToAdd);
	void removeElementAtIndex(int index);
};

#include "DynamicArray.cpp"
#endif
