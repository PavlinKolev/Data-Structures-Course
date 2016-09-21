#ifndef _QUEUE_H
#define _QUEUE_H
#include <iostream>

template<class T>
class Queue;

template<class T>
class Node
{
	friend class Queue<T>;
public:
	Node(const T& v, Node* n = NULL) :val(v), next(n){}
private:
	Node(const Node&);
	Node& operator=(const Node&);
private:
	T val;
	Node* next;
};

template<class T>
class Queue
{
public:
	Queue();
	Queue(const Queue& rhs);
	Queue& operator=(const Queue& rhs);
	~Queue();
public:
	bool isEmpty()const{ return head == NULL; }
	T& getHead();
	const T& getHead()const;
	void pop();
	void push(const T& val);
private:
	void copy(Node<T>* node);
	void free(Node<T>* node);
private:
	Node<T>* head;
	Node<T>* tail;
};

template <class T>
Queue<T>::Queue() :head(NULL), tail(NULL){}

template <class T>
Queue<T>::Queue(const Queue<T>& rhs) : head(NULL), tail(NULL)
{
	copy(rhs.head);
}
template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& rhs)
{
	if (this != &rhs)
	{
		free(head);
		copy(rhs.head);
	}

	return *this;
}

template <class T>
Queue<T>::~Queue()
{
	free(head);
}

template<class T>
T& Queue<T>::getHead()
{
	if (isEmpty())
	{
		throw "Empty Queue.";
	}

	return head->val;
}

template<class T>
const T& Queue<T>::getHead() const
{
	if (isEmpty())
	{
		throw "Empty Queue.";
	}

	return head->val;
}

template<class T>
void Queue<T>::pop()
{
	if (isEmpty())
	{
		throw "Empty Queue.";
	}

	Node<T>* toDelete = head;
	head = head->next;
	delete toDelete;
	if (isEmpty())
	{
		tail = head;
	}
}

template<class T>
void Queue<T>::push(const T& val)
{
	if (isEmpty())
	{
		head = (tail = new Node<T>(val));
	}
	else
	{
		tail->next = new Node<T>(val);
		tail = tail->next;
	}
}

template<class T>
void Queue<T>::copy(Node<T>* node)
{
	if (node == NULL)
	{
		return;
	}

	push(node->val);
	copy(node->next);
}

template<class T>
void Queue<T>::free(Node<T>* node)
{
	if (node == NULL)
	{
		return;
	}

	free(node->next);
	delete node;
}

#endif
