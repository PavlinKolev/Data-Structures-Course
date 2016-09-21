#include "Tree.h"

Tree::Tree(const char* str) :root(NULL)
{
	if (!Tree::correctString(str))
	{
		throw "Not correct string for tree.";
	}

	root = setTree(str);
}

Tree::Tree(const Tree& rhs) :root(NULL)
{
	root = new Vertex(rhs.root->number);
	copy(root, rhs.root);
}

Tree& Tree::operator=(const Tree& rhs)
{
	if (this != &rhs)
	{
		free(root);
		root = new Vertex(rhs.root->number);
		copy(root, rhs.root);
	}

	return *this;
}

Tree::~Tree()
{
	free(root);
}

size_t Tree::BFS_inStack(Stack<Vertex*>& stack)const
{
	if (!root)
	{
		return 0;
	}
	size_t heigh = 0;
	Queue<Vertex*> queue;
	queue.push(root);
	queue.push(NULL);

	stack.push(root);
	stack.push(NULL);

	visitTheVertexs(queue, stack, heigh);

	return heigh;
}

void Tree::visitTheVertexs(Queue<Vertex*>& queue, Stack<Vertex*>& stack, size_t& heigh)const
{
	while (!queue.isEmpty())
	{
		Vertex* v = queue.getHead();
		queue.pop();

		if (v == NULL)
		{
			if (queue.isEmpty())
			{
				stack.pop();
				return;
			}
			queue.push(NULL);
			stack.push(NULL);
			heigh++;
			continue;
		}

		size_t vertexChildren = v->children.getSize();
		for (size_t i = 0; i < vertexChildren; ++i)
		{
			queue.push(v->children[i]);
			stack.push(v->children[i]);
		}
	}
}

Vertex* Tree::setTree(const char*& str)
{
	const char* end = getEnd(str, '(', ')');
	end--;
	str++;//Skip the symbol '(', before the number

	int number = atoi(str);
	Vertex* vertex = new Vertex(number);//Create a node with the founded number
	moveAfterAtoi(str, number);

	setChildren(vertex->children, str, end);//Fills the info about the children of the new node

	return vertex;
}

void Tree::setChildren(DynArray<Vertex*>& arr, const char*& str, const char* end)
{
	str++;//Skipping the symbol '{'
	while (str < end)
	{
		Vertex* child = setTree(str);
		arr.pushBack(child);
	}
	str = end + 3;//Skipping the symbols ")} "
}

void Tree::free(Vertex* Vertex)
{
	if (Vertex->children.isEmpty())
	{
		delete Vertex;
		return;
	}
	size_t childCount = Vertex->children.getSize();
	for (size_t i = 0; i < childCount; ++i)
	{
		free(Vertex->children[i]);
	}

	delete Vertex;
}

void Tree::copy(Vertex* dest, Vertex* source)
{
	if (source->children.isEmpty())
	{
		return;
	}

	size_t sourceChildren = source->children.getSize();

	for (size_t i = 0; i < sourceChildren; i++)
	{
		dest->children.pushBack(new Vertex(source->children[i]->number));
		copy(dest->children[i], source->children[i]);
	}
}

bool Tree::correctString(const char* string)
{
	if (!string)
	{
		return false;
	}
	return correctTree(string);
}

bool Tree::correctTree(const char*& string)
{
	if (*string != '(')//The first symbol of tree must be '('
		return false;
	string++;
	int number = atoi(string);
	moveAfterAtoi(string, number);

	if (!correctChildren(string))
	{
		return false;
	}
	string++;//Goes to the last symbol of the tree
	if (*string != ')')
	{
		return false;
	}
	else
	{
		string++;//Skips an interval between two trees(children to same parent)
		return true;
	}

}

bool Tree::correctChildren(const char*& string)
{
	const char* end = getEnd(string, '{', '}');
	string++;
	while (string < end)
	{
		if (!correctTree(string))
			return false;
		if (*string != '}')//If the "end" of children's info is not reached 
			string++;
	}
	return true;
}

void moveAfterAtoi(const char*& str, int number)
{
	while (number)
	{
		number /= 10;
		str++;
	}

	if (*str == ' ')
		str++;
}

const char* getEnd(const char* str, char startSymol, char endSymbol)
{
	int count = 1;
	str++;
	while (*str && count)
	{
		if (*str == startSymol)
			count++;
		if (*str == endSymbol)
			count--;
		str++;
	}

	return str - 1;
}
