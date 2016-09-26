#include "MemoryAllocator.h"
#include "MemoryAllocatorTests.h"
#include <iostream>
using std::cout;

int main()
{
	cout << "Test 1...\n";
	Test_Create_CharArray();

	cout << "Test 2...\n";
	Test_Create_IntArray();

	cout << "Test 3...\n";
	Test_Create_DoubleArray();

	cout << "Test 4...\n";
	Test_Not_Enough_Allocated_Memory();

	return 0;
}