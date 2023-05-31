#pragma once
#include "common_libs.h"

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.size() == 0)
	{
		return false;
	}

	// RESOLVED: убрать std::max_element
	T maxEl = arr[0];
	std::for_each(arr.begin(), arr.end(), [&](const T& curr) {
		if (less(maxEl, curr))
		{
			maxEl = curr;
		}
	});

	maxValue = maxEl;
	return true;
}