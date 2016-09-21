#include "TreesIsomorphism.h"

bool TreesIsomorphism::isomorphicTrees(const Tree& tree1, const Tree& tree2)
{
	Stack<Vertex*> BFS_tree1;
	size_t heigh1 = tree1.BFS_inStack(BFS_tree1);

	Stack<Vertex*> BFS_tree2;
	size_t heigh2 = tree2.BFS_inStack(BFS_tree2);

	if (heigh1 != heigh2)
	{
		return false;
	}

	return isomorphicStacksOfVertexs(BFS_tree1, BFS_tree2, heigh1);

}

bool TreesIsomorphism::isomorphicStacksOfVertexs(Stack<Vertex*>& stack_1, Stack<Vertex*>& stack_2, size_t treeHeigh)
{
	while (treeHeigh)
	{
		int childrenCounts_1[32];
		int childrenCounts_2[32];
		size_t size1 = 0;
		size_t size2 = 0;

		getChildrenCounts(stack_1, childrenCounts_1, size1);
		getChildrenCounts(stack_2, childrenCounts_2, size2);

		if (size1 != size2)
		{
			return false;
		}

		for (int i = 0; i < size1; i++)
		{
			if (childrenCounts_1[i] != childrenCounts_2[i])
			{
				return false;
			}
		}

		treeHeigh--;
	}

	return true;
}

void TreesIsomorphism::getChildrenCounts(Stack<Vertex*>& stack, int* arr, size_t& size)
{
	Vertex* v = stack.getTop();
	stack.pop();

	while (v != NULL && !stack.isEmpty())
	{
		int childrenCount = v->getChildrenCount();
		arr[size++] = childrenCount;

		v = stack.getTop();
		stack.pop();
	}

	CountingSort(arr, size);
}

void CountingSort(int* arr, size_t size)
{
	const size_t MaxIndex = 32;
	int counting[MaxIndex] = { 0 };

	for (size_t i = 0; i < size; i++)
	{
		counting[arr[i]]++;
	}

	size_t arrIndex = 0;
	for (size_t i = 0; i < 32; i++)
	{
		while (counting[i])
		{
			arr[arrIndex++] = i;
			counting[i]--;
		}
	}
}
