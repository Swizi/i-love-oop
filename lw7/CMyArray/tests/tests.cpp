#pragma once
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../CMyArray.h"
#include <string>

SCENARIO("User has ability to create arrays")
{
	WHEN("User creates array from pointer to array")
	{
		const char* arr = "123\0";
		const size_t arrSize = 4;

		CMyArray<char> myArray = CMyArray<char>(arr, arrSize);

		THEN("Array should be successfully created")
		{
			REQUIRE(strcmp(myArray.GetArray(), "123") == 0);
			REQUIRE(myArray.Count() == 4);
		}
	}

	WHEN("User creates empty array")
	{
		CMyArray<int> myArray;

		THEN("Array should be empty")
		{
			REQUIRE(myArray.GetArray() == nullptr);
			REQUIRE(myArray.Count() == 0);
		}
	}

	WHEN("User creates array containing standard string")
	{
		CMyArray<std::string> myArray;
		myArray.Insert("123");

		THEN("Array should contain standard string")
		{
			REQUIRE(myArray[0] == "123");
			REQUIRE(myArray.Count() == 1);
		}
	}

	WHEN("User creates array containing double")
	{
		CMyArray<double> myArray;
		myArray.Insert(2);
		myArray.Insert(2.1);

		THEN("Array should contain double")
		{
			REQUIRE(myArray[0] == 2.0);
			REQUIRE(myArray[1] == 2.1);
			REQUIRE(myArray.Count() == 2);
		}
	}

	WHEN("User creates array using copy constructor from empty array")
	{
		CMyArray<double> myArray1;
		CMyArray<double> myArray2 = myArray1;

		THEN("Both arrays should be empty")
		{
			REQUIRE(myArray1.GetArray() == nullptr);
			REQUIRE(myArray1.Count() == 0);
			REQUIRE(myArray2.GetArray() == nullptr);
			REQUIRE(myArray2.Count() == 0);
		}
	}

	WHEN("User creates array using copy constructor from filled array")
	{
		CMyArray<double> myArray1;
		myArray1.Insert(3);
		CMyArray<double> myArray2 = myArray1;

		THEN("Array should be equal")
		{
			REQUIRE(myArray1.Count() == 1);
			REQUIRE(myArray2.Count() == 1);
			REQUIRE(myArray1[0] == 3.0);
			REQUIRE(myArray2[0] == 3.0);
		}
	}

	WHEN("User creates array using move constructor from empty array")
	{
		CMyArray<double> myArray1;
		CMyArray<double> myArray2(std::move(myArray1));

		THEN("Both arrays should be empty")
		{
			REQUIRE(myArray1.GetArray() == nullptr);
			REQUIRE(myArray1.Count() == 0);
			REQUIRE(myArray2.GetArray() == nullptr);
			REQUIRE(myArray2.Count() == 0);
		}
	}

	WHEN("User creates array using move constructor from filled array")
	{
		CMyArray<double> myArray1;
		myArray1.Insert(3);
		CMyArray<double> myArray2(std::move(myArray1));

		THEN("First array should be empty, second one should contain stealed elements")
		{
			REQUIRE(myArray1.GetArray() == nullptr);
			REQUIRE(myArray1.Count() == 0);
			REQUIRE(myArray2[0] == 3.0);
			REQUIRE(myArray2.Count() == 1);
		}
	}
}

SCENARIO("User has ability to use assignment operator")
{
	WHEN("User uses copying assignment operator with empty array")
	{
		CMyArray<char> myArrayDest;
		CMyArray<char> myArraySrc;

		myArrayDest = myArraySrc;

		THEN("Both arrays should be empty")
		{
			REQUIRE(myArrayDest.Count() == 0);
			REQUIRE(myArraySrc.Count() == 0);
			REQUIRE(myArrayDest.GetArray() == nullptr);
			REQUIRE(myArraySrc.GetArray() == nullptr);
		}
	}

	WHEN("User uses copying assignment operator with filled array")
	{
		CMyArray<int> myArrayDest;
		CMyArray<int> myArraySrc;
		myArraySrc.Insert(3);
		myArraySrc.Insert(2);

		myArrayDest = myArraySrc;

		THEN("Arrays should be equal")
		{
			REQUIRE(myArrayDest.Count() == 2);
			REQUIRE(myArraySrc.Count() == 2);
			REQUIRE(myArrayDest[0] == 3);
			REQUIRE(myArrayDest[1] == 2);
			REQUIRE(myArraySrc[0] == 3);
			REQUIRE(myArraySrc[1] == 2);
		}
	}

	WHEN("User uses moving assignment operator with empty array")
	{
		CMyArray<char> myArrayDest;
		CMyArray<char> myArraySrc;

		myArrayDest = std::move(myArraySrc);

		THEN("Both arrays should be empty")
		{
			REQUIRE(myArrayDest.Count() == 0);
			REQUIRE(myArraySrc.Count() == 0);
			REQUIRE(myArrayDest.GetArray() == nullptr);
			REQUIRE(myArraySrc.GetArray() == nullptr);
		}
	}

	WHEN("User uses moving assignment operator with filled array")
	{
		CMyArray<char> myArrayDest;
		CMyArray<char> myArraySrc;
		myArraySrc.Insert('a');
		myArraySrc.Insert('b');

		myArrayDest = std::move(myArraySrc);

		THEN("Both arrays should be empty")
		{
			REQUIRE(myArrayDest.Count() == 2);
			REQUIRE(myArraySrc.Count() == 0);
			REQUIRE(myArrayDest[0] == 'a');
			REQUIRE(myArrayDest[1] == 'b');
			REQUIRE(myArraySrc.GetArray() == nullptr);
		}
	}
}

SCENARIO("User has ability to use taking operator by index")
{
	WHEN("User uses operator on empty array")
	{
		CMyArray<int> arr;

		THEN("Exception should be throwed")
		{
			REQUIRE_THROWS(arr[0]);
		}
	}

	WHEN("User uses operator on 1-array to read")
	{
		CMyArray<int> arr;
		arr.Insert(2);

		THEN("Value should be returned")
		{
			REQUIRE(arr[0] == 2);
		}
	}

	WHEN("User uses operator on 1-array to write")
	{
		CMyArray<int> arr;
		arr.Insert(2);
		arr[0] = 3;

		THEN("Value should be overwritten")
		{
			REQUIRE(arr[0] == 3);
		}
	}

	WHEN("User uses operator with index, that is greater than size of array")
	{
		CMyArray<int> arr;
		arr.Insert(2);

		THEN("Exception should be throwed")
		{
			REQUIRE_THROWS(arr[1]);
		}
	}

	WHEN("Users uses operator with negative index")
	{
		CMyArray<int> arr;
		arr.Insert(2);

		THEN("Exception should be throwed")
		{
			REQUIRE_THROWS(arr[-1]);
		}
	}
}

SCENARIO("User has ability to resize array")
{
	WHEN("User resizes empty array")
	{
		CMyArray<int> arr;
		arr.Resize(3);

		THEN("Array should be resized")
		{
			REQUIRE(arr.Count() == 3);
			REQUIRE(arr[0] == 0);
			REQUIRE(arr[1] == 0);
			REQUIRE(arr[2] == 0);
		}
	}

	WHEN("User resizes filled array")
	{
		CMyArray<int> arr;
		arr.Insert(3);
		arr.Resize(3);

		THEN("Array should be resized with saving previous values")
		{
			REQUIRE(arr.Count() == 3);
			REQUIRE(arr[0] == 3);
			REQUIRE(arr[1] == 0);
			REQUIRE(arr[2] == 0);
		}
	}
}

SCENARIO("User has ability to use iterators on array")
{
	GIVEN("Inconstant iterator")
	{
		WHEN("Use begin() ... end() on string")
		{
			auto it = CMyArray<char>("i like JS", 9);
			std::string result = "";

			std::for_each(it.begin(), it.end(), [&](auto ch) {
				result += ch;
			});

			THEN("Iterator should pass through all string's characters")
			{
				REQUIRE(result == "i like JS");
			}
		}

		WHEN("Use begin() ... end() on empty string")
		{
			auto it = CMyArray<char>("", 0);
			std::string result = "";

			std::for_each(it.begin(), it.end(), [&](auto ch) {
				result += ch;
			});

			THEN("Iterator should pass through all string's characters")
			{
				REQUIRE(result == "");
			}
		}

		WHEN("Use rbegin() ... rend() on string")
		{
			auto it = CMyArray<char>("i like JS", 9);
			std::string result = "";

			std::for_each(it.rbegin(), it.rend(), [&](auto ch) {
				result += ch;
			});

			THEN("Iterator should pass through all string's characters")
			{
				REQUIRE(result == "SJ ekil i");
			}
		}

		WHEN("Use rbegin() ... rend() on empty string")
		{
			auto it = CMyArray<char>("", 0);
			std::string result = "";

			std::for_each(it.rbegin(), it.rend(), [&](auto ch) {
				result += ch;
			});

			THEN("Iterator should pass through all string's characters")
			{
				REQUIRE(result == "");
			}
		}

		WHEN("Try to change element, that pointed by iterator")
		{
			CMyArray<std::string> arr;
			arr.Insert("123");
			auto it = arr.begin();

			*it = "another str";

			THEN("Element should be changed")
			{
				REQUIRE(arr[0] == "another str");
			}
		}

		WHEN("Try to use access index operator")
		{
			CMyArray<std::string> arr;
			arr.Insert("str");
			auto it = arr.begin();

			std::string str = it[0];

			THEN("Should return element to which the pointer points")
			{
				REQUIRE(str == "str");
			}
		}

		WHEN("Try to change using access index operator")
		{
			CMyArray<std::string> arr;
			arr.Insert("123");
			auto it = arr.begin();

			it[0] = "str";

			THEN("String should be changed successfully")
			{
				REQUIRE(arr[0] == "str");
			}
		}

		WHEN("Use arithmetic with string")
		{
			WHEN("Use postfix increment")
			{
				CMyArray<std::string> arr;
				arr.Insert("str1");
				arr.Insert("str2");
				auto it = arr.begin();

				auto itResult = it++;

				THEN("Returned value should not be equals to incremented value")
				{
					REQUIRE(*it == "str2");
					REQUIRE(*itResult == "str1");
				}
			}

			WHEN("Use prefix increment")
			{
				CMyArray<std::string> arr;
				arr.Insert("str1");
				arr.Insert("str2");
				auto it = arr.begin();

				auto itResult = ++it;

				THEN("Returned value should not be equals to incremented value")
				{
					REQUIRE(*it == "str2");
					REQUIRE(*itResult == "str2");
				}
			}

			WHEN("Use postfix decrement")
			{
				CMyArray<std::string> arr;
				arr.Insert("str1");
				arr.Insert("str2");
				auto it = arr.begin();
				it++;

				auto itResult = it--;

				THEN("Returned value should not be equals to incremented value")
				{
					REQUIRE(*it == "str1");
					REQUIRE(*itResult == "str2");
				}
			}

			WHEN("Use prefix decrement")
			{
				CMyArray<std::string> arr;
				arr.Insert("str1");
				arr.Insert("str2");
				auto it = arr.begin();
				it++;

				auto itResult = --it;

				THEN("Returned value should not be equals to incremented value")
				{
					REQUIRE(*it == "str1");
					REQUIRE(*itResult == "str1");
				}
			}
		}

		WHEN("Use range-based version operator for with not empty array")
		{
			CMyArray<std::string> arr;
			arr.Insert("str1");
			arr.Insert("str2");
			std::string res = "";

			for (auto& str : arr)
			{
				res += str;
			}

			THEN("Result should contain all elements from array")
			{
				REQUIRE(res == "str1str2");
			}
		}

		WHEN("Use range-based version operator for with empty string")
		{
			CMyArray<std::string> arr;
			std::string res = "";

			for (auto& ch : arr)
			{
				res += ch;
			}

			THEN("Result should be empty")
			{
				REQUIRE(res == "");
			}
		}
	}
}

SCENARIO("User has ability to assign arrays with different elements types")
{
	WHEN("User assigns filled double array to filled int array")
	{
		CMyArray<double> doubleArr;
		doubleArr.Insert(3);
		CMyArray<int> intArr;
		intArr.Insert(2);

		intArr = doubleArr;

		THEN("Both arrays should contain double elements and should be filled")
		{
			REQUIRE(intArr.Count() == 1);
			REQUIRE(doubleArr.Count() == 1);
			REQUIRE(intArr[0] == 3);
			REQUIRE(doubleArr[0] == 3.0);
		}
	}

	WHEN("User assigns empty double array to empty int array")
	{
		CMyArray<double> doubleArr;
		CMyArray<int> intArr;

		intArr = doubleArr;

		THEN("Both arrays should be empty")
		{
			REQUIRE(intArr.Count() == 0);
			REQUIRE(doubleArr.Count() == 0);
		}
	}

	WHEN("User assigns empty double array to filled int array")
	{
		CMyArray<double> doubleArr;
		CMyArray<int> intArr;
		intArr.Insert(2);

		intArr = doubleArr;

		THEN("Both arrays should be empty")
		{
			REQUIRE(intArr.Count() == 0);
			REQUIRE(doubleArr.Count() == 0);
		}
	}

	WHEN("User assigns filled double array to empty int array")
	{
		CMyArray<double> doubleArr;
		doubleArr.Insert(3.0);
		CMyArray<int> intArr;

		intArr = doubleArr;

		THEN("Both arrays should be filled")
		{
			REQUIRE(intArr.Count() == 1);
			REQUIRE(doubleArr.Count() == 1);
			REQUIRE(intArr[0] == 3);
			REQUIRE(doubleArr[0] == 3.0);
		}
	}
}