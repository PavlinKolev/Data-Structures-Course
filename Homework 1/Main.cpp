#include "String.h"
#include "Stack.h"
#include "Decoding.h"

int main()
{
	String str = "A";
	Decode(str);
	std::cout << std::endl;

	str = "AB";
	Decode(str);
	std::cout << std::endl;

	str = "3(A)";
	Decode(str);
	std::cout << std::endl;

	str = "3(AB2(B))";
	Decode(str);
	std::cout << std::endl;

	str = "12(ZQ)";
	Decode(str);
	std::cout << std::endl;

	str = "2(2(A)3(B))";
	Decode(str);
	std::cout << std::endl;

	return 0;
}
