#ifndef _RLE_H
#define _RLE_H
#include <fstream>
using std::ostream;

class RLE
{
public:
	RLE(char symbol, unsigned char length) :symbol(symbol), length(length){}
	
	char getSymbol()const{ return symbol; }
	char& getSymbol(){ return symbol; }

	size_t getLength()const{ return (size_t)length; }
	void setLength(size_t);
private:
	static const size_t MAX_SIZE = 255;
private:
	char symbol;
	unsigned char length;
};

ostream& operator<<(ostream& stream, const RLE& rle);

#endif
