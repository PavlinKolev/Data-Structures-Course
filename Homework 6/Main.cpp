#include <iostream>
#include "RLE.h"
#include "List.h"
#include "RLEString.h"

using std::cout;
using std::endl;

int main()
{
	cout << "------- Test 1 -------\n";
	RLEString rle1("AAABBCBBC");
	cout << rle1 << endl;

	rle1.splice(2, 5);
	cout << rle1 << endl;

	cout << "\n\n------- Test 2 -------\n";
	RLEString rle2("AB");
	RLEString rle3("AABCC");
	rle3.insert(rle2, 2);
	
	cout << rle3 << endl<<endl;

	return 0;
}