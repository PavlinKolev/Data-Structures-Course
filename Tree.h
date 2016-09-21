#ifndef _TREE_H
#define _TREE_H
#include "Vertex.h"
#include "Stack.h"
#include "Queue.h"
#include <iostream>

class Tree
{
public:
	Tree(const char* str);
	Tree(const Tree& rhs);
	Tree& operator=(const Tree& rhs);
	~Tree();
public:
	size_t BFS_inStack(Stack<Vertex*>& stack)const;//Inserts the nodes in the stack in the order which are founded with BFS and returns the height of the tree

private:
	void visitTheVertexs(Queue<Vertex*>&, Stack<Vertex*>&,size_t&)const;
	Vertex* setTree(const char*& str);//Creates a tree from the string "str" and returns a pointer to it's roof
	void setChildren(DynArray<Vertex*>& arr, const char*& str, const char* end);
	void free(Vertex* Vertex);
private:
	static void copy(Vertex* dest, Vertex* source);//Copyes a tree with roof "source" in tree with roof "dest"
	static bool correctString(const char* string);
	static bool correctTree(const char*& string);
	static bool correctChildren(const char*& string);
private:
	Vertex* root;
};

void moveAfterAtoi(const char*& str, int number);
const char* getEnd(const char* str, char startSymol, char endSymbol);

#endif
