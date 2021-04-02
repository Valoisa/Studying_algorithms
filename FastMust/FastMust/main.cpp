#include "Multiplier.h"
#include <iostream>

int main()
{
	number num1 = read_number();
	number num2 = read_number();
	number res = long_mult(num1, num2);
	for (const auto x : res)
		std::cout << x;
	std::cout << std::endl;
	number res2 = long_add(num1, num2);
	for (const auto x : res2)
		std::cout << x;

	return 0;
}