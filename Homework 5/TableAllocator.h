#ifndef _TABLE_ALLOCATOR_H
#define _TABLE_ALLOCATOR_H

class TableAllocator
{
public:
	template<class T>
	T** allocate(size_t tableSize) const
	{
		T** ptr = new T*[tableSize];
		for (size_t i = 0; i < tableSize; i++)
		{
			ptr[i] = new T[tableSize];
		}

		return ptr;
	}

	template<class T>
	void free(T** ptr,size_t tableSize) const
	{
		for (size_t i = 0; i < tableSize; i++)
		{
			delete[] ptr[i];
		}

		delete[] ptr;
	}
};


#endif