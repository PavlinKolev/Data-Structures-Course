#ifndef _DECODING_H
#define _DECODING_H
#include "String.h"
#include "Stack.h"

struct Box
{
	size_t repeats;
	size_t startIndex;
};

void Decode(const String& string);

#endif
