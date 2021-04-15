//	Matrix.h
//	Standard includes
#include <vector>
#include <exception>
#include <iostream>
#include <iomanip>
#include <functional>
//	Local includes
#include "Helpers.h"

//	Macros
//		Max number
#define max(a,b) ((a)>(b)?(a):(b))

//	Global classes
//		Matrix template class
template <typename Elem>
class Matrix
{
public:
	//	Matrix constructors/destructor
	/*
			Matrix constructor
			Params: dims
	*/
	Matrix(const size_t row_count, const size_t col_count) : m_row_count(row_count), m_col_count(col_count)
	{
		m_matrix.assign(row_count, Matrix::row_type(col_count, Elem()));
	}

	/*
			Square matrix constructor
			Params: dim
	*/
	explicit Matrix(const size_t n) : m_row_count(n), m_col_count(n)
	{
		m_matrix.assign(m_row_count, Matrix::row_type(m_col_count, Elem()));
	}

	//	Public methods
	/*
			Print matrix
			Params: none
			Return: none
	*/
	void print(void)
	{
		for (size_t i = 0; i < m_row_count; ++i)
		{
			std::cout.width(3);
			for (size_t j = 0; j < m_col_count; ++j)
				std::cout << m_matrix[i][j] << " ";
			std::cout << std::endl;
		}
	}

	//	Friend functions
	/*
			Sums two matrices
			Params: matrices to sum
			Return: sum
	*/
	friend Matrix operator+(const Matrix& a, const Matrix& b)
	{
		const bool equal_dims = a.m_row_count == b.m_row_count && a.m_col_count == b.m_col_count;
		if (!equal_dims)
			throw std::exception("Unable to sum matrices with the unequal dimensions.");
		Matrix res(a.m_row_count, a.m_col_count);
		for (size_t i = 0; i < a.m_row_count; ++i)
			for (size_t j = 0; j < a.m_col_count; ++j)
				res.m_matrix[i][j] = a.m_matrix[i][j] + b.m_matrix[i][j];
		return res;
	}

	/*
			Matrices subtraction
			Params: minuend, subtrahend
			Return: diff
	*/
	friend Matrix operator-(const Matrix& a, const Matrix& b)
	{
		const bool equal_dims = a.m_row_count == b.m_row_count && a.m_col_count == b.m_col_count;
		if (!equal_dims)
			throw std::exception("Unable to find the diff between the matrices with the unequal dimensions.");
		Matrix res(a.m_row_count, a.m_col_count);
		for (size_t i = 0; i < a.m_row_count; ++i)
			for (size_t j = 0; j < a.m_col_count; ++j)
				res.m_matrix[i][j] = a.m_matrix[i][j] - b.m_matrix[i][j];
		return res;
	}

	/*
			Multiplies two matrices
			Params: matricex to multiply
			Retun: product
	*/
	friend Matrix operator*(const Matrix& a, const Matrix& b)
	{
		const bool equal_dims = a.m_col_count == b.m_col_count;
		if (!equal_dims)
			throw std::exception("Unable to multiply matrices with incoherent dimensions.");
		Matrix res(a.m_row_count, b.m_col_count);
		for (size_t i = 0; i < a.m_row_count; ++i)
			for (size_t j = 0; j < b.m_row_count; ++j)
				for (size_t k = 0; k < a.m_col_count; ++k)
					res.m_matrix[i][j] += a.m_matrix[i][k] * b.m_matrix[k][j];
		return res;
	}

	/*
			Strassen matrices multiplication 
			Params: matrices to multiply
			Return: product
	*/
	friend Matrix strassen(const Matrix& a, const Matrix& b)
	{
		const size_t max_dim = max(max(a.m_row_count, b.m_row_count), max(a.m_col_count, b.m_col_count));
		const size_t pow = nearest_power(max_dim);
		const Matrix x = a.squarize(pow);
		const Matrix y = b.squarize(pow);
		Matrix res = strassen_mult(x, y);
		res.resize(a.m_row_count, b.m_col_count);
		return res;
	}

//	Static methods
/*
		Randomly generates an integer matrix
		Params: n x m, functor to generate the element of the matrix
		Return: integer matrix
*/
	static Matrix generate_matrix(const size_t n, const size_t m, const std::function<Elem()>& functor)
	{
		Matrix result(n, m);
		for (size_t i = 0; i < n; ++i)
			for (size_t j = 0; j < m; ++j)
				result.m_matrix[i][j] = functor();
		return result;
	}

private:
//	Matrix private constructors
/*
		Matrix private defaut constructor
		Params: none
*/
	Matrix(void) : m_row_count(0), m_col_count(0)
	{
	}

//	Matrix private methods
/*
		Makes matric a square matrix with a size of power of 2
		Params: size
		Return: squarized matrix
*/
	Matrix squarize(const size_t n) const
	{
		size_t pow = nearest_power(n);
		Matrix res(pow);
		for (size_t i = 0; i < m_row_count; ++i)
			for (size_t j = 0; j < m_col_count; ++j)
				res.m_matrix[i][j] = m_matrix[i][j];
		return res;
	}

/*
		Cuts matrix to the given size
		Params: n x m
		Reutrn: none
*/
	void resize(const size_t n, const size_t m)
	{
		m_row_count = n;
		m_col_count = m;
		m_matrix.resize(n);
		for (auto& row : m_matrix)
			row.resize(m);
	}

//	Private static methods
	/*
			Strassen matrices multiplication (only for square matricex)
			Params: matrices to multiply
			Return: product
	*/
	static Matrix strassen_mult(const Matrix& a, const Matrix& b)
	{
		if (a.m_row_count == 1 && b.m_row_count == 1)
			return a * b;
	//		Divide matrices
		const size_t n = a.m_row_count;
		const size_t n_2 = n / 2;
		Matrix a11(n_2);
		Matrix a12(n_2);
		Matrix a21(n_2);
		Matrix a22(n_2);
		for (size_t i = 0; i < n_2; ++i)
			for (size_t j = 0; j < n_2; ++j)
			{
				a11.m_matrix[i][j] = a.m_matrix[i][j];
				a12.m_matrix[i][j] = a.m_matrix[i][j + n_2];
				a21.m_matrix[i][j] = a.m_matrix[i + n_2][j];
				a22.m_matrix[i][j] = a.m_matrix[i + n_2][j + n_2];
			}
		Matrix b11(n_2);
		Matrix b12(n_2);
		Matrix b21(n_2);
		Matrix b22(n_2);
		for (size_t i = 0; i < n_2; ++i)
			for (size_t j = 0; j < n_2; ++j)
			{
				b11.m_matrix[i][j] = b.m_matrix[i][j];
				b12.m_matrix[i][j] = b.m_matrix[i][j + n_2];
				b21.m_matrix[i][j] = b.m_matrix[i + n_2][j];
				b22.m_matrix[i][j] = b.m_matrix[i + n_2][j + n_2];
			}
	//		Count products
		const Matrix p1 = strassen_mult(a11, b12 - b22);
		const Matrix p2 = strassen_mult(a11 + a12, b22);
		const Matrix p3 = strassen_mult(a21 + a22, b11);
		const Matrix p4 = strassen_mult(a22, b21 - b11);
		const Matrix p5 = strassen_mult(a11 + a22, b11 + b22);
		const Matrix p6 = strassen_mult(a12 - a22, b21 + b22);
		const Matrix p7 = strassen_mult(a11 - a21, b11 + b12);

	//		Build up the result
		const Matrix r11 = p5 + p4 - p2 + p6;
		const Matrix r12 = p1 + p2;
		const Matrix r21 = p3 + p4;
		const Matrix r22 = p1 + p5 - p3 - p7;

		Matrix res(n);
		for (size_t i = 0; i < n_2; ++i)
			for (size_t j = 0; j < n_2; ++j)
			{
				res.m_matrix[i][j] = r11.m_matrix[i][j];
				res.m_matrix[i][j + n_2] = r12.m_matrix[i][j];
				res.m_matrix[i + n_2][j] = r21.m_matrix[i][j];
				res.m_matrix[i + n_2][j + n_2] = r22.m_matrix[i][j];
			}
		return res;
	}

//	Classes
//		Row type
	typedef std::vector<Elem> row_type;
//		Matrix type
	typedef std::vector<row_type> matrix_type;

//	Members
//		Row count
	size_t m_row_count;
//		Colonm count
	size_t m_col_count;
//		Matrix
	matrix_type m_matrix;
};
