#ifndef _STACK_H
#define _STACK_H

template<class T>
class Stack
{
public:
	Stack();
	Stack(const Stack& rhs);
	Stack& operator=(const Stack& rhs);
	~Stack();
public:
	bool isEmpty(){ return size == 0; }
	void push(const T& data);

	T& top();
	const T& top()const;

	void pop();
private:
	void copyFrom(const Stack& rhs);
	void resize();
private:
	static const size_t DEFAULT_CAPACITY = 8;
private:
	T* arr;
	size_t size;
	size_t capacity;
};


template<class T>
Stack<T>::Stack() :arr(new T[DEFAULT_CAPACITY]), size(0), capacity(DEFAULT_CAPACITY)
{}

template<class T>
Stack<T>::Stack(const Stack& rhs) : arr(NULL), size(0), capacity(0)
{
	copyFrom(rhs);
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack& rhs)
{
	if (this != *rhs)
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
void Stack<T>::push(const T& data)
{
	arr[size++] = data;
	if (size == capacity)
	{
		resize();
	}
}

template<class T>
T& Stack<T>::top()
{
	if (isEmpty())
	{
		throw "Empty Stack.";
	}

	return arr[size - 1];
}

template<class T>
const T& Stack<T>::top()const
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
void Stack<T>::copyFrom(const Stack& rhs)
{
	if (capacity != rhs.capacity)
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

template<class T>
void Stack<T>::resize()
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

#endif
