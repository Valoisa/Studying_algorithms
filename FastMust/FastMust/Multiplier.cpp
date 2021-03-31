//	Local includes
#include "Multiplier.h"

//	Standard includes
#include <iostream>
#include <string>
#include <set>
#include <exception>

//	Global functions implementation
std::vector<size_t> read_number(void)
{
	static const std::set<char> digits({ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' });
	std::vector<size_t> result;
	while (result.empty())
	{
		try
		{
			std::cout << "Enter the number:" << std::endl;
			const std::string string_num = [&]()
			{
				std::string temp;
				std::cin >> temp;
				return temp;
			}();

			result.reserve(string_num.size());
			for (size_t i = 0; i < string_num.size(); ++i)
			{
				if (digits.find(string_num[i]) == digits.end())
				{
					result.clear();
					throw std::exception("wrong_char");
				}
				result.push_back((size_t)(string_num[i] - '0'));
			}
		}
		catch (const std::exception& e)
		{
			if (std::string(e.what()) == "wrong_char")
				std::cout << "Please, eneter a number (must contain only the digits)" << std::endl;
		}
	}

	return result;
}

std::vector<size_t> long_mult(const std::vector<size_t> left, const std::vector<size_t> right)
{
	return std::vector<size_t>();
}