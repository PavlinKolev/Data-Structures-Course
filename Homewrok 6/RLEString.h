#ifndef _RLESTRING_H
#define _RLESTRING_H
#include "List.h"
#include "RLE.h"

class RLEString
{
	friend ostream& operator<<(ostream& os, const RLEString& rle);
public:
	RLEString();
	RLEString(const char* string);
	
public:
	size_t length()const{ return len; }
	char& operator[](int i);
	RLEString& operator+=(const RLEString& right);
	RLEString operator+(const RLEString& right)const;
	void splice(int start, int length);
	void insert(const RLEString& rles, int pos);

	void setFromString(const char* str);
private:
	static bool checkString(const char*);
private:
	//Separates the objects in two parts through position "pos".
	//The left part is saved in *this and the right is the return value
	RLEString cutAt(int pos);

	//It is called in operator+=. If the last element of *this contains the same symbol
	//as the first element of "rhs". The point is to get one element with length = the sum of lenghts of the two elements
	void setNewSizeOfLastElem(const RLEString& rhs);

	//Check if the last element of *this and the first element of "rhs" have same symbol
	bool checkLastFirst(const RLEString& rhs);

	//Erase "length" symbols from the decompress string, starting from the first symbol of the box
	//on position "pos" in "list". "it" points at the same box.
	void eraseElements(Iterator<RLE> it, size_t pos,int length);

	//"pos" is the index of the box in "list", where is the starting element from which
	//starts the erasing of "lenght" symbols from the decompress string. "it" points at the same box
	//"tempCount" is the sum of the "lenghts" of the first "pos" boxes.
	void spliceBegin(Iterator<RLE> it,int start, int length, int tempCount, size_t pos);
private:

	//List from double boxes. One box contains a symbol and count of repeats of that symbol(lenght)
	List<RLE> list;

	//The size of the decompress string
	size_t len;
};

#endif
