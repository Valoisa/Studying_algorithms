#include "Multiplier.h"
#include <iostream>

int main()
{
	Number num1(read_number());
	Number num2(read_number());
	Number res = num1 + num2;
	res.print();

	return 0;
}