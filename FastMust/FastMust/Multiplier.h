#include <vector>

//	Synonims
typedef std::vector<size_t> number;

//	Global functions
/*
		Reads the long number
		Params: none
		Return: long number
*/
number read_number(void);

/*
		Long multiplication
		Params: numbers to multiply
		Return: product
*/
number long_mult(const number& left, const number& right);

/*
		Long addition
		Params: numbers to sum
		Return: sum
*/
number long_add(const number& left, const number& right);

//	Classes
class Multiplier
{
public:

private:

//	Members
//		First factor
	number m_first_factor;
//		Second factor
	number m_second_factor;
//		Product
	number m_product;
};