#ifndef _ITERATOR_H
#define _ITERATOR
#include "Node.h"

template<class T>
class List;

template<class T>
class Iterator
{
	friend class List<T>;
public:
	Iterator(const Iterator& rhs) :pointer(rhs.pointer){}
	Iterator& operator=(const Iterator& rhs);
public:
	bool operator==(const Iterator& rhs){ return pointer == rhs.pointer; }
	bool operator!=(const Iterator& rhs){ return !(*this == rhs); }

	operator bool(){ return pointer != NULL; }
	Iterator& operator++();

	T& operator*(){ return pointer->val; }
	T* operator->(){ return &(pointer->val); }

private:
	Iterator(Node<T>* n) :pointer(n){}
	Node<T>* pointer;
};

template<class T>
Iterator<T>& Iterator<T>::operator=(const Iterator& rhs)
{
	if (this != &rhs)
	{
		this->pointer = rhs.pointer;
	}

	return *this;
}

template<class T>
Iterator<T>& Iterator<T>::operator++()
{
	if (pointer)
	{
		pointer = pointer->next;
	}

	return *this;
}

#endif