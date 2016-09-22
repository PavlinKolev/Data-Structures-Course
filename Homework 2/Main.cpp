#include<iostream>
#include "Labyrinth.h"
using namespace std;

int main()
{
	//Maximum cells in Matrix
	short const maxSize = 256;

	short N, M, x, y;
	char * matrix;

	try
	{
		cout << "Enter N and M: \n";
		cin >> N >> M;
		if (N < 0 || M < 0)
		{
			throw "N and M must e positive numbers";
		}
		if (N*M>maxSize)
		{
			throw "Too large Matrix.";
		}
		matrix = new char[N*M];
		cout << "Enter the matrix:\n";
		for (int i = 0; i < N*M; i++)
		{
			cin >> matrix[i];
		}
		cout << "Enter StartPoint: (X,Y)\n";
		cin >> x >> y;
		cout << endl;

		//Setting the Labyrinth
		Labyrinth *lab = Labyrinth::getInstance(matrix, N, M, x,y);

		lab->BFS();
		lab->getAllPaths();

		cout << endl << endl;
		lab->ReadData();
		cout << endl;
		delete[]matrix;
	}
	catch (char * ex)
	{
		cout << ex << endl;
	}

	return 0;

}