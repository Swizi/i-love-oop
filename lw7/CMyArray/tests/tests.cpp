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
		// Поправить
		//CMyArray<double> myArray1;
		//myArray1.Insert(3);
		//CMyArray<double> myArray2 = myArray1;

		//THEN("Array should be equal")
		//{
		//	REQUIRE(myArray1.Count() == 1);
		//	REQUIRE(myArray2.Count() == 1);
		//	REQUIRE(myArray1[0] == 3.0);
		//	REQUIRE(myArray2[0] == 3.0);
		//}
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
