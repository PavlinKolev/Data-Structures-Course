#include <iostream>
#include <fstream>
#include "CSV_Matrix.h"

bool correctCSV(const char* fileName)
{
	if (!fileName)
	{
		return false;
	}
	size_t size = strlen(fileName);
	char csv[] = ".csv";
	if (size < strlen(csv)+1)
	{
		return false;
	}

	for (int i = strlen(csv)-1; i >= 0; --i)
	{
		if (csv[i] != fileName[--size])
		{
			return false;
		}
	}

	return true;
}

int main(int argc, char* argv[])
{
	if (correctCSV(argv[argc-1]))
	{
		CSV_Matrix matrix(argv[argc-1]);

		matrix.peopleToPeople();
		matrix.GroupToGroup();
		matrix.Closeness();
	}

	return 0;
}