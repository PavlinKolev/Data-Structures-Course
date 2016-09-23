#include "String.h"

String::String() :str(NULL){}

String::String(const String& rhs) : str(NULL)
{
	setStr(rhs.str);
}

String::String(const char* str) : str(NULL)
{
	setStr(str);
}

String& String::operator=(const String& rhs)
{
	if (this != &rhs)
	{
		setStr(rhs.str);
	}
	return *this;
}

String::~String()
{
	delete[] str;
}

void String::setStr(const char* str)
{
	if (str == NULL)
	{
		throw "String cannot be NULL.";
	}
	delete[] this->str;
	this->str = new char[strlen(str) + 1];
	strcpy(this->str, str);
}

char& String::operator[](size_t index)
{
	if (index >= getSize())
	{
		throw "Index out of range.";
	}

	return str[index];
}

char String::operator[](size_t index)const
{

	if (index >= getSize())
	{
		throw "Index out of range.";
	}

	return str[index];
}

bool String::isDigit(size_t index)const
{
	if (index >= getSize())
	{
		throw "Index out of range.";
	}

	if (str[index] >= '0' && str[index] <= '9')
	{
		return true;
	}
	return false;
}

size_t String::getNumber(size_t& index)const
{
	if (!isDigit(index))
	{
		throw "No number to extract from string.";
	}

	size_t number = atoi(str + index);

	index += digitsCount(number)- 1;

	return number;
}

size_t digitsCount(size_t number)
{
	size_t digits = 0;
	while (number)
	{
		number /= 10;
		digits++;
	}

	return digits;
}
