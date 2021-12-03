/*
	This is the template implementation of the Binary Heap. It is a so-called max-heap by default.
	Rules of the BH building:
		1) The value of any node is greater or equal to the value of its descendants.
		2) A binary heap is a complete binary tree, which means that all levels of the tree, except possibly the last one, are fully filled,
		   and if the last level of the tree is not complete, that nodes of that level are filled from left to right.

	Operations:
		1) Insert O(log n)
		2) GetMin/GetMax O(1)
		3) DelMin/DelMax O(log n)
		4) Heapify (turn unordered array to a heap) O(n)

	Space complexity is O(n)
*/

#include <vector>
#include <memory>
#include <exception>

#include "Exception.h"

namespace Trees
{
//		BinaryHeap class

template <class ElemType, class Comparator = std::less<ElemType>>
class BinaryHeap
{
public:
/*
		BinaryHeap constructor
		Params: size, comparator
*/
	explicit BinaryHeap(const size_t size, const Comparator comp = Comparator()) : m_comparator(comp)
	{
		m_storage.reserve(size);
	}

/*
		BinaryHeap constructor
		Params: vector, comparator
*/
	explicit BinaryHeap(const std::vector<ElemType> input, const Comparator comp = Comparator()) :
		m_storage(input), m_comparator(comp)
	{
		for (size_t index = input.size() / 2; index--;)
			shift_down(index);
	}

/*
		Gets the top element (which is max/min) without deleting it
		Params: none
		Return: top element
*/
	const ElemType& top(void) const
	{
		if (m_storage.empty())
			throw Exception(L"Attempt to get the top of the empty heap");
		return m_storage[0];
	}

/*
		Pops the top element out of the heap
		Params: none
		Return: none
*/
	void pop(void)
	{
		if (m_storage.empty())
			return;
		if (m_storage.size() == 1)
		{
			m_storage.pop_back();
			return;
		}
		std::swap(m_storage[0], m_storage[m_storage.size() - 1]);
		m_storage.pop_back();
		shift_down(0);
	}

/*
		Inserts the element to the heap
		Params: element to insert
		Return: none
*/
	void insert(const ElemType& elem)
	{
		m_storage.push_back(elem);
		shift_up(m_storage.size() - 1);
	}

/*
		Binary heap emptiness checker
		Params: none
		Return: check result
*/
	bool empty(void) const
	{
		return m_storage.empty();
	}

private:
//	Types
//		Storage type
	typedef std::vector<ElemType> storage_type;
//	Methods
/*
		
*/
	void shift_up(const size_t index)
	{
		if (index >= m_storage.size())
			throw Exception(L"The element's index is out of range.");
		if (index == 0)
			return;

		const size_t parent_index = (index - 1) / 2;
		ElemType& parent = m_storage[parent_index];
		ElemType& current = m_storage[index];
		if (m_comparator(parent, current))
			return;
		std::swap(current, parent);
		shift_up(parent_index);
	}

/*

*/
	void shift_down(const size_t index)
	{
		const size_t storage_size = m_storage.size();
		if (index >= storage_size)
			throw Exception(L"The element's index is out of range.");
		ElemType& current = m_storage[index];

		const size_t left_child_idx = (index * 2) + 1;
		const size_t right_child_idx = (index * 2) + 2;

		ElemType* left_child = left_child_idx < storage_size ? &m_storage[left_child_idx] : nullptr;
		ElemType* right_child = right_child_idx < storage_size ? &m_storage[right_child_idx] : nullptr;

		if (left_child == nullptr && right_child == nullptr)
			return;

		ElemType* elem_to_compare = nullptr;
		size_t elem_to_compare_idx = 0;
		const bool left = left_child != nullptr && right_child != nullptr ? m_comparator(*left_child, *right_child) : left_child != nullptr;
		elem_to_compare = left ? left_child : right_child;
		elem_to_compare_idx = left ? left_child_idx : right_child_idx;
		if (m_comparator(current, *elem_to_compare))
			return;

		std::swap(current, *elem_to_compare);
		shift_down(elem_to_compare_idx);
	}

//	Members
//		Storage
	storage_type m_storage;
//		Comparator
	Comparator m_comparator;
};
}
