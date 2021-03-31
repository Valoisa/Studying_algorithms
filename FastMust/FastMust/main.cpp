#include "Multiplier.h"
#include <iostream>

int main()
{
	std::vector<size_t> num = read_number();
	for (size_t i = 0; i < num.size(); ++i)
		std::cout << num[i];
	return 0;
}