#include "MemoryAllocator.h"


MemoryAllocator::MemoryAllocator(int64_t size) :startPtr(NULL), endPtr(NULL)
{
	try
	{
		allocateFromHeap(size);
	}
	catch (const char* m)
	{
		std::cerr << m << std::endl;
		throw;
	}

	int64_t blocks = getBlocksCount(size);
	for (size_t i = 0; i < blocks; i++)
	{
		startPtr[i] = 0;
	}

	endPtr = startPtr + blocks - 1;

	//In the beginnig of the program there is only one, free block which occupies the all allocated memory.
	(*startPtr) = size - getBytesCount(2);//getBytesCount(2)=2*8=16 - the total size of both cells(header and footer).
	(*endPtr) = size - getBytesCount(2);
}

MemoryAllocator::~MemoryAllocator()
{
	delete[] startPtr;
}

void* MemoryAllocator::MyMalloc(int64_t sizeInBytes)
{
	if (sizeInBytes == 0)
	{
		return NULL;
	}
	sizeInBytes = getRound(sizeInBytes);

	return bestFit(sizeInBytes);
}

void MemoryAllocator::MyFree(void* p)
{
	if (!p)
		return;
	int64_t* ptr = (int64_t*)p;
	ptr--;//Goes to the cell where is saved the info about the allocated block.

	if (!isValidAllocatedPointer(ptr))
	{
		std::cerr << "The Pointer you want to free is not valid.\n";
		return;
	}

	freeBlock(ptr);
	mergeFreeBlocks(ptr);//If in left and/or in right from the new freed block there are another free blocks, they are merged.
}

void MemoryAllocator::allocateFromHeap(int64_t& size)
{
	if (size < MIN_SIZE_IN_BYTES)
		size = MIN_SIZE_IN_BYTES;
	else
		size = getRound(size);

	try
	{
		startPtr = new int64_t[getBlocksCount(size)];
	}
	catch (std::bad_alloc&)
	{
		size /= 2;
		startPtr = new int64_t[getBlocksCount(size)];
		if (!startPtr)
		{
			throw "Cannot Allocate memory from heap.\n";
		}
	}
}

int64_t* MemoryAllocator::firstFit(int64_t sizeInBytes)
{
	int64_t* ptr = startPtr;

	while ((ptr < endPtr) && (isAllocated(ptr) || (sizeInBytes >(*ptr - getBytesCount(2)))))
	{
		//getBlockCount(*ptr)=count of the cells which are in the temp block
		ptr += getBlocksCount(*ptr) + 2;//+2= one cell for the footer of temp block and one for the header of left block.
	}

	if (isAllocated(ptr))
	{
		return NULL;
	}
	return ptr;
}

int64_t* MemoryAllocator::bestFit(int64_t sizeInBytes)
{
	int64_t* ptr = firstFit(sizeInBytes);
	if (!ptr)
	{
		std::cerr << "There is no enough memory.\n";
		return NULL;
	}
	if (sizeInBytes == *ptr)
	{
		allocateBlock(ptr, sizeInBytes);
		return ptr + 1;
	}
	int64_t* best = ptr;

	ptr += getBlocksCount(*ptr) + 2;

	while (ptr < endPtr)
	{
		if (!isAllocated(ptr))
		{
			if (sizeInBytes == *ptr)
			{
				allocateBlock(ptr, sizeInBytes);
				return ptr + 1;
			}
			if (sizeInBytes < *ptr)
			{
				if (*ptr < *best)
				{
					best = ptr;
				}
			}
		}
		ptr += getBlocksCount(*ptr) + 2;
	}
	int64_t oldSizeInBytes = *best;
	allocateBlock(best, sizeInBytes);
	fixRightFreeBlock(best, oldSizeInBytes);

	return best + 1;
}

void MemoryAllocator::allocateBlock(int64_t* ptr, int64_t sizeInBytes)
{
	*ptr = sizeInBytes + 1;//... +1 - lowest bit is set to 1
	ptr += getBlocksCount(sizeInBytes) + 1;//goes to the footer
	*ptr = sizeInBytes + 1;
}

void MemoryAllocator::fixRightFreeBlock(int64_t* ptr, int64_t oldSizeInBytes)
{
	int64_t newSize = oldSizeInBytes - (*ptr - 1) - getBytesCount(2);

	ptr += getBlocksCount(*ptr) + 2;//Goes to the new header of the right block
	*ptr = newSize;
	ptr += getBlocksCount(newSize) + 1;
	*ptr = newSize;
}

void MemoryAllocator::freeBlock(int64_t* ptr)
{
	(*ptr)--;//Lowes bit is set to 0
	ptr += getBlocksCount(*ptr) + 1;
	(*ptr)--;
}

void MemoryAllocator::mergeFreeBlocks(int64_t* ptr)
{
	if (ptr > startPtr)
	{
		mergeLeft(ptr);
	}
	ptr += getBlocksCount(*ptr) + 1;
	if (ptr < endPtr)
	{
		mergeRight(ptr);
	}
}

void MemoryAllocator::mergeLeft(int64_t* right)
{
	int64_t* left = right - 1;//Goes to the footer of the left block
	if (!isAllocated(left))
	{
		left -= getBlocksCount(*left) + 1;//Goes to the header of the left block
		*left += *right + getBytesCount(2);//The size is increased with (the size of the right block + the size of the two cells which are freed).
		//These two cells are the footer of the left block and the header of the right block

		right += getBlocksCount(*right) + 1;//Goes to the footer of the right block
		*right = *left;
	}
}

void MemoryAllocator::mergeRight(int64_t* left)
{
	int64_t* right = left + 1;
	if (!isAllocated(right))
	{
		left -= getBlocksCount(*left) + 1;
		*left += *right + getBytesCount(2);

		right += getBlocksCount(*right) + 1;
		*right = *left;
	}
}
