
#ifndef List_H
#define List_H
#include<iostream>
#include <assert.h>
#include "Iterator.h"
using namespace std;

template<class T>
class List
{
private:
	Node<T> *First;
	Node<T> *Last;
	size_t size;
public:
	List();
	List(List const &);
	List & operator=(List const &);
	~List();
private:
	//Destroys all elements of the List
	void Destroy();

	//Initializes the List members. The List is Empty and ready to work with it.
	void Init();

	//Copies the element of source list to this list
	//This list must be initialize with init() before that.
	void CopyFrom(List const &);
public:
	bool isEmpty() const;
	size_t getSize() const;

	//Push an element after last emenent. The pushed element becomes the last(newest) element for the List.
	void push(T const &);

	//Delete the last(the newest) element and return its data
	T pop_back();

	//Dete the first(the oldest) element and return its data
	T pop_front();

	Iterator<T> begin()
	{
		return Iterator<T>(this->First);
	}

	template<class V>
	//Sorts a List whichs elements are other Lists
	//Lis< T=List<V> >::SortListOfLists(List< T=List<V> >& toBeSorted)
	//toBeSorted will be sorted by size of its elements(by size of every List in toBeSorted)
	static void SortListOfLists(List<List<V>>& toBeSorted);

	template<class V>
	//Does MergeSort for a List which elements are other Lists
	static void mergeSort(Node<List<V>>*&);

	template<class V>
	//Divides a List of List on two halfs
	static void partition(Node<List<V>>*, Node<List<V>>*&);

	template<class V>
	//Merge a Lists of Lists in one List of List, and returns a Node_pointer pointers to the first element of the merged List
	static Node<List<V>>* mergeList(Node<List<V>>*, Node<List<V>>*);
};

template<class T>
List<T>::List()
{
	Init();
}

template<class T>
List<T>::List(List const & list)
{
	Init();
	CopyFrom(list);
}

template<class T>
List<T> & List<T>::operator=(List const & list)
{
	if (this != &list)
	{
		Destroy();
		Init();
		CopyFrom(list);
	}
	return *this;
}

template<class T> 
List<T>::~List()
{
	Destroy();
	Init();
}

template<class T>
void List<T>::CopyFrom(List const & src)
{
	if (src.size == 0)//No elements to copy
	{
		return;
	}
	Node<T> *p1 = NULL;
	Node<T> *p2 = NULL;

	//Creates a Node with a copy of data, from the first element of src
	//and this Node is pointered by this->First
	this->First = new Node<T>(src.First->data);

	p1 = this->First;//p1 will go through elements of this List
	p2 = src.First->next;//p2 will go through elements of source List

	while (p2)
	{
		p1->next = new Node<T>(p2->data);
		p1 = p1->next;
		p2 = p2->next;
	}
	this->Last = p1;
	this->size = src.size;
}

template<class T>
void List<T>::Init()
{
	this->First = NULL;
	this->Last = NULL;
	this->size = 0;
}

template<class T>
void List<T>::Destroy()
{
	Node<T> *p1 = this->First;
	Node<T> *p2 = NULL;//p2 is one element behind p1

	while (p1)
	{
		p2 = p1;
		p1 = p1->next;
		delete p2;
	}
}


template<class T>
bool List<T>::isEmpty() const
{
	return (this->size == 0);
}

template<class T>
size_t List<T>::getSize() const
{
	return this->size;
}

template<class T>
void List<T>::push(T const & elem)
{
	//Step 1
	//Creates a Node with data like elem, and next pointers to NULL
	Node<T> *temp = new Node<T>(elem);

	if (temp == NULL)
	{
		throw "New returned NULL at List.push()";
	}

	if (this->isEmpty())
	{
		//Step 2
		//We have only one Node - First and Last are pointering to it
		this->First = temp;
		this->Last = temp;
	}
	else
	{
		//Step 2
		//The new Node is pointered by Last->next
		this->Last->next = temp;
		//Step 3
		//The new Node becomes Last for the List
		this->Last = temp;
	}
	this->size++;

}

template<class T>
T List<T>::pop_back()
{
	//If pop_back() is called on empty List
	assert(!this->isEmpty());

	T elem = this->Last->data;
	if (this->size == 1)
	{
		Destroy();
		Init();
	}
	else
	{
		Node<T> *p = this->First;
		while (p->next != this->Last)
		{
			//This Loop will stop when p becomes the element before Last
			p = p->next;
		}
		p->next = NULL;
		delete this->Last;
		Last = p;
		this->size--;
	}
	return elem;
}

template<class T>
T List<T>::pop_front()
{
	//If pop_front() is called on empty  List
	assert(!this->isEmpty());

	T elem = this->First->data;
	Node<T> *p = this->First;
	this->First = this->First->next;
	if (this->First == NULL)
	{
		//If there is only one element before calling pop_front()
		this->Last = NULL;
	}
	delete p;
	this->size--;
	return elem;
}

template<class T>
template<class V>
void List<T>::SortListOfLists(List<List<V>>& list)
{
	//Calls mergeSort with first element of the list
	//so after mergeSort, the elements of the list will be sorted, 
	//and the first one will be pointered by list.First
	mergeSort(list.First);
}

template<class T>
template<class V>
//It takes Node_pointer& so the changes that are made on source will reflect to the Node_pointer with which is called mergeSort
void List<T>::mergeSort(Node<List<V>>*& source)
{
	Node<List<V>>* left = source;
	Node<List<V>>* right = NULL;

	if (!source || !(source->next))
	{
		return;
	}
	//Divides the List on two halfs, and after partition
	//right will be the start of the second half
	partition(source, right);

	mergeSort(left);
	mergeSort(right);

	source = mergeList(left, right);
}

template<class T>
template<class V>
void List<T>::partition(Node<List<V>>* head, Node<List<V>>*& back)
{
	Node<List<V>>* fast;
	Node<List<V>>* slow;

	if (!head || !(head->next))
	{
		back = NULL;
	}
	else
	{
		slow = head;
		fast = head->next;

		//In this Loop fast makes twice more steps than slow,
		//so after the loop, fast will be reached the end of List
		//and slow will be on twice steps behind - which is exactly the middle of the List
		while (fast)
		{
			fast = fast->next;
			if (fast)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		back = slow->next;
		slow->next = NULL;
	}
}

template<class T>
template<class V>
Node<List<V>>* List<T>::mergeList(Node<List<V>>* left, Node<List<V>>* right)
{
	Node<List<V>>*merged = NULL;

	//If left is NUll - we have taken all of the elements of left List
	//so we can takes only elements of the right list
	if (!left)
	{
		return right;
	}
	else if (!right)
	{
		return left;
	}

	//Compares by data.getSize(), because data is also a List
	if (left->data.getSize() < right->data.getSize())
	{
		merged = left;
		merged->next = mergeList(left->next, right);
	}
	else
	{
		merged = right;
		merged->next = mergeList(left, right->next);
	}

	return merged;
}
#endif