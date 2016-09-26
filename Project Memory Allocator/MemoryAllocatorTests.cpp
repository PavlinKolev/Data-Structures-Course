#include "MemoryAllocatorTests.h"

void Test_Create_IntArray()
{
	cout << "	Create int array..." << endl;

	MemoryAllocator m((1 << 20) * 10);
	int* ptr = (int*)m.MyMalloc(150 * sizeof(int));

	if (ptr)
	{
		cout << "	Allocation of int - OK.\n";
		m.MyFree(ptr);
		cout << "	Free int - OK\n";
	}
	else
		cout << "	Allocation of int  - failed.\n";

}

void Test_Create_CharArray()
{
	cout << "	Create char array..." << endl;

	MemoryAllocator m((1 << 20) * 10);
	char* ptr = (char*)m.MyMalloc(150 * sizeof(char));

	if (ptr)
	{
		cout << "	Allocation of char - OK.\n";
		m.MyFree(ptr);
		cout << "	Free char - OK.\n";
	}
	else
		cout << "	Allocation of char  - failed.\n";

}

void Test_Create_DoubleArray()
{
	cout << "	Create double array..." << endl;

	MemoryAllocator m((1 << 20) * 10);
	double* ptr = (double*)m.MyMalloc(150 * sizeof(double));

	if (ptr)
	{
		cout << "	Allocation of double - OK.\n";
		m.MyFree(ptr);
		cout << "	Free doublev - OK.\n";
	}
	else
		cout << "	Allocation of double  - failed.\n";

}

void Test_Not_Enough_Allocated_Memory()
{
	MemoryAllocator m(1 << 20);
	char*ptr = (char*)m.MyMalloc(1 << 20);

	if (!ptr)
		cout << "	Test \"Not enough memory\" - OK.\n";
	else
		cout << "	Test \"Not enough memory\" - Failed\n";
}

