#ifndef _STRING_H
#define _STRING_H
#include <fstream>
#include <iostream>

class String
{
public:
	String();
	String(const char* str);
	String(const String& rhs);
	String& operator=(const String& rhs);
	~String();
public:
	const char* getString()const{ return  str; }
	void setString(const char* str);
private:
	char* str;
};

std::ostream& operator<<(std::ostream& stream, const String& string);

#endif
