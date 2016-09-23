#include "Decoding.h"

/*
This code is from SDP-Practicum from 03.11.2015
*/

void Decode(const String& string)
{
	Stack<Box> stack;

	for (size_t i = 0; i < string.getSize(); i++)
	{
		if (string.isDigit(i))
		{
			size_t repeats = string.getNumber(i);

			Box box = { repeats, i + 1 };//i+1 because of skipping the '(' symbol

			stack.push(box);
		}
		else if (string[i] == ')')
		{
			Box &box = stack.top();
			box.repeats--;
			if (box.repeats == 0)
			{
				stack.pop();
			}
			else
			{
				i = box.startIndex - 1;//turn back to the beginnig of last printed substring
			}
		}
		else if (string[i] != '(')
		{
			std::cout << string[i];
		}
	}
}
