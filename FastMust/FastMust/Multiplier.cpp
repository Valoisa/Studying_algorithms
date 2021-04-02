//	Local includes
#include "Multiplier.h"

//	Standard includes
#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <exception>

//	Local functions
/*
		Trims left zeros in the number
		Params: number to trim
		Return: result
*/
number trim_left(const number& num)
{
	size_t zeros = 0;
	auto it = num.begin();
	while (*it == 0)
	{
		++zeros;
		++it;
	}
	number trimmed_result;
	trimmed_result.reserve(num.size() - zeros);
	for (; it != num.end(); ++it)
		trimmed_result.push_back(*it);
	return trimmed_result;
}

//	Global functions implementation
number read_number(void)
{
	static const std::set<char> digits({ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' });
	number result;
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

number long_mult(const number& left, const number& right)
{
	number result(2 * std::max(left.size(), right.size()), 0);
	size_t pos = 0;
	for (auto lit = left.rbegin(); lit != left.rend(); ++lit)
	{
		size_t c = 0;
		auto res_pos = result.rbegin() + pos;
		for (auto rit = right.rbegin(); rit != right.rend(); ++rit)
		{
			const size_t x = (*lit) * (*rit) + (*res_pos) + c;
			const size_t r = x % 10;
			c = x / 10;
			*res_pos = r;
			++res_pos;
		}
		*res_pos = c;
		++pos;
	}
	
	return trim_left(result);
}

number long_add(const number& left, const number& right)
{
	number result(std::max(left.size(), right.size()) + 1, 0);
	auto lit = left.rbegin();
	auto rit = right.rbegin();
	auto res_pos = result.rbegin();
	size_t c = 0;
	while (lit != left.rend() || rit != right.rend())
	{
		const size_t a = lit == left.rend() ? 0 : *lit;
		const size_t b = rit == right.rend() ? 0 : *rit;
		const size_t x = a + b + c;
		*res_pos = x % 10;
		c = x / 10;
		if (lit != left.rend())
			++lit;
		if (rit != right.rend())
			++rit;
		++res_pos;
	}
	*res_pos = c;
	//while (lit != left.rend())
	//{
	//	*res_pos += *lit;
	//	++lit;
	//	++res_pos;
	//}
	//while (rit != right.rend())
	//{
	//	*res_pos += *rit;
	//	++rit;
	//	++res_pos;
	//}

	return trim_left(result);
}