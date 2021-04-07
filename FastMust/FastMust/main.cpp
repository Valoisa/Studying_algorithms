#include "Number.h"
#include <iostream>

int main()
{
	Number num1(read_number());
	Number num2(read_number());
	Number res = Number::karatsuba_mult(num1, num2);
	res.print();

	return 0;
}