#ifndef _DYN_ARRAY_H
#define _DYN_ARRAY_H
#include <iostream>

template<class T>
class DynArray
{
public:
	DynArray();
	DynArray(const DynArray<T>& rhs);
	DynArray& operator=(const DynArray& rhs);
	~DynArray();

public:
	bool isEmpty()const{ return size == 0; }
	size_t getSize()const{ return size; }

	void pushBack(const T& val);

	T& operator[](size_t index);
	const T& operator[](size_t index)const;
public:
	void incrementSize();
private:
	void resize();
	void copyFrom(const DynArray<T>& rhs);
private:
	static const size_t DEFAULT_CAPACITY = 16;
private:
	T* arr;
	size_t size;
	size_t capacity;
};


template<class T>
DynArray<T>::DynArray(): arr(new T[DEFAULT_CAPACITY]), size(0), capacity(DEFAULT_CAPACITY){}

template <class T>
DynArray<T>::DynArray(const DynArray<T>& rhs) : arr(NULL), size(0), capacity(0)
{
	copyFrom(rhs);
}

template<class T>
DynArray<T>& DynArray<T>::operator=(const DynArray<T>& rhs)
{
	if (this != &rhs)
	{
		copyFrom(rhs);
	}

	return *this;
}

template<class T>
DynArray<T>::~DynArray()
{
	delete[] arr;
}

template<class T>
void DynArray<T>::pushBack(const T& val)
{
	arr[size++] = val;
	if (size == capacity)
		resize();
}

template<class T>
T& DynArray<T>::operator[](size_t index)
{
	if (index >= size)
	{
		throw "Index out of range.";
	}

	return arr[index];
}

template<class T>
const T& DynArray<T>::operator[](size_t index)const
{
	if (index >= size)
	{
		throw "Index out of range.";
	}

	return arr[index];
}

template<class T>
void DynArray<T>::incrementSize()
{ 
	size++; 
	if (size == capacity)resize(); 
}

template<class T>
void DynArray<T>::resize()
{
	capacity *= 2;
	T* newArr = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		newArr[i] = arr[i];
	}

	delete[]arr;
	arr = newArr;
}

template<class T>
void DynArray<T>::copyFrom(const DynArray<T>& rhs)
{
	if (rhs.capacity != capacity)
	{
		delete[] arr;
		capacity = rhs.capacity;
		arr = new T[capacity];
	}

	size = rhs.size;
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = rhs.arr[i];
	}
}

#endif
