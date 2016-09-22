#ifndef Iterator_H
#define Iterator_H
#include "Node.h"

template<class T>
class List;

template<class T>
class Iterator
{
private:
	Node<T>* pointer;
	Iterator()
	{
		pointer = NULL;
	}
	Iterator(Node<T>*src)//Private, because only friend class can have an access and creates Iterators
	{
		this->pointer = src;
	}
public:
	friend class List<T>;//List must have access to the private Iterator constructor

	~Iterator()
	{
		pointer = NULL;
	}

	Iterator(const Iterator & src)
	{
		this->pointer = src.pointer;
	}

	Iterator & operator =(const Iterator & src)
	{
		this->pointer = src.pointer;
		return *this;
	}
	//Allow to change data in List
	T & operator *()
	{
		return pointer->data;
	}

	bool operator ==(const Iterator & it)
	{
		return this->pointer == it.pointer;
	}

	operator bool()
	{
		return this->pointer != NULL;
	}
	//Operator ++ does nothing if pointer pointers to NULL
	Iterator & operator ++()
	{
		if (pointer)
		{
			pointer = pointer->next;
		}
		return *this;
	}
	//Returns the adress of data
	T* operator->()
	{
		return &(pointer->data);
	}

};

#endif