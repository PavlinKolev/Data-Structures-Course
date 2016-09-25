#include "RLE.h"

void RLE::setLength(size_t len)
{
	if (len > RLE::MAX_SIZE)
	{
		throw "Too big length for RLE.";
	}
	this->length = (unsigned char)len;
}
ostream& operator<<(ostream& stream, const RLE& rle)
{

	stream << "(" << rle.getLength() << "," << rle.getSymbol() << ")";

	return stream;
}