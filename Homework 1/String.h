#ifndef _STRING_H
#define _STRING_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class String
{
public:
	String();
	String(const String& rhs);
	String(const char* str);
	String& operator=(const String& rhs);
	~String();
public:
	size_t getSize()const{ return (str) ? strlen(str) : 0; }

	void setStr(const char* str);
	const char* getStr()const{ return str; }

	char& operator[](size_t index);
	char operator[](size_t index)const;

	bool isDigit(size_t index)const;
	size_t getNumber(size_t& index)const;
private:
	char* str;
};

size_t digitsCount(size_t number);

#endif
