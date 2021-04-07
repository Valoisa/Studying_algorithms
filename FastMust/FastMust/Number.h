#include <vector>

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

//	Static methods
/*
		Karatsuba multiplication
		Params: factors
		Return: product
*/
	friend Number karatsuba_mult(const Number& x, const Number& y);

private:
//	Classes
	typedef std::vector<int> number_vec;

//	Number - private constructors
/*
		Number private default constructor
		Params: none
*/
	Number(void);

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
		Gets the size of the number
		Params: none
		Return: size
*/
	const size_t size(void) const;

/*
		Breaks a number into two half-numbers
		Params: output numbers, half-size
		Return: none
*/
	void half_number(Number& beg, Number& end, const size_t half_size) const;

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
