#ifndef _MEMORY_ALLOCATOR_H
#define _MEMORY_ALLOCATOR_H
#include <stdint.h>
#include <iostream>

/*
A block from heap(big enough), aligned on 8 bytes, is allocated.
After a several cals of "MyMalloc" and/or "MyFree" this block
will be represented as a sequence of "allocated" and "free" smaller blocks.
Every block has two cells in both ends - header and footer.
They save the size(in bytes) of the rest part of the block(the part which the customer knows).
If a block is "allocated" it's header and footer's lowest bit is set to 1 - when freeing, the bit is set to 0.
*/
class MemoryAllocator
{
public:
	MemoryAllocator(int64_t sizeInBytes);
	~MemoryAllocator();

	void* MyMalloc(int64_t sizeInBytes);
	void MyFree(void* ptr);
private:
	void allocateFromHeap(int64_t& size);

	int64_t getBlocksCount(int64_t sizeInBytes)const{ return sizeInBytes >> 3; }
	int64_t getBytesCount(int64_t blocksCount)const{ return blocksCount << 3; }

	int64_t getRound(int64_t size)const{return (size % 8) ? (size + (8 - (size % 8))) : size;}
	bool isAllocated(int64_t* ptr)const{return *ptr & 1;}
	bool isValidAllocatedPointer(int64_t* ptr)const{ return (ptr>=startPtr && ptr<endPtr) && isAllocated(ptr); }

	int64_t* firstFit(int64_t sizeInBytes);
	int64_t* bestFit(int64_t sizeInBytes);

	void allocateBlock(int64_t* ptr, int64_t sizeInBytes);
	void fixRightFreeBlock(int64_t* ptr, int64_t oldSizeInBytes);

	void freeBlock(int64_t* ptr);
	void mergeFreeBlocks(int64_t*ptr);
	void mergeLeft(int64_t* right);
	void mergeRight(int64_t* left);

private:
	static const int64_t MIN_SIZE_IN_BYTES = 1 << 10;

	int64_t* startPtr;
	int64_t* endPtr;

private:
	MemoryAllocator(const MemoryAllocator&);
	MemoryAllocator& operator=(const MemoryAllocator&);
};

#endif
