#ifndef _STACK_H_
#define _STACK_H_
#include <iostream>

template<class T>
class Stack
{
public:
	Stack();
	Stack(const Stack& rhs);
	~Stack();
	Stack& operator=(const Stack& rhs);
public:
	bool isEmpty()const{ return size == 0; }
	T& getTop();
	const T& getTop()const;
	void pop();
	void push(const T& val);
private:
	void copyFrom(const Stack<T>& rhs);
	void resize();
private:
	static const size_t DEFAULT_CAPACITY = 16;
private:
	T* arr;
	size_t size;
	size_t capacity;
};

template <class T>
Stack<T>::Stack() :arr(new T[DEFAULT_CAPACITY]), size(0), capacity(DEFAULT_CAPACITY){}

template<class T>
Stack<T>::Stack(const Stack<T>& rhs) : arr(NULL), size(0), capacity(0)
{
	copyFrom(rhs);
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs)
{
	if (this != &rhs)
	{
		copyFrom(rhs);
	}

	return *this;
}

template<class T>
Stack<T>::~Stack()
{
	delete[] arr;
}

template<class T>
T& Stack<T>::getTop()
{
	if (isEmpty())
	{
		throw "Empty Stack.";
	}

	return arr[size - 1];
}

template<class T>
const T& Stack<T>::getTop() const
{
	if (isEmpty())
	{
		throw "Empty Stack.";
	}

	return arr[size - 1];
}

template<class T>
void Stack<T>::pop()
{
	if (isEmpty())
	{
		throw "Empty Stack.";
	}

	size--;
}

template<class T>
void Stack<T>::push(const T& val)
{
	arr[size++] = val;
	if (size == capacity)
	{
		resize();
	}
}

template<class T>
void Stack<T>::copyFrom(const Stack<T>& rhs)
{
	if (capacity != rhs.capacity)
	{
		delete[] arr;
		capacity = rhs.capacity;
		arr = new T[capacity];
	}

	for (size_t i = 0; i < rhs.size; ++i)
	{
		arr[i] = rhs.arr[i];
	}
	
	size = rhs.size;
}

template<class T>
void Stack<T>::resize()
{
	capacity *= 2;
	T* newArr = new T[capacity];
	for (size_t i = 0; i < size; ++i)
	{
		newArr[i] = arr[i];
	}

	delete[] arr;
	arr = newArr;
}
#endif
