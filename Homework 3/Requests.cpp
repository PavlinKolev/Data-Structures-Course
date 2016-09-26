#include "Requests.h"

void runProgram()
{
	size_t testsCount;
	cin >> testsCount;

	for (size_t i = 0; i < testsCount; i++)
	{
		singleTest();
	}
}

void singleTest()
{
	size_t stringsCount;
	size_t requestsCount;

	cin >> stringsCount;
	cin >> requestsCount;

	Vector<String> strings(stringsCount);

	for (size_t i = 0; i < stringsCount; i++)
	{
		char buffer[8];
		cin >> buffer;
		strings.addBack(buffer);
	}

	strings.MergeSort();

	size_t start = 0;
	size_t end = stringsCount - 1;

	for (size_t i = 0; i < requestsCount; i++)
	{
		executeRequest(strings, start, end);
	}
}

void executeRequest(Vector<String>& strings, size_t& start, size_t& end)
{
	char request[8];
	cin >> request;

	if (strcmp(request, "ENTER") == 0)
	{
		cin >> start;
		cin >> end;
	}
	else if (strcmp(request, "QUERY") == 0)
	{
		char prefix[8];
		cin >> prefix;

		size_t prefMeets = 0;
		for (size_t i = start; i <= end; i++)
		{
			if (strings[i].checkPefix(prefix))
				prefMeets++;
		}

		cout << prefMeets << endl;
	}
	else
	{
		cout << "Wrong request.\n";
	}
}
