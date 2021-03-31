#include <vector>

//	Global functions
/*
		Reads the long number
		Params: none
		Return: long number
*/
std::vector<size_t> read_number(void);

/*
		Long multiplication
		Params: numbers to multiply
		Return: product
*/
std::vector<size_t> long_mult(const std::vector<size_t> left, const std::vector<size_t> right);

//	Classes
class Multiplier
{
public:

private:

//	Members
//		First factor
	std::vector<size_t> m_first_factor;
//		Second factor
	std::vector<size_t> m_second_factor;
//		Product
	std::vector<size_t> m_product;
};