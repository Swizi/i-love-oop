#pragma once
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../FindMax.hpp"
#include "Sportsman.h"

SCENARIO("Function can find max element in not empty array")
{
	WHEN("Array is not empty and try to find max by height")
	{
		const std::vector<Sportsman> arr = {
			{"Ivan Petrov Grigoriyevich", 180, 90},
			{"Denis Ivanov Ivanovich", 210, 120},
			{"Alexanded Konkov Alexandrovich", 188, 90}
		};
		Sportsman maxValue;
		const bool result = FindMax(arr, maxValue, CompareLessHeight);

		THEN("Function can find max in arr")
		{
			REQUIRE(result == true);
			REQUIRE(maxValue.height == 210);
		}
	}

	WHEN("Array is not empty and try to find max from numbers")
	{
		const std::vector<int> arr = {
			0, 1, 2, 3, 4, -1
		};
		int maxValue;
		const bool result = FindMax(arr, maxValue, [](const int left, const int right) {return left < right; });

		THEN("Function can find max in arr")
		{
			REQUIRE(result == true);
			REQUIRE(maxValue == 4);
		}
	}

	WHEN("Array is not empty and try to find max by weight")
	{
		const std::vector<Sportsman> arr = {
			{"Ivan Petrov Grigoriyevich", 180, 90},
			{"Denis Ivanov Ivanovich", 210, 120},
			{"Alexanded Konkov Alexandrovich", 188, 90}
		};
		Sportsman maxValue;
		const bool result = FindMax(arr, maxValue, CompareLessWeight);

		THEN("Function can find max in arr")
		{
			REQUIRE(result == true);
			REQUIRE(maxValue.weight == 120);
		}
	}

	WHEN("Array has one element and try to find max by weight")
	{
		const std::vector<Sportsman> arr = {
			{"Ivan Petrov Grigoriyevich", 180, 90}
		};
		Sportsman maxValue;
		const bool result = FindMax(arr, maxValue, CompareLessWeight);

		THEN("Function should return this element")
		{
			REQUIRE(result == true);
			REQUIRE(maxValue.weight == 90);
		}
	}

	WHEN("Array has one element and try to find max by height")
	{
		const std::vector<Sportsman> arr = {
			{"Ivan Petrov Grigoriyevich", 180, 90}
		};
		Sportsman maxValue;
		const bool result = FindMax(arr, maxValue, CompareLessHeight);

		THEN("Function should return this element")
		{
			REQUIRE(result == true);
			REQUIRE(maxValue.weight == 90);
		}
	}

	WHEN("Array has one element and try to find max from numbers")
	{
		const std::vector<int> arr = {
			-1
		};
		int maxValue;
		const bool result = FindMax(arr, maxValue, [](const int left, const int right) {return left < right; });

		THEN("Function can find max in arr")
		{
			REQUIRE(result == true);
			REQUIRE(maxValue == -1);
		}
	}
}

SCENARIO("Function can't find max element in empty array")
{
	WHEN("Array is empty")
	{
		const std::vector<Sportsman> arr = {};
		Sportsman maxValue;
		const bool result = FindMax(arr, maxValue, CompareLessWeight);

		THEN("Function should return false")
		{
			REQUIRE(result == false);
		}
	}
}