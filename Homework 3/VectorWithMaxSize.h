#ifndef _VECTOR_WITH_MAX_SIZE_H
#define _VECTOR_WITH_MAX_SIZE_H

template<class T>
class Vector
{
public:
	Vector(size_t maxSize);
	Vector(const Vector& rhs);
	Vector& operator=(const Vector& rhs);
	~Vector();
public:
	bool isEmpty(){ return size == 0; }
	void addBack(const T& data);
	void removeBack();
	T& operator[](size_t index);
	const T& operator[](size_t index)const;

	void MergeSort();
private:
	void copyFrom(const Vector& rhs);

	void split(T* arr, size_t size, T* sorted);
	void merge(T* left, size_t leftSize, T* right, size_t rightSize, T* sorted);
private:
	T* arr;
	size_t size;
	size_t maxSize;
};


template<class T>
Vector<T>::Vector(size_t maxSize) :arr(new T[maxSize]), size(0), maxSize(maxSize)
{}

template<class T>
Vector<T>::Vector(const Vector& rhs) : arr(NULL), size(0), maxSize(0)
{
	copyFrom(rhs);
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector& rhs)
{
	if (this != *rhs)
	{
		copyFrom(rhs);
	}
	return *this;
}

template<class T>
Vector<T>::~Vector()
{
	delete[] arr;
}

template<class T>
void Vector<T>::addBack(const T& data)
{
	if (size == maxSize)
	{
		throw "Vector is full.";
	}
	arr[size++] = data;
}

template<class T>
void Vector<T>::removeBack()
{
	if (isEmpty())
	{
		throw "Vector is empty.";
	}

	size--;
}

template<class T>
T& Vector<T>::operator[](size_t index)
{
	if (index >= size)
	{
		throw "Index out of range.";
	}

	return arr[index];
}

template<class T>
const T& Vector<T>::operator[](size_t index)const
{
	if (index >= size)
	{
		throw "Index out of range.";
	}

	return arr[index];
}

template<class T>
void Vector<T>::MergeSort()
{
	if (size <= 1)
		return;

	T* sorted = new T[size];
	split(arr, size, sorted);

	delete[]sorted;
}

template<class T>
void Vector<T>::copyFrom(const Vector& rhs)
{
	if (maxSize != rhs.maxSize)
	{
		maxSize = rhs.maxSize;
		delete[] arr;
		arr = new T[maxSize];
	}

	size = rhs.size;
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = rhs.arr[i];
	}
}

template<class T>
void Vector<T>::split(T* arr, size_t size, T* sorted)
{
	if (size <= 1)
		return;

	size_t middle = size / 2;
	split(arr, middle, sorted);
	split(arr + middle, size - middle, sorted + middle);

	merge(arr, middle, arr + middle, size - middle, sorted);

	for (size_t i = 0; i < size; i++)
	{
		arr[i] = sorted[i];
	}
}

template<class T>
void Vector<T>::merge(T* left, size_t leftSize, T* right, size_t rightSize, T* sorted)
{
	size_t i = 0, leftInd = 0, rightInd = 0;

	while (leftInd < leftSize && rightInd < rightSize)
		sorted[i++] = (left[leftInd] <= right[rightInd]) ? left[leftInd++] : right[rightInd++];

	while (leftInd < leftSize)
		sorted[i++] = left[leftInd++];

	while (rightInd < rightSize)
		sorted[i++] = right[rightInd++];
}

#endif
