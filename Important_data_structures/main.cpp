#include <iostream>
#include <vector>

#include "BinarySearchTree.h"
#include "BinaryHeap.h"
#include "AVLTree.h"

struct FakeStruct
{
	FakeStruct(const int elem_) : elem(elem_)
	{
	}

	bool operator<(const FakeStruct& other) const
	{
		return elem < other.elem;
	}

	int elem;
};

int main()
{
//	std::vector<FakeStruct> unordered({ 6, 9, 3, 8, 4, 5, 1, 6, 2, 7 });
	std::vector<FakeStruct> unordered({ 9, 8, 7, 6, 5, 4, 3, 2, 1 });

	Trees::BinaryHeap<FakeStruct> heap(unordered);
	Trees::BinaryHeap<int> heap(unordered.size());
	for (size_t i = 0; i < unordered.size(); ++i)
		heap.insert(unordered[i]);
	while (!heap.empty())
	{
		std::cout << heap.top().elem << std::endl;
		heap.pop();
	}

	Trees::BinarySearchTree<FakeStruct, int> bin_tree;
	for (size_t i = 0; i < unordered.size(); ++i)
		bin_tree.insert(unordered[i], i);
	const auto result = bin_tree.find(2);
	bin_tree.remove(2);
	bin_tree.traverse([](const FakeStruct& key, int& val)
	{
		std::cout << key.elem << std::endl;
//		val = val * 10;
	});

	Trees::AVLTree<FakeStruct, int> avl_tree;
	for (size_t i = 0; i < unordered.size(); ++i)
		avl_tree.insert(unordered[i], i);
	avl_tree.remove(4);

	avl_tree.traverse([](const FakeStruct& key, int& val)
	{
		std::cout << key.elem << std::endl;
//		val = val * 10;
	});


	return 0;
}