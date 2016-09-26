#include "String.h"

String::String() :str(NULL)
{}

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

bool String::checkPefix(const String& pref)const
{
	if (pref.getSize() > this->getSize())
	{
		return false;
	}

	for (size_t i = 0; i < pref.getSize(); i++)
	{
		if (pref.str[i] != str[i])
		{
			return false;
		}
	}

	return true;
}

bool String::operator<(const String& right)const
{
	for (size_t i = 0; i<this->getSize(); i++)
	{
		if (i >= right.getSize())
		{
			return false;
		}
		if (str[i] < right.str[i])
		{
			return true;
		}
		else if (str[i]>right.str[i])
		{
			return false;
		}
	}

	return true;
}

bool String::operator==(const String& right)const
{
	if (right.getSize() != this->getSize())
	{
		return false;
	}
	for (size_t i = 0; i < this->getSize(); i++)
	{
		if (str[i] != right.str[i])
		{
			return false;
		}
	}

	return true;
}

ostream& operator<<(ostream& stream, const String& str)
{
	stream << str.getStr();

	return stream;
}