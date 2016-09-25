#ifndef _LIST_H
#define _LIST_H
#include "Node.h"
#include "Iterator.h"
#include <iostream>

template<class T>
class List
{
public:
	List();
	List(const List& rhs);
	List& operator=(const List& rhs);
	~List();
public:
	void free();
	T* front(){ return &(head->val); }
	T* back(){ return &(tail->val); }
	const T* front()const{ return &(head->val); }
	const T* back()const{ return &(tail->val); }

	List& operator+=(const List& rhs);
	List operator+(const List& rhs)const;

	void addBack(const T& val);
	void removeAt(size_t pos);
	void insertAt(const T& val, size_t pos);

	//Adds the elements of "rhs" from position "pos"
	void append(const List& rhs, size_t pos);

	bool isEmpty()const{ return size == 0; }
	Iterator<T> begin() const{ return Iterator<T>(head); }

private:
	void copy(Node<T>* node);
	void free(Node<T>* node);
private:
	Node<T>* head;
	Node<T>* tail;
	size_t size;
};


template<class T>
List<T>::List() :head(NULL), tail(NULL), size(0){}

template<class T>
List<T>::List(const List& rhs) : head(NULL), tail(NULL), size(0)
{
	copy(rhs.head);
}

template<class T>
List<T>& List<T>::operator=(const List& rhs)
{
	if (this != &rhs)
	{
		free(head);
		head = tail = NULL;
		size = 0;
		copy(rhs.head);
	}
	return *this;
}

template<class T>
List<T>::~List()
{
	free(head);
}

template<class T>
void List<T>::free()
{
	free(head);
	head = tail = NULL;
	size = 0;
}

template<class T>
List<T>& List<T>::operator+=(const List& rhs)
{
	Node<T>* node = rhs.head;
	while (node)
	{
		addBack(node->val);
		node = node->next;
	}

	return *this;
}

template<class T>
List<T> List<T>::operator+(const List& rhs)const
{
	List<T> temp(*this);
	temp += rhs;

	return temp;
}

template<class T>
void List<T>::free(Node<T>* node)
{
	if (node == NULL)
	{
		return;
	}
	free(node->next);
	delete node;
}

template<class T>
void List<T>::addBack(const T& val)
{
	if (isEmpty())
	{
		head = tail = new Node<T>(val);
	}
	else
	{
		tail->next = new Node<T>(val);
		tail = tail->next;
	}
	size++;
}

template<class T>
void List<T>::removeAt(size_t pos)
{
	if (pos >= size)
	{
		throw "Index out of range.";
	}
	if (pos == 0)
	{
		Node<T>* toRemove = head;
		head = head->next;
		if (head == NULL)
		{
			tail = NULL;
		}
		delete toRemove;
	}
	else
	{
		pos--;
		Node<T>* node = head;
		while (pos)
		{
			node = node->next;
			pos--;
		}
		Node<T>* toRemove = node->next;
		node->next = toRemove->next;
		if (toRemove->next == NULL)
		{
			tail = node;
		}
		delete toRemove;
	}
	size--;
}

template<class T>
void List<T>::insertAt(const T& val, size_t pos)
{
	if (pos > size)
	{
		throw "Index out of range.";
	}
	if (pos == 0)
	{
		Node<T>* temp = new Node<T>(val);
		temp->next = head;
		head = temp;
		if (head->next == NULL)
		{
			tail = head;
		}
		size++;
		return;
	}
	pos--;
	Node<T>* node = head;
	while (pos)
	{
		node = node->next;
		pos--;
	}
	Node<T>* temp = node->next;
	node->next = new Node<T>(val);
	node->next->next = temp;
	if (temp == NULL)
	{
		tail = node->next;
	}
	size++;
}

template<class T>
void List<T>::append(const List& rhs, size_t pos)
{
	if (pos >= rhs.size)
	{
		throw "Index out of range.";
	}
	Node<T>* node = rhs.head;

	while (pos)
	{
		node = node->next;
		pos--;
	}

	copy(node);
}

template<class T>
void List<T>::copy(Node<T>* node)
{
	if (node == NULL)
	{
		return;
	}
	addBack(node->val);
	copy(node->next);
}

#endif
