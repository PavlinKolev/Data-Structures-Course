#ifndef _Vertex_H
#define _Vertex_H
#include "DynArray.h"

class Vertex
{
	friend class Tree;
public:
	Vertex(int n) :number(n){}
	size_t getChildrenCount(){ return children.getSize(); }

private:
	int number;
	DynArray<Vertex*> children;
private:
	Vertex(const Vertex&);
	Vertex& operator=(const Vertex&);
};

#endif
