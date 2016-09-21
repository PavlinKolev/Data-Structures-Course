#ifndef _ISOMORPHISM_H
#define _ISOMORPHISM_H
#include "Tree.h"
#include "Stack.h"
#include "Queue.h"

//Information about the algorithm for Tree Isomorphoism:
//http://crypto.cs.mcgill.ca/~crepeau/CS250/2004/HW5+.pdf

class TreesIsomorphism
{
public:
	static bool isomorphicTrees(const Tree& tree1, const Tree& tree2);

private:
	//"stack" contains the nodes in order of their founding with BFS. Two levels from BFS inside "stack" are separated with NULL.
	//This function writes the number of children of all nodes in one level, after that arr is being sorted.
	static void getChildrenCounts(Stack<Vertex*>& stack, int* arr, size_t& size);

	//Goes trough the levels in the stacks and checks if all levels are isomorphic. Both stacks contains the nodes of trees with equals heights.
	static bool isomorphicStacksOfVertexs(Stack<Vertex*>& stack_1, Stack<Vertex*>& stack_2, size_t treeHeigh);

private:
	TreesIsomorphism();
	TreesIsomorphism(const TreesIsomorphism&);
	TreesIsomorphism& operator=(const TreesIsomorphism&);
	~TreesIsomorphism();
};

void CountingSort(int* arr, size_t size);

#endif
