#ifndef _STRING_H
#define _STRING_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using std::ostream;

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

	bool checkPefix(const String& pref)const;

	bool operator<(const String& right)const;
	bool operator>(const String& right)const{ return (right < *this); }
	bool operator<=(const String& right)const{ return !(*this > right); }
	bool operator>=(const String& right)const{ return !(*this < right); }

	bool operator==(const String& right)const;
	bool operator!=(const String& right)const{ return !(*this == right); }
private:
	char* str;

};

ostream& operator<<(ostream& stream, const String& str);

#endif