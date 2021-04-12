#include "Matrix.h"

int main()
{
	Matrix<int> a = Matrix<int>::generate_matrix(2, 2);
	a.print();
	std::cout << std::endl;
	Matrix<int> b = Matrix<int>::generate_matrix(2, 2);
	b.print();
	std::cout << std::endl;
	Matrix<int> res = strassen(a, b);
	res.print();
	return 0;
}