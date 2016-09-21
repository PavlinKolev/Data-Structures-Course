#include "Tree.h"
#include "TreesIsomorphism.h"
#include<iostream>

int main()
{
	try
	{
		char str[128];
		std::cin.getline(str, 128);
		Tree tree1(str);

		std::cin.getline(str, 128);
		Tree tree2(str);

		if (TreesIsomorphism::isomorphicTrees(tree1, tree2))
		{
			std::cout << "\nYes. Isomorphic." << std::endl;
		}
		else
		{
			std::cout << "\nNo. Not Isomorphic." << std::endl;
		}
	}
	catch (char* message)
	{
		std::cout << message << std::endl;
	}

	return 0;
}