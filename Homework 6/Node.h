#ifndef _NODE_H
#define _NODE_H
#include<iostream>

template<class T>
class List;

template<class T>
class Iterator;

template<class T>
class Node
{
	friend class List<T>;
	friend class Iterator<T>;
public:
	Node(const T& v, Node* n = NULL) :val(v), next(n){}
private:
	T val;
	Node* next;
private:
	Node(const Node&);
	Node& operator=(const Node&);
};

#endif