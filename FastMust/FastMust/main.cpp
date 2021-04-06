#include "Multiplier.h"
#include <iostream>

int main()
{
	Number num1(read_number());
	Number num2(read_number());
	Number res = Number::karatsuba_mult(num1, num2);
	std::cout << std::endl;
	res.print();

	return 0;
}