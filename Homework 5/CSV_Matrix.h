#ifndef _MATRIX_H
#define _MATRIX_H
#include <fstream>
#include <iostream>
#include "DynArray.h"
#include "String.h"
#include "TableAllocator.h"

class CSV_Matrix
{
public:
	CSV_Matrix(const char* fileName);

	void peopleToPeople()const;
	void GroupToGroup()const;
	void Closeness()const;
private:
	unsigned short** createPeopleToPeopleMatrix() const;
	unsigned short** createGroupToGroupMatrix()const;

	//Calculates the distances between all possible pairs of people with Floyd-Warshall algorithm
	unsigned short** createDistancesMatrix()const;

	void  Floyd_Warshall_Algorithm(unsigned short** distances, size_t size)const;
	//Prints the first three people with largest value of closeness-centrality
	void printCloseness(unsigned short** distances)const;
	//This function is used in printCloseness - sets the three people(their indexes) which are with largest value for closeness-centrality
	//in temporary moment
	void setTempCloseness(size_t temp, float closeTemp, size_t& first, float& closeFirst, size_t& second, float& closeSecond, 
		size_t& third, float& closeThird)const;

	//Finds which lines from matrix have biggest sum of their elements
	void getMostConnected(unsigned short** matrix, size_t tableSize, const DynArray<String>& arr)const;
	void printMostConnected(size_t* indexs, size_t count, unsigned short biggestCount, const DynArray<String>& arr)const;

	//Reads the first line from CSV-file - sets the names of organisations
	void readFirstLine(std::ifstream& file);
	//Reads single line from CSV-file - the name of a person and his memberships
	void readSingleLine(char* buffer, size_t maxSize, size_t line);

	unsigned short colsMultiplication(size_t col_1, size_t col_2)const;
	unsigned short rowsMultiplication(size_t row_1, size_t row_2)const;

	void createCSV_File(const char* fileName,const DynArray<String>& firstRow,const DynArray<String>& firstCol, unsigned short** table)const;
private:
	DynArray<String> organisations;
	DynArray<String> people;
	DynArray<DynArray<unsigned short>> table;
	size_t rows, cols;
private:
	//It is used for allocating and freeing memory for dynamically allocated square matrices
	TableAllocator allocator;
};

void checkFile(std::ifstream& file);
void moveAfterAtoi(char*& str, int number);
//Copies source in dest till findind delim and move the pointer source
void m_strtok(char* dest, char*& source, char delim = '\0');
 
#endif
