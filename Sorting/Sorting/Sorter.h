#include <vector>
#include <limits>

template <typename Comparable>
class Sorter
{
public:
//	Constructors/destructor
/*
		Sorter constructor
		Params: vector
*/
	Sorter(const std::vector<Comparable>& data) : m_input(data), m_output(data), m_sorted(false)
	{
	}

//	Public methods
/*
		Insertion sort: best O(n), average O(n^2), worst O(n^2); space: O(1)
		Params: none
		Return: none
*/
	void insertion_sort(void)
	{
		if (m_sorted)
			m_output = m_input;

		insertion_sort_impl();
		m_sorted = true;
	}

/*
		Selection sort: best, avg, worst O(n^2); space: O(1)
		Params: none
		Return: none
*/
	void selection_sort(void)
	{
		if (m_sorted)
			m_output = m_input;

		selection_sort_impl();
		m_sorted = true;
	}

/*
		Merge sort: best, avg, worst O(n log n); space: O(n)
		Params: none
		Return: none
*/
	void merge_sort(void)
	{
		if (m_sorted)
			m_output = m_input;

		const size_t left = 0;
		const size_t right = m_output.size() - 1;

		merge_sort_impl(left, right);
		m_sorted = true;
	}

/*
		Counts inversions in the array
		Params: none
		Return: number of inversions
*/
	size_t count_inversions(void)
	{
		if (m_sorted)
			m_output = m_input;

		const size_t left = 0;
		const size_t right = m_output.size() - 1;
		return count_inversions_impl(left, right);
	}

private:
//	Private methods
/*
		Insertion sort implementation
		Params: none
		Return: none
*/
	void insertion_sort_impl(void)
	{
		for (size_t i = 1; i < m_output.size(); ++i)
		{
			const Comparable temp = m_output[i];
			bool not_placed = true;
			for (size_t j = i - 1; j >= 0 && j < std::numeric_limits<size_t>::max(); --j)
			{
				if (m_output[j] > temp)
					m_output[j + 1] = m_output[j];
				else
				{
					m_output[j + 1] = temp;
					not_placed = false;
					break;
				}
			}

			if (not_placed)
				m_output[0] = temp;
		}
	}

/*
		Selection sort implementation
		Params: none
		Return: none
*/
	void selection_sort_impl(void)
	{
		for (size_t i = m_output.size() - 1; i >= 0 && i < std::numeric_limits<size_t>::max(); --i)
		{
			size_t max_idx = i;
			for (size_t j = 0; j < i; ++j)
				if (m_output[j] > m_output[max_idx])
					max_idx = j;
			if (max_idx != i)
				std::swap(m_output[i], m_output[max_idx]);
		}
	}

/*
		Merge sort implementation
		Params: input, left, right
		Return: none
*/
	void merge_sort_impl(const size_t left, const size_t right)
	{
		if (left >= right)
			return;

		const size_t mid = left + (right - left) / 2;
		merge_sort_impl(left, mid);
		merge_sort_impl(mid + 1, right);
		merge_impl(left, mid, right);
	}

/*
		Merge sort helper method: merges two sorted arrays
		Params: input, left, mid, right
		Return: none
*/
	void merge_impl(const size_t left, const size_t mid, const size_t right)
	{
		std::vector<Comparable> temp_left;
		temp_left.reserve(mid - left + 1);
		for (size_t i = left; i <= mid; ++i)
			temp_left.push_back(m_output[i]);

		std::vector<Comparable> temp_right;
		temp_right.reserve(right - mid + 1);
		for (size_t i = mid + 1; i <= right; ++i)
			temp_right.push_back(m_output[i]);

		size_t l = 0;
		size_t r = 0;
		size_t i = left;
		while (l < temp_left.size() && r < temp_right.size())
		{
			if (temp_left[l] < temp_right[r])
			{
				m_output[i] = temp_left[l];
				++l;
			}
			else
			{
				m_output[i] = temp_right[r];
				++r;
			}
			++i
		}
		while (l < temp_left.size())
		{
			m_output[i] = temp_left[l];
			++i;
			++l;
		}
		while (r < temp_right.size())
		{
			m_output[i] = temp_right[r];
			++i;
			++r;
		}
	}

/*
		Inversions counter (implementation)
		Params: left and right indices of the array
		Return: number of inversions
*/
	size_t count_inversions_impl(const size_t left, const size_t right)
	{
		if (left >= right)
			return 0;
		const size_t mid = left + (right - left) / 2;

		const size_t left_inv = count_inversions_impl(left, mid);
		const size_t right_inv = count_inversions_impl(mid + 1, right);
		const size_t split_inv = count_split_inversions_impl(left, mid, right);

		return left_inv + right_inv + split_inv;
	}

/*
		Counts the number of the split inversions
		Params: left, middle and right indices of the array
		Return: number of split inversions
*/
	size_t count_split_inversions_impl(const size_t left, const size_t mid, const size_t right)
	{
		std::vector<Comparable> temp_left;
		temp_left.reserve(mid - left + 1);
		for (size_t i = left; i <= mid; ++i)
			temp_left.push_back(m_output[i]);

		std::vector<Comparable> temp_right;
		temp_right.reserve(right - mid + 1);
		for (size_t i = mid + 1; i <= right; ++i)
			temp_right.push_back(m_output[i]);

		size_t inv_num = 0;
		size_t l = 0;
		size_t r = 0;
		size_t i = left;
		while (l < temp_left.size() && r < temp_right.size())
		{
			if (temp_left[l] <= temp_right[r])
			{
				m_output[i] = temp_left[l];
				++l;
			}
			else
			{
				m_output[i] = temp_right[r];
				inv_num += temp_left.size() - l;
				++r;
			}
			++i;
		}
		while (l < temp_left.size())
		{
			m_output[i] = temp_left[l];
			++l;
			++i;
		}
		while (r < temp_right.size())
		{
			m_output[i] = temp_right[r];
			++r;
			++i;
		}
		return inv_num;
	}

//	Members
//		Input; stores input state before sorting
	std::vector<Comparable> m_input;
//		Output: stores input state after sorting
	std::vector<Comparable> m_output;
//		Sorted flag
	bool m_sorted;
};