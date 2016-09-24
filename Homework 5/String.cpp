#define _CRT_SECURE_NO_WARNINGS
#include "String.h"

String::String() :str(NULL){}

String::String(const char* str) :str(NULL)
{
	setString(str);
}

String::String(const String& rhs) : str(NULL)
{
	setString(rhs.str);
}

String& String::operator=(const String& rhs)
{
	if (this != &rhs)
	{
		setString(rhs.str);
	}
	return *this;
}

String::~String()
{
	delete[] str;
}

void String::setString(const char* str)
{
	if (str == NULL)
	{
		throw "String cannot be NULL.";
	}

	size_t size = strlen(str) + 1;
	delete[] this->str;
	this->str = new char[size];
	strcpy(this->str, str);
}

std::ostream& operator<<(std::ostream& stream, const String& string)
{
	stream << string.getString();
	return stream;
}