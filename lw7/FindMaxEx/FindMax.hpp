#pragma once
#include "common_libs.h"

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	// TODO: убрать std::max_element
	auto maxEl = std::max_element(arr.begin(), arr.end(), less);

	if (maxEl != arr.end())
	{
		maxValue = *maxEl;
		return true;
	}

	return false;
}