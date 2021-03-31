#include "Sorter.h"

int main()
{
	std::vector<int> data = {9, 43, 66, 22, 50, 72, 83, 26, 87, 79};
	Sorter<int> sorter(data);
//	sorter.insertion_sort();
//	sorter.selection_sort();
//	sorter.merge_sort();
	size_t invs = sorter.count_inversions();
	return 0;
}