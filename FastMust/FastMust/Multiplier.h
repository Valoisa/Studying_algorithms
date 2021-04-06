#include <vector>

//	Synonims
typedef std::vector<int> number;

//	Classes
class Number
{
public:
//	Constructors/destructor
/*
		Number constructor
		Params: string
*/
	Number(const std::string& number);

//	Public methods
/*
		Prints the number
		Params: none
		Return: none
*/
	void print(void) const;

//	Friend functions
/*
		Adds two Numbers
		Params: numbers two add
		Return: sum
*/
	friend Number operator+(const Number& a, const Number& b);

/*
		Find the diff between the two nubers
		Params: minuend, substrahend
		Return: diff
*/
	friend Number operator-(const Number& a, const Number& b);

/*
		Mults two numbers
		Params: numbers to multiply
		Return: product
*/
	friend Number operator*(const Number& a, const Number& b);

private:
//	Classes
	typedef std::vector<int> number_vec;

//	Number - private constructors
/*
		Number constructor
		Params: sign, vector
*/
	Number(const number_vec& number_, const bool positive);

//	Methods
/*
		Gets the digit by the given index
		Params: index
		Return: digit
*/
	const size_t operator[](const size_t idx) const;

/*
		Less than operator (for modules)
		Params: number to compare
		Return: comparison result
*/
	bool lt_mod(const Number& other) const;

/*
		Greater than operator (for modules)
		Params: number to compare
		Return: comparison result
*/
	bool gt_mod(const Number& other) const;

/*
		Equal to operator (for modules)
		Params: number to compare
		Return: comparison result
*/
	bool eq_mod(const Number& other) const;

/*
		Not equal to operator (for modules)
		Params: number to compare
		Return: comparison result
*/
	bool neq_mod(const Number& other) const;

/*
		Less or equal operator (for modules)
		Params: number to compare
		Return: comparison result
*/
	bool loe_mod(const Number& other) const;

/*
		Greater or equal operator (for modules)
		Params: number to compare
		Return: comparison result
*/
	bool goe_mod(const Number& other) const;

/*
		Adds two long numbers
		Params: number to add, sum sign
		Return: sum
*/
	Number long_add(const Number& x, const bool sign) const;

/*
		Subs two long numbers
		Params: number to sub, diff sign
		Return: diff
*/
	Number long_sub(const Number& x, const bool sign) const;

/*
		Multiplies two long numbers
		Params: factor, product sign
		Return: product
*/
	Number long_mult(const Number& x, const bool sign) const;

/*
		Multiplies two long numbers
		Params: numbers to multiply
		Return: product
*/
	void trim_left(void);

//	Members
//		Sign
	bool m_positive;
//		Number
	number_vec m_number;
};

//	Global functions
/*
		Reads the long number
		Params: none
		Return: long number
*/
std::string read_number(void);

/*
		Recursively multiplies two long numbers
		Params: numbers to multiply
		Return: product
*/
number rec_mult(const number& x, const number& y);

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