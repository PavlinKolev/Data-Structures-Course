#include "Labyrinth.h"

short const Labyrinth::MaxSize = 256;
bool Labyrinth::isCreated = false;
Labyrinth* Labyrinth::single = NULL;
int const Labyrinth::MaxDFSsteps = 10000;

Labyrinth* Labyrinth::getInstance(char* array, short N, short M, short row, short col)
{
	if (!isCreated)
	{
		single = new Labyrinth(array, N, M, row, col);
		isCreated = true;
	}
	return single;
}

Labyrinth::Labyrinth(char *array, short N, short M, short row, short col)
{
	if (N <= 0 || M <= 0 || N*M > MaxSize)
	{
		throw "Number of rows or number of cols is not a valid number!";
	}
	if (row < 0 || col < 0 || row >= N || col >= M)
	{
		throw "The startPoint is outside the Labyrinth!";
	}
	this->matrix = new char[N*M];

	for (int i = 0; i < N*M; i++)
	{
		this->matrix[i] = array[i];
	}
	this->N = N;
	this->M = M;
	this->startPoint = row*M + col;
}

Labyrinth::~Labyrinth()
{
	delete[] this->matrix;
	isCreated = false;
}

short Labyrinth::getNeighboor(short currentPoint, int index)
{
	// moves[]: direction | displacement
	//			-----------------------
	//		down	0	  | + M //M-number of columns
	//		left	1	  | -1 
	//		up		2	  | -M
	//		right	3	  |	+1
	short moves[] = { M, -1, -M, 1 };

	short neighboor = currentPoint + moves[index];

	//Because I work with one-dimensional array there is have to be these cheks
	//if(dir is LEFT and I am on COL 0) ||(dir is RIGHT and I am on COL M-1)||(dir is DOWN and I am on ROW N-1) ||(dir is UP and I am on ROW 0)
	if ((index == 1 && currentPoint%M == 0) || (index == 3 && (currentPoint + 1) % M == 0) || (index == 0 && currentPoint >= M*(N - 1)) || (index == 2 && currentPoint < M))
	{
		neighboor = -1;
	}
	return neighboor;
}

bool Labyrinth::isValid(short point)
{
	//Chek if point is outside matrix and if it is passable
	return ((point >= 0) && (point < N*M) && (matrix[point] != '#'));
}

void Labyrinth::BFS()
{
	if (matrix[startPoint] == '#')
	{
		std::cout << "Start position is '#'. No pass trough '#'.\n";
		return;
	}
	bool noPasses = true;

	//If BFS went through a point, this point becomes visited in matrix
	char const visited = '!';

	//-1 is the delimiter wich is pushed in queueBFS,after we passed trough all points in one level
	short const delim = -1;

	int const movesCount = 4;

	//queueBFS will be used as queue wich holds points founded from BFS
	//We push point in back, and pop point in front
	//In every single moment queueBFS will have points from maximum two levels
	List<short> queueBFS;

	//Push the startPoint in queueBFS
	queueBFS.push(startPoint);

	//Make starPoint visited
	matrix[startPoint] = visited;

	//Push delim in queueBFS - Level 0 from BFS is ready
	queueBFS.push(delim);

	while (!queueBFS.isEmpty())
	{
		//Get the current point, and remove that point from queueBFS
		short current = queueBFS.pop_front();

		if (current != delim)
		{
			//Generate all 4 neighbours
			for (int i = 0; i < movesCount; i++)
			{
				short neighboor = getNeighboor(current, i);

				if (isValid(neighboor) && matrix[neighboor] != visited)
				{
					if (noPasses)
					{
						cout << "All passable points\n--------------------\n";
						noPasses = false;
					}

					//Push the founded point to queue
					queueBFS.push(neighboor);

					//Here we save ALL points founded from BFS
					pointsFromBFS.push(neighboor);

					writePoint(neighboor);

					//Make the founded point visited
					matrix[neighboor] = visited;
				}
			}
		}
		else
		{
			//If the last point we poped is delim
			//and the queue is Empty - the BFS is finished
			if (queueBFS.isEmpty())
			{
				break;
			}
			//Else we finished one level and we have to push delim
			queueBFS.push(delim);
		}
	}
	if (noPasses)
	{
		cout << "No passable cells found.\n";
	}
}

void Labyrinth::writePoint(short point)
{
	int row = ((int)point) / M;
	int col = ((int)point) % M;
	std::cout << "(" << row << "," << col << ") ";
}

void Labyrinth::DFS(short start, short final, List<List<short>>& allPaths, List<short>&singlePath, int & steps)
{
	steps++;//Counting the steps - the number of caling DFS recursively
	if (steps > MaxDFSsteps)
	{
		throw "\nDFS goes to deeper. There will be too many paths for each reachable point.";
	}

	int const movesCount = 4;

	//If we pass through a point - we make this point visited in matrix,
	//beacause: if we dont make it visited, we will have an endless loop.
	char visited = 'X';

	//Before we go back trough "recursively return" we have to make a visited point again not visited,
	//because this point may be a part of another path
	char symbolToReset = matrix[start];

	//Push the startPoint in current path
	singlePath.push(start);

	//Make startPoint visited
	matrix[start] = visited;

	if (start == final)
	{
		//We founded a path, so we push that path in allPaths(this is all paths to one point)
		allPaths.push(singlePath);

		//We remove the current(the final) point from the path, and make current point again not visited
		//because there may be another paths to find, which includes this point.
		//It is like we are going one step backward.
		singlePath.pop_back();
		matrix[start] = symbolToReset;

		//We return and the algorithm goes in another direction
		return;
	}
	else
	{
		for (int i = 0; i < movesCount; i++)
		{
			short neighboor = getNeighboor(start, i);
			if (matrix[neighboor] != visited)
			{
				if (isValid(neighboor))
				{
					//We generate all neighbour points, and if a point is valid - maybe there is a chance to find a path with that point
					//We call recursively DFS with this new point
					DFS(neighboor, final, allPaths, singlePath, steps);
				}
			}
		}
		//Here we already cheked for all direction of current point(current point is start point in arguments)
		//So we pop this point from the path and make it again not visited
		singlePath.pop_back();
		matrix[start] = symbolToReset;
	}
}

void Labyrinth::getAllPaths()
{
	//Will save all paths for a current point
	List<List<short>> currPointPaths;

	for (Iterator<short> i = pointsFromBFS.begin(); i; ++i)
	{
		//Will save all points from a current path
		List<short>singlePath;
		int steps = 0;

		//(*i) is a final point for DFS
		DFS(startPoint, *i, currPointPaths, singlePath, steps);

		//Here we founded all paths for a current point
		//and we push these allpaths in the list of paths for all points
		allPointsPats.push(currPointPaths);

		//We clear currentPointPaths,
		//so currPointPaths is empty and ready to work for the next final point
		currPointPaths.~List();
	}

	//After we founded all paths for all points,
	//we sort them by lenght
	sortAllPaths();
}

void Labyrinth::ReadData()
{
	//In the first for loop we pass through the points in pointsFromBFS,
	//and trough elements of allPointsPaths
	Iterator<short> point = pointsFromBFS.begin();
	Iterator<List<List<short>>> pathsForPoint = allPointsPats.begin();
	for (; pathsForPoint; ++pathsForPoint, ++point)
	{
		cout << "Paths to point ";
		writePoint(*point);
		cout << "\n----------------------" << endl;

		//In the second for loop we pass through the paths for a current point
		Iterator<List<short>> path = pathsForPoint->begin();
		for (; path; ++path)
		{
			cout << "	";

			//In the third for loop we pass through the points in one path
			Iterator<short> currPoint = path->begin();
			for (; currPoint; ++currPoint)
			{
				writePoint(*currPoint);
			}
			cout << endl << endl;
		}
	}
}

void Labyrinth::sortAllPaths()
{
	//We pass through elements of allPointsPaths,
	//where one element is List of paths
	//and we call SortListOfList() for that List of paths.
	for (Iterator <List<List<short>>> paths = allPointsPats.begin(); paths; ++paths)
	{
		List<List<short>>::SortListOfLists(*paths);
	}
}