//	C includes
#include <stdlib.h>
#include <time.h>

//	Local includes
#include "Matrix.h"

int main()
{
	const auto& randomize = []() 
	{
//		srand(time(NULL));
		return rand() % 100;
	};
	Matrix<int> a = Matrix<int>::generate_matrix(2, 2, randomize);
	a.print();
	std::cout << std::endl;
	Matrix<int> b = Matrix<int>::generate_matrix(2, 2, randomize);
	b.print();
	std::cout << std::endl;
	Matrix<int> res = strassen(a, b);
	res.print();
	return 0;
}