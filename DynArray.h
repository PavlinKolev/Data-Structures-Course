#ifndef _DYN_ARRAY_H
#define _DYN_ARRAY_H

template<class T>
class DynArray
{
public:
	DynArray();
	DynArray(const DynArray& rhs);
	~DynArray();
	DynArray& operator=(const DynArray& rhs);
public:
	bool isEmpty()const{ return size == 0; }
	void pushBack(const T& val);
	T& operator[](size_t index);
	const T& operator[](size_t index)const;
	size_t getSize()const{ return size; }

private:
	void resize();
	void copyFrom(const DynArray& rhs);

private:
	static const size_t DEFAULT_CAPACITY = 4;
private:
	T* arr;
	size_t size;
	size_t capacity;
};


template<class T>
DynArray<T>::DynArray() :arr(new T[DEFAULT_CAPACITY]), capacity(DEFAULT_CAPACITY), size(0){}

template<class T>
DynArray<T>::DynArray(const DynArray& rhs) : arr(NULL), capacity(0), size(0)
{
	copyFrom(rhs);
}


template<class T>
DynArray<T>::~DynArray()
{
	delete[] arr;
}

template <class T>
DynArray<T>& DynArray<T>::operator=(const DynArray& rhs)
{
	if (this != &rhs)
	{
		copyFrom(rhs);
	}

	return *this;
}

template <class T>
void DynArray<T>::pushBack(const T& val)
{
	arr[size++] = val;
	if (size == capacity)
	{
		resize();
	}
}

template <class T>
T& DynArray<T>::operator[](size_t index)
{
	if (index < 0 || index >= size)
	{
		throw "Index out of range";
	}

	return arr[index];
}

template <class T>
const T& DynArray<T>::operator[](size_t index)const
{
	if (index < 0 || index >= size)
	{
		throw "Index out of range";
	}

	return arr[index];
}

template <class T>
void DynArray<T>::resize()
{
	capacity *= 2;
	T* newArr = new T[capacity];
	for (size_t i = 0; i < size; i++)
	{
		newArr[i] = arr[i];
	}
	delete[] arr;
	arr = newArr;
}

template <class T>
void DynArray<T>::copyFrom(const DynArray& rhs)
{
	if (rhs.capacity != capacity)
	{
		delete[] arr;
		arr = new T[rhs.capacity];
	}

	for (size_t i = 0; i < rhs.size; ++i)
	{
		arr[i] = rhs.arr[i];
	}

	size = rhs.size;
}

#endif
