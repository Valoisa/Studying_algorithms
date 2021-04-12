//	Matrix.h
//	Standard includes
#include <vector>
#include <exception>
#include <iostream>
#include <iomanip>

//	C includes
#include <stdlib.h>
#include <time.h>  

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
		m_matrix.assign(row_count, Matrix::row_type(col_count, 0));
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

//	Static methods
/*
		Randomly generates an integer matrix
		Params: n x m
		Return: integer matrix
*/
	static Matrix<int> generate_matrix(const size_t n, const size_t m)
	{
		Matrix<int> result(n, m);
		srand(time(NULL));
		for (size_t i = 0; i < n; ++i)
			for (size_t j = 0; j < m; ++j)
				result.m_matrix[i][j] = rand() % 100;
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
