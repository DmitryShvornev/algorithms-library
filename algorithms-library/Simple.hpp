#pragma once
#include <vector>

// алгоритм Евклида
int GCD(int a, int b) {
	while (b != 0)
	{
		int remainder = a % b;
		a = b;
		b = remainder;
	}
	return a;
}

template<class __DataType>
__DataType FindLargest(std::vector<__DataType> arr) {
	__DataType largest = arr[0];
	for (unsigned i = 1; i < arr.size(); i++)
	{
		if (arr[i] > largest)
		{
			largest = arr[i];
		}
	}
	return largest;
}

template<class __DataType>
bool ContainsDuplicates(std::vector<__DataType> arr) {
	for (unsigned i = 0; i < arr.size() - 1; i++)
	{
		for (unsigned j = i + 1; j < arr.size(); j++)
		{
			if (i != j)
			{
				if (arr[i] == arr[j])
				{
					return true;
				}
			}
		}
	}
	return false;
}
