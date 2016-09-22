#ifndef Labyrinth_H
#define Labyrinth_H
#include "List.h"

//There will be only one instance of Labyrinth
//because Labyrinth is only one for the task.
class Labyrinth
{
private:
	static bool isCreated;

	//Pointers to the single instance of Labyrinth
	static Labyrinth *single;

	//Private constructors
	Labyrinth(){}
	Labyrinth(char* labyrinth, short N, short M, short row, short col);
public:
	//Returns single
	static Labyrinth* getInstance(char*, short, short, short,short);
	~Labyrinth();

private:
	//MaxSize for number of cells in labyrinth
	static short const MaxSize;

	//Maximum steps that DFS makes
	static int const MaxDFSsteps;

	//The labyrinth
	//I use only one-dimensional array, because points(coordinates of a point) are short integers
	char *matrix;

	//N - rows, M collumns
	short N, M;

	//In this class a point(coordinates of a point) is not represented with two integers - X and Y.
	//A point(coordinates of a point) is represented only with one short integer.
	//Excample: 
	//		short point=S;
	//		int rows = S/M; //M - number of columns
	//		int cols = S%M;
	short startPoint;

	List<short> pointsFromBFS;//List of all reachable points that are founded in BFS()

	//All paths for all points
	//This List has elements List<Paths>, for every point
	List<List<List<short>>> allPointsPats;

	//Check if a point is passable
	bool isValid(short);

	//Finds all paths from startPoint to finalPoint
	void DFS(short startPoint, short finalPoint, List<List<short>>& allPaths, List<short>& currentPath,int& stepsForDFS);

	//Generate a neighboor_point to currentPoit according direction
	short getNeighboor(short currentPoint, int direction);

	//Write a point on the console
	void writePoint(short);

	//Sorts the paths for all points
	void sortAllPaths();
public:
	//Finds all reachable points with BFS algorithm, and prints them on the console
	void BFS();

	//Finds all Paths for all reachable points
	void getAllPaths();

	//Writes on console all paths for all reachable points
	void ReadData();

};

#endif