#ifndef Node_H
#define Node_H

template<class T>
class List;

template<class T>
class Iterator;

template<class T>
class Node
{
private:
	T data;
	Node *next;
	Node(){}
public:
	Node(T const & data, Node *next = NULL)
	{
		this->data = data;
		this->next = next;
	}
	//List and Iterator must have access to data and next
	friend class List<T>;
	friend class Iterator<T>;
};

#endif