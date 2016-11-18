#include "RLEString.h"


RLEString::RLEString() :len(0){}

RLEString::RLEString(const char* string) : len(0)
{
	setFromString(string);
}

char& RLEString::operator[](int i)
{
	if (i < 0 || i >= len)
	{
		throw "Index out of Range.";
	}
	int tempSize = 0;

	for (Iterator<RLE> j = list.begin(); j; ++j)
	{
		tempSize += j->getLength();
		if (tempSize > i)
		{
			return j->getSymbol();
		}
	}
}

RLEString& RLEString::operator+=(const RLEString& right)
{
	if (checkLastFirst(right))
	{
		setNewSizeOfLastElem(right);
		list.append(right.list, 1);
	}
	else
	{
		list += right.list;
	}
	len += right.len;

	return *this;
}

RLEString RLEString::operator+(const RLEString& right)const
{
	RLEString temp(*this);
	temp += right;

	return temp;
}

void RLEString::splice(int start, int length)
{
	size_t tempCount = 0;
	size_t pos = 0;

	for (Iterator<RLE> i = list.begin(); i; ++i, ++pos)
	{
		tempCount += i->getLength();
		if (tempCount > start)
		{
			spliceBegin(i, start, length, tempCount, pos);

			break;
		}
	}
}

void RLEString::insert(const RLEString& rles, int pos)
{
	if (pos > len)
	{
		throw "Index out of range.";
	}
	if (pos == 0)
	{
		*this = rles + *this;
		return;
	}
	if (pos == len)
	{
		*this += rles;
		return;
	}
	RLEString right = cutAt(pos);
	*this += rles;
	*this += right;

}

void RLEString::setFromString(const char* string)
{
	if (!RLEString::checkString(string))
	{
		throw "Not correct string.";
	}

	list.free();
	len = 0;

	char symbol = *string;
	unsigned char symbolLen = 1;
	string++;
	len++;

	while (*string)
	{
		if (symbol != *string)
		{
			list.addBack({ symbol, symbolLen });

			symbol = *string;
			symbolLen = 0;
		}
		string++;
		symbolLen++;
		len++;
	}

	list.addBack({ symbol, symbolLen });
}

RLEString RLEString::cutAt(int pos)
{
	RLEString right;
	int tempCount = 0;
	size_t index = 0;
	for (Iterator<RLE> i = list.begin(); i; ++i, ++index)
	{
		tempCount += i->getLength();
		if (tempCount > pos)
		{
			char symbol = i->getSymbol();
			size_t newLength = i->getLength() - (tempCount - pos);
			if (newLength)
			{
				i->setLength(newLength);
				++index;
				++i;
			}
			else
			{
				++i;
				list.removeAt(index);
			}

			newLength = tempCount - pos;
			right.list.addBack({ symbol, (unsigned char)newLength });

			while (i)
			{
				right.list.addBack({ i->getSymbol(), unsigned char(i->getLength()) });
				++i;
				list.removeAt(index);
			}
			break;
		}
	}
	right.len = len - pos;
	len = pos;

	return right;
}

void RLEString::setNewSizeOfLastElem(const RLEString& rhs)
{
	RLE* last = list.back();
	size_t newSizeOfLastElem = last->getLength();
	newSizeOfLastElem += rhs.list.front()->getLength();

	last->setLength(newSizeOfLastElem);
}

bool RLEString::checkLastFirst(const RLEString& rhs)
{
	char lastSymbol = list.back()->getSymbol();
	char firstSymbol = rhs.list.front()->getSymbol();

	if (lastSymbol == firstSymbol)
	{
		return true;
	}

	return false;
}

void RLEString::eraseElements(Iterator<RLE> it, size_t pos, int length)
{
	Iterator<RLE> i = it;
	while (i)
	{
		if (length > i->getLength())
		{
			length -= i->getLength();
			++i;
			list.removeAt(pos);
		}
		else
		{
			int newLen = i->getLength() - length;
			if (newLen <= 0)
			{
				list.removeAt(pos);
			}
			else
			{
				i->setLength(i->getLength() - length);
			}
			break;
		}
	}
}

void RLEString::spliceBegin(Iterator<RLE> i, int start, int length, int tempCount, size_t pos)
{
	int countToRemove = tempCount - start;
	if (countToRemove > length)
	{
		countToRemove = length;
	}
	int newLength = i->getLength() - countToRemove;
	if (newLength <= 0)
	{
		++i;
		list.removeAt(pos);
	}
	else
	{
		i->setLength(newLength);
		++i;
		++pos;
	}
	length -= countToRemove;
	if (length > 0)
	{
		eraseElements(i, pos, length);
	}
}


bool RLEString::checkString(const char* str)
{
	if (str == NULL)
	{
		return false;
	}
	while (*str)
	{
		if ((*str)<'A' || (*str)>'Z')
		{
			return false;
		}
		str++;
	}
	return true;
}

ostream& operator<<(ostream& os, const RLEString& rle)
{
	for (Iterator<RLE> i = rle.list.begin(); i; ++i)
	{
		os << *i << " ";
	}

	return os;
}