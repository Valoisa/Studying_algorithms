//	Local includes
#include "Multiplier.h"

//	Standard includes
#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <exception>

//	Classes implementation
//		Number - constructors/destructor
Number::Number(const std::string& number)
{
	const bool positive = number[0] != '-';
	m_positive = positive;
	size_t i = positive ? 0 : 1;
	m_number.reserve(number.size() - i);
	for (; i < number.size(); ++i)
		m_number.push_back((int)(number[i] - '0'));
}

//		Number - friend functions
Number operator+(const Number& a, const Number& b)
{
	if (!(a.m_positive ^ b.m_positive)) // same signs
		return a.long_add(b, a.m_positive);
	else // different signs
	{
		const bool a_gr_b = a.gt_mod(b);
		const auto& c = a_gr_b ? a : b;
		const auto& d = a_gr_b ? b : a;
		return c.long_sub(d, c.m_positive);
	}
}

Number operator-(const Number& a, const Number& b)
{
	const Number b_oppos(b.m_number, !b.m_positive);
	return a + b_oppos;
}

Number operator*(const Number& a, const Number& b)
{
	const bool sign = !(a.m_positive ^ b.m_positive);
	return a.long_mult(b, sign);
}

//		Number - private constructors
Number::Number(const number_vec& number_, const bool positive) : m_number(number_), m_positive(positive)
{
}

//		Number - private methods
const size_t Number::operator[](const size_t idx) const
{
	return m_number[idx];
}
bool Number::lt_mod(const Number& other) const
{
	if (m_number.size() != other.m_number.size())
		return m_number.size() < other.m_number.size();
	for (size_t i = 0; i < m_number.size(); ++i)
	{
		if (m_number[i] != other.m_number[i])
			return m_number[i] < other.m_number[i];
	}
	return false;
}

bool Number::gt_mod(const Number& other) const
{
	if (m_number.size() != other.m_number.size())
		return m_number.size() > other.m_number.size();
	for (size_t i = 0; i < m_number.size(); ++i)
	{
		if (m_number[i] != other.m_number[i])
			return m_number[i] > other.m_number[i];
	}
	return false;
}

bool Number::eq_mod(const Number& other) const
{
	if (m_number.size() != other.m_number.size())
		return false;
	for (size_t i = 0; i < m_number.size(); ++i)
	{
		if (m_number[i] != other.m_number[i])
			return false;
	}
	return true;
}

bool Number::neq_mod(const Number& other) const
{
	return !(eq_mod(other));
}

bool Number::loe_mod(const Number& other) const
{
	return !(gt_mod(other));
}

bool Number::goe_mod(const Number& other) const
{
	return !(lt_mod(other));
}

Number Number::long_add(const Number& x, const bool sign) const
{
	const auto& left = m_number;
	const auto& right = x.m_number;
	Number result(number_vec(std::max(left.size(), right.size()) + 1, 0), sign);
	auto lit = left.rbegin();
	auto rit = right.rbegin();
	auto res_pos = result.m_number.rbegin();
	int c = 0;
	while (lit != left.rend() || rit != right.rend())
	{
		const int a = lit == left.rend() ? 0 : *lit;
		const int b = rit == right.rend() ? 0 : *rit;
		const int x = a + b + c;
		*res_pos = x % 10;
		c = x / 10;
		if (lit != left.rend())
			++lit;
		if (rit != right.rend())
			++rit;
		++res_pos;
	}
	*res_pos = c;
	result.trim_left();
	return result;
}

Number Number::long_sub(const Number& x, const bool sign) const
{
	const auto& left = m_number;
	const auto& right = x.m_number;
	if (left.size() < right.size())
		throw std::exception("Minued must be greater than subtrahend.");
	Number result(number_vec(left.size(), 0), sign);
	auto lit = left.rbegin();
	auto rit = right.rbegin();
	auto res_pos = result.m_number.rbegin();
	int c = 0;
	while (lit != left.rend())
	{
		const int b = (rit == right.rend() ? 0 : *rit);
		const int a = [&]() 
		{
			if (*lit - c >= b)
			{
				const int temp = *lit - c;
				c = 0;
				return temp;
			}
			else
			{
				const int lit_borrowed = *lit + 10;
				if (lit_borrowed - c >= b)
				{
					const int temp = lit_borrowed - c;
					c = 1;
					return temp;
				}
//				Is this ever possible???
				else
				{
					const int temp = lit_borrowed + 10 - c;
					c += 1;
					return temp;
				}
			}
		}();
		*res_pos = a - b;
		if (rit != right.rend())
			++rit;
		++lit;
		++res_pos;
	}
	result.trim_left();
	return result;
}

Number Number::long_mult(const Number& x, const bool sign) const
{
	const auto& left = m_number;
	const auto& right = x.m_number;
	Number result(number_vec(2 * std::max(left.size(), right.size()), 0), sign);
	size_t pos = 0;
	for (auto lit = left.rbegin(); lit != left.rend(); ++lit)
	{
		size_t c = 0;
		auto res_pos = result.m_number.rbegin() + pos;
		for (auto rit = right.rbegin(); rit != right.rend(); ++rit)
		{
			const int x = (*lit) * (*rit) + (*res_pos) + c;
			const int r = x % 10;
			c = x / 10;
			*res_pos = r;
			++res_pos;
		}
		*res_pos = c;
		++pos;
	}
	result.trim_left();
	return result;
}

void Number::trim_left(void)
{
	size_t zeros = 0;
	auto it = m_number.begin();
	while (*it == 0)
	{
		++zeros;
		++it;
	}
	number_vec trimmed_result;
	trimmed_result.reserve(m_number.size() - zeros);
	for (; it != m_number.end(); ++it)
		trimmed_result.push_back(*it);
	m_number.clear();
	m_number = trimmed_result;
}

void Number::print(void) const
{
	std::cout << (m_positive ? "" : "-");
	for (const auto x : m_number)
		std::cout << x;
}

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

/*
		Recursive multiplication implementation
		Params: 
*/

//	Global functions implementation
std::string read_number(void)
{
	static const std::set<char> digits({ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-' });
	std::string result;
	while (result.empty())
	{
		try
		{
			std::cout << "Enter the number:" << std::endl;
			std::cin >> result;

			for (size_t i = 0; i < result.size(); ++i)
			{
				if (digits.find(result[i]) == digits.end())
				{
					result.clear();
					throw std::exception("wrong_char");
				}
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

number rec_mult(const number& x, const number& y)
{
	//if (x.size() == 1 && y.size() == 1)
	//	return long_mult(x, y);

	//const size_t n_2 = x.size() / 2;
	//number a, b, c, d;
	//a.reserve(n_2);
	//size_t i = 0;
	//for (; i < n_2; ++i)
	//	a.push_back(x[i]);
	//b.reserve(n_2);
	//for (; i < x.size(); ++i)
	//	b.push_back(x[i]);
	//i = 0;
	//
	//c.reserve(n_2);
	//for (; i < n_2; ++i)
	//	c.push_back(y[i]);
	//d.reserve(n_2);
	//for (; i < y.size(); ++i)
	//	d.push_back(y[i]);

	//const number ac = rec_mult(a, c);
	//const number bd = rec_mult(b, d);
	//const number abcd = rec_mult(long_add(a, b), long_add(c, d));
//	const number gauss_trick = sub isn't implemented...
	return{};
}