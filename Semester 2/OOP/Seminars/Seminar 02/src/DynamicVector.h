#pragma once

template <typename T>
class DynamicVector
{
private: 
	int capacity, size;
	T* elems;

public:
	DynamicVector(int capacity = 10);
	~DynamicVector();
	DynamicVector(const DynamicVector& v);
	DynamicVector& operator=(const DynamicVector& v);
	void add(const T& elem);
	int getSize() const;

private:
	void resize();
};

template<typename T>
inline DynamicVector<T>::DynamicVector(int capacity):
	capacity{capacity}, size{0}
{
	this->elems = new T[this->capacity];
}

template<typename T>
inline DynamicVector<T>::~DynamicVector()
{
	delete[] this->elems;
}

template<typename T>
inline DynamicVector<T>::DynamicVector(const DynamicVector& v)
{
	this->capacity = v.capacity;
	this->size = v.size;

	this->elems = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];
}

template<typename T>
inline DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector& v)
{
	if (this == &v)
		return *this;

	this->capacity = v.capacity;
	this->size = v.size;

	delete[] this->elems;
	this->elems = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];

	return *this;
}

template<typename T>
inline void DynamicVector<T>::add(const T& elem)
{
	if (this->size == this->capacity)
		this->resize();

	this->elems[this->size++] = elem;
}

template<typename T>
inline int DynamicVector<T>::getSize() const
{
	return this->size;
}

template<typename T>
inline void DynamicVector<T>::resize()
{
	int aux_cap = this->capacity * 2;

	T* aux = new T[aux_cap];
	if (aux == nullptr)
		return;

	this->capacity = aux_cap;
	for (int i = 0; i < this->size; i++)
		aux[i] = this->elems[i];
	delete[] this->elems;
	this->elems = aux;
}
