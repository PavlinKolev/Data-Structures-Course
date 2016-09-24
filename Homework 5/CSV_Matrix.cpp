#define _CRT_SECURE_NO_WARNINGS
#include "CSV_Matrix.h"
#include <iomanip>
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;

CSV_Matrix::CSV_Matrix(const char* fileName)
{
	std::ifstream file(fileName, std::ios::in);
	if (!file)
	{
		throw "File does not exist.";
	}

	file.seekg(1, std::ios::beg);//reads the first "empty" word 
	checkFile(file);

	readFirstLine(file);

	char buffer[256];
	for (size_t i = 0; !file.eof(); i++)
	{
		file.getline(buffer, 256);

		if (!file.eof())
			checkFile(file);

		readSingleLine(buffer, 256, i);
	}

	rows = people.getSize();//The lines of table are as much as the people
}


void CSV_Matrix::peopleToPeople()const
{
	unsigned short** matrix = createPeopleToPeopleMatrix();

	getMostConnected(matrix, rows, people);//Finds and prints the person(people) with most connections with other people
	createCSV_File("People to people.csv", people, people, matrix);

	allocator.free<unsigned short>(matrix, rows);
}

void CSV_Matrix::GroupToGroup()const
{
	unsigned short** matrix = createGroupToGroupMatrix();

	getMostConnected(matrix, cols, organisations);//Finds and prints the organisation with most connections with other organisations

	createCSV_File("Group to group.csv", organisations, organisations, matrix);

	allocator.free<unsigned short>(matrix, cols);
}

void CSV_Matrix::Closeness()const
{
	unsigned short** distances = createDistancesMatrix();

	printCloseness(distances);

	createCSV_File("Distances.csv", people, people, distances);

	allocator.free<unsigned short>(distances, rows);
}


unsigned short** CSV_Matrix::createPeopleToPeopleMatrix()const
{
	unsigned short** matrix = allocator.allocate<unsigned short>(rows);

	unsigned short value = 0;

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < rows; j++)
		{
			matrix[i][j] = rowsMultiplication(i, j);
		}
	}

	return matrix;
}

unsigned short** CSV_Matrix::createGroupToGroupMatrix()const
{
	unsigned short** matrix = allocator.allocate<unsigned short>(cols);

	for (size_t i = 0; i < cols; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			matrix[i][j] = colsMultiplication(i, j);
		}
	}

	return matrix;
}

unsigned short** CSV_Matrix::createDistancesMatrix()const
{
	unsigned short** distances = allocator.allocate<unsigned short>(rows);

	Floyd_Warshall_Algorithm(distances, rows);

	return distances;
}


void CSV_Matrix::Floyd_Warshall_Algorithm(unsigned short** distances, size_t size)const
{
	unsigned short** peopleToPeople = createPeopleToPeopleMatrix();

	for (size_t i = 0; i < size; i++)
	{
		distances[i][i] = 0;
	}

	const unsigned short MAX_DISTANCE = 2000;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (i != j)
			{
				if (peopleToPeople[i][j])
				{
					distances[i][j] = 1;
				}
				else
				{
					distances[i][j] = MAX_DISTANCE;
				}
			}
		}
	}

	for (size_t k = 0; k < size; k++)
	{
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				if (distances[i][j]>distances[i][k] + distances[k][j])
				{
					distances[i][j] = distances[i][k] + distances[k][j];
				}
			}
		}
	}

	allocator.free<unsigned short>(peopleToPeople, rows);
}

void CSV_Matrix::printCloseness(unsigned short** distances)const
{
	size_t first = 0, second = 0, third = 0;//The indexes of the three people with largesr value of closeness centrality in "people"
	float closeFirst = -1, closeSecond = -1, closeThird = -1;//The closeness-centrality values of the first three people

	for (size_t i = 0; i < rows; i++)
	{
		float distSum = 0;//The sum of the distances from person "i" to all others people 
		for (size_t j = 0; j < rows; j++)
		{
			distSum += (float)distances[i][j];
		}

		setTempCloseness(i, 1.0 / distSum, first, closeFirst, second, closeSecond, third, closeThird);
	}

	cout << "Closeness Centrality:\n";
	if (closeFirst>0.0)
	{
		cout << " First: " << std::setw(16) << people[first] << " - " << closeFirst << endl;
	}
	if (closeSecond > 0.0)
	{
		cout << "Second: " << std::setw(16) << people[second] << " - " << closeSecond << endl;
	}
	if (closeThird > 0.0)
	{
		cout << " Third: " << std::setw(16) << people[third] << " - " << closeThird << endl;
	}
}

void CSV_Matrix::setTempCloseness(size_t temp, float closeTemp, size_t& first, float& closeFirst, size_t& second, float& closeSecond,
	size_t& third, float& closeThird)const
{
	if (closeFirst < closeTemp)
	{
		closeThird = closeSecond;
		third = second;

		closeSecond = closeFirst;
		second = first;

		closeFirst = closeTemp;
		first = temp;
	}
	else if (closeSecond < closeTemp)
	{
		closeThird = closeSecond;
		third = second;

		closeSecond = closeTemp;
		second = temp;
	}
	else if (closeThird < closeTemp)
	{
		closeThird = closeTemp;
		third = temp;
	}
}


void CSV_Matrix::getMostConnected(unsigned short** matrix, size_t tableSize, const DynArray<String>& arr)const
{
	size_t equalConnections[64];//Will save the indexes of the elements(people or organisations) which have most connections with other elements(people or organisations)
	//the indexes are for "arr"
	size_t equalsCount = 0;//The count of elements with most connections

	unsigned short connectionsOfMostConnected = 0;
	unsigned short tempConnections = 0;

	for (size_t i = 0; i < tableSize; i++)
	{
		tempConnections = 0;
		for (size_t j = 0; j < tableSize; j++)//Finds the connections of element "i" with the others elements
		{
			if (i != j)
				tempConnections += matrix[i][j];
		}

		if (tempConnections == connectionsOfMostConnected)
		{
			equalConnections[equalsCount++] = i;
		}
		if (tempConnections>connectionsOfMostConnected)
		{
			connectionsOfMostConnected = tempConnections;
			equalsCount = 0;
			equalConnections[equalsCount++] = i;
		}
	}

	printMostConnected(equalConnections, equalsCount, connectionsOfMostConnected, arr);
}

void CSV_Matrix::printMostConnected(size_t* indexs, size_t count, unsigned short biggestCount, const DynArray<String>& arr)const
{
	char word[64];

	if (count == 1)
	{
		if ((&arr) == (&people))
		{
			strcpy(word, "person");
		}
		else
		{
			strcpy(word, "organisation");
		}
		std::cout << "The " << word << " with most connection is: " << arr[*indexs]
			<< "\nConnections: " << biggestCount << std::endl;
	}
	else
	{
		if ((&arr) == (&people))
		{
			strcpy(word, "people");
		}
		else
		{
			strcpy(word, "organisations");
		}
		std::cout << "The most connected " << word << " are: \n";
		for (size_t i = 0; i < count; i++)
		{
			std::cout << "	" << arr[indexs[i]] << std::endl;
		}
		std::cout << "\nConnections: " << biggestCount << std::endl;
	}
}


void CSV_Matrix::readFirstLine(std::ifstream& file)
{
	char line[1024];
	file.getline(line, 1024);
	checkFile(file);
	char* buffer = line;

	char organisationName[128];
	m_strtok(organisationName, buffer, ',');

	while (*organisationName)
	{
		organisations.pushBack(organisationName);
		m_strtok(organisationName, buffer, ',');
	}

	cols = organisations.getSize();//The columns of "table" are as such as the organisations
}

void CSV_Matrix::readSingleLine(char* buffer, size_t maxSize, size_t line)
{
	char personName[64];
	m_strtok(personName, buffer, ',');

	people.pushBack(personName);
	table.incrementSize();

	for (size_t i = 0; i < cols; i++)
	{
		unsigned short number = atoi(buffer);
		moveAfterAtoi(buffer, number);

		table[line].pushBack(number);
	}
}


unsigned short CSV_Matrix::colsMultiplication(size_t col_1, size_t col_2)const
{
	unsigned short val = 0;
	for (size_t i = 0; i < rows; i++)
	{
		val += (table[i][col_1] * table[i][col_2]);
	}

	return val;
}

unsigned short CSV_Matrix::rowsMultiplication(size_t row_1, size_t row_2)const
{
	unsigned short val = 0;
	for (size_t i = 0; i < cols; i++)
	{
		val += (table[row_1][i] * table[row_2][i]);
	}

	return val;
}


void CSV_Matrix::createCSV_File(const char* fileName, const DynArray<String>& firstRow, const DynArray<String>& firstCol, unsigned short** table)const
{
	std::ofstream file(fileName, std::ios::out);
	if (!file)
	{
		return;
	}
	size_t rowsCount = firstCol.getSize();
	size_t colsCount = firstRow.getSize();

	file << ',';
	for (size_t i = 0; i < colsCount; i++)
	{
		file << firstRow[i];

		if (i < rowsCount - 1)
			file << ',';
		else
			file << '\n';

	}
	for (size_t i = 0; i < rowsCount; i++)
	{
		file << firstCol[i] << ',';
		for (size_t j = 0; j < colsCount; j++)
		{
			file << table[i][j];

			if (j < colsCount - 1)
				file << ',';
			else
				file << '\n';
		}
	}

}


void checkFile(std::ifstream& file)
{
	if (file.eof())
	{
		file.clear();
		file.close();
		throw "End of file.";
	}
	else if (file.bad())
	{
		file.clear();
		file.close();
		throw "Error in file";
	}
	else if (file.fail())
	{
		file.clear();
		file.close();
		throw "Bad information in file.";
	}
}

void moveAfterAtoi(char*& str, int number)
{
	if (number < 10)
	{
		str += 2;//Skips the number and the comma
	}
	else
	{
		while (number)
		{
			number /= 10;
			str++;
		}
		str++;//Skips the comma
	}
}

void m_strtok(char* dest, char*& source, char delim)
{
	size_t index = 0;
	while (*source && *source != delim)
	{
		dest[index++] = *source++;
	}

	if (*source)
		source++;//Moves to the symbol after "delim"

	dest[index] = '\0';
}