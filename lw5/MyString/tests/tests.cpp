#pragma once
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../CMyString.h"

// Main part of program

SCENARIO("User has ability to create strings")
{
	WHEN("User creates string without parameters")
	{
		CMyString str = CMyString();

		THEN("String data should be empty")
		{
			REQUIRE(strcmp(str.GetStringData(), "") == 0);
		}

		THEN("String's length should be 0")
		{
			REQUIRE(str.GetLength() == 0);
		}
	}

	WHEN("User create string with one parameter equals to ''")
	{
		CMyString str = CMyString("");

		THEN("String data should be equals to ''")
		{
			REQUIRE(strcmp(str.GetStringData(), "") == 0);
		}

		THEN("String's length should be 0")
		{
			REQUIRE(str.GetLength() == 0);
		}
	}

	WHEN("User creates string with one parameter equals to '123'")
	{
		CMyString str = CMyString("123");

		THEN("String data should be equals '123'")
		{
			REQUIRE(strcmp(str.GetStringData(), "123") == 0);
		}

		THEN("String's length should be 3")
		{
			REQUIRE(str.GetLength() == 3);
		}
	}

	WHEN("User creates string with two correct parameters('1234' and 3)")
	{
		CMyString str = CMyString("1234", 3);

		THEN("String data should be equals to '123'")
		{
			REQUIRE(strcmp(str.GetStringData(), "123") == 0);
		}

		THEN("String's length should be 3")
		{
			REQUIRE(str.GetLength() == 3);
		}
	}

	WHEN("User creates string with two parameters('', 0)")
	{
		CMyString str = CMyString("", 0);

		THEN("String's data should be ''")
		{
			REQUIRE(strcmp(str.GetStringData(), "") == 0);
		}

		THEN("String's length should be 0")
		{
			REQUIRE(str.GetLength() == 0);
		}
	}

	WHEN("User creates string from stl string '123'")
	{
		std::string stlString = "123";
		CMyString myString = CMyString(stlString);

		THEN("String's data should be '123'")
		{
			REQUIRE(strcmp(myString.GetStringData(), "123") == 0);
		}

		THEN("String's length should be 3")
		{
			REQUIRE(myString.GetLength() == 3);
		}
	}

	WHEN("User creates string from stl string ''")
	{
		std::string stlString = "";
		CMyString myString = CMyString(stlString);

		THEN("String's data should be ''")
		{
			REQUIRE(strcmp(myString.GetStringData(), "") == 0);
		}

		THEN("String's length should be 0")
		{
			REQUIRE(myString.GetLength() == 0);
		}
	}

	WHEN("User creates string through copying")
	{
		CMyString sourceString = CMyString("123");
		CMyString hostString = sourceString;

		THEN("String's data should be equals to copied data('123')")
		{
			REQUIRE(strcmp(hostString.GetStringData(), "123") == 0);
		}

		THEN("String's data should be equals to copied data's length(3)")
		{
			REQUIRE(hostString.GetLength() == 3);
		}
	}
}

SCENARIO("User has ability to get length of strings")
{
	WHEN("Creates string with no parametsrs")
	{
		CMyString str;

		THEN("Length of string should be 0")
		{
			REQUIRE(str.GetLength() == 0);
		}
	}

	WHEN("Creates string with one empty parameter")
	{
		CMyString str = CMyString("");

		THEN("Length of string should be 0")
		{
			REQUIRE(str.GetLength() == 0);
		}
	}

	WHEN("Creates string with one not empty parameter")
	{
		CMyString str = CMyString("123");

		THEN("Length of string should be equals to length of '123'(3)")
		{
			REQUIRE(str.GetLength() == 3);
		}
	}

	WHEN("Creates string with two parameters with empty string")
	{
		CMyString str = CMyString("0", 0);

		THEN("Length of string should be 0")
		{
			REQUIRE(str.GetLength() == 0);
		}
	}

	WHEN("Creates string with two parameters with not empty string")
	{
		CMyString str = CMyString("123", 2);

		THEN("Length of string should be equals to length parameter(2)")
		{
			REQUIRE(str.GetLength() == 2);
		}
	}

	WHEN("Creates string from stl empty string")
	{
		std::string stlString = "";
		CMyString myString(stlString);

		THEN("Length of string should be 0")
		{
			REQUIRE(myString.GetLength() == 0);
		}
	}

	WHEN("Creates string from stl not empty string")
	{
		std::string stlString = "123";
		CMyString myString(stlString);

		THEN("Length of string should be equals to stlString's length")
		{
			REQUIRE(myString.GetLength() == stlString.size());
		}
	}
}

SCENARIO("User has ability to get string's data")
{
	WHEN("Creates empty string")
	{
		CMyString str;

		THEN("String's data should be empty")
		{
			REQUIRE(strcmp(str.GetStringData(), "") == 0);
		}
	}

	WHEN("Creates not empty string")
	{
		CMyString str = "123";

		THEN("String's data should be equals to not empty string('123')")
		{
			REQUIRE(strcmp(str.GetStringData(), "123") == 0);
		}
	}
}

SCENARIO("User has ability to get substring's of string")
{
	WHEN("Creates substring from string correct")
	{
		CMyString sourceString("12345");
		CMyString substring = sourceString.SubString(0, 2);

		THEN("Substring should be correctly created")
		{
			REQUIRE(strcmp(substring.GetStringData(), "12") == 0);
			REQUIRE(substring.GetLength() == 2);
		}
	}

	WHEN("Creates substring from string correct")
	{
		CMyString sourceString("12345");
		CMyString substring = sourceString.SubString(1, 3);

		THEN("Substring should be correctly created")
		{
			REQUIRE(strcmp(substring.GetStringData(), "234") == 0);
			REQUIRE(substring.GetLength() == 3);
		}
	}

	WHEN("Creates substring with index, that is more than source string size")
	{
		CMyString sourceString("12345");

		THEN("Exception should be throwed")
		{
			REQUIRE_THROWS(sourceString.SubString(6, 3));
		}
	}

	WHEN("Creates substring with length, that is more than source string size")
	{
		CMyString sourceString("12345");

		THEN("Exception should be throwed")
		{
			REQUIRE_THROWS(sourceString.SubString(0, 12));
		}
	}

	WHEN("Creates substring, that goes beyond the bounds of the string")
	{
		CMyString sourceString("12345");

		THEN("Exception should be throwed")
		{
			REQUIRE_THROWS(sourceString.SubString(3, 4));
		}
	}

	WHEN("Creates substring with zero length")
	{
		CMyString sourceString("12345");
		CMyString substring = sourceString.SubString(0, 0);

		THEN("Substring should be empty")
		{
			REQUIRE(strcmp(substring.GetStringData(), "") == 0);
			REQUIRE(substring.GetLength() == 0);
		}
	}
}

SCENARIO("User has ability to clear strings")
{
	WHEN("Creates empty string and tries to clear it")
	{
		CMyString str;

		str.Clear();

		THEN("String should be empty")
		{
			REQUIRE(strcmp(str.GetStringData(), "") == 0);
			REQUIRE(str.GetLength() == 0);
		}
	}

	WHEN("Creates not empty string and tries to clear it")
	{
		CMyString str("123");

		str.Clear();

		THEN("String should be empty")
		{
			REQUIRE(strcmp(str.GetStringData(), "") == 0);
			REQUIRE(str.GetLength() == 0);
		}
	}
}

SCENARIO("User has ability to use assignment operations on string")
{
	WHEN("Use assignment operation on string")
	{
		CMyString str1;
		CMyString str2("123");

		THEN("Left string should be equals to right string")
		{
			str2 = str1;

			REQUIRE(strcmp(str2.GetStringData(), "") == 0);
			REQUIRE(str2.GetLength() == 0);
		}

		THEN("Assignment operation should return left operand")
		{
			CMyString str3 = (str2 = str1);

			REQUIRE(strcmp(str3.GetStringData(), "") == 0);
			REQUIRE(str3.GetLength() == 0);
		}
	}

	WHEN("Use assignment operation on string itself")
	{
		CMyString str1("i like to draw");

		str1 = str1;

		THEN("String should not be changed")
		{
			REQUIRE(strcmp(str1.GetStringData(), "i like to draw") == 0);
		}
	}

	WHEN("Use assignment with addition operation")
	{
		WHEN("Use addition operation on strings with one empty string")
		{
			CMyString str1;
			CMyString str2("123");

			str1 += str2;

			THEN("Result should contain not empty string")
			{
				REQUIRE(strcmp(str1.GetStringData(), str2.GetStringData()) == 0);
				REQUIRE(str1.GetLength() == str2.GetLength());
			}
		}

		WHEN("Use addition operation on strings with two empty strings")
		{
			CMyString str1;
			CMyString str2;

			str1 += str2;
			str2 += str1;

			THEN("Result should contain empty string")
			{
				REQUIRE(strcmp(str1.GetStringData(), "") == 0);
				REQUIRE(str1.GetLength() == 0);
				REQUIRE(strcmp(str2.GetStringData(), "") == 0);
				REQUIRE(str2.GetLength() == 0);
			}
		}

		WHEN("Use addition operation on 2 not empty strings")
		{
			CMyString str1("12");
			CMyString str2("34");

			str1 += str2;

			THEN("Result should contain their contatenation")
			{
				REQUIRE(strcmp(str1.GetStringData(), "1234") == 0);
				REQUIRE(str1.GetLength() == 4);
			}
		}

		WHEN("Use addition operation on 2 not empty strings")
		{
			CMyString str1("12");
			CMyString str2("34");

			CMyString result = str1 += str2;

			THEN("+= operation should return str1 result")
			{
				REQUIRE(strcmp(result.GetStringData(), "1234") == 0);
				REQUIRE(result.GetLength() == 4);
			}
		}

		WHEN("Use addition operation on result of addition operation as right operand")
		{
			CMyString str1("12");
			CMyString str2("34");
			CMyString str3("56");

			str1 += (str2 += str3);

			THEN("+= operation should return concatenation result")
			{
				REQUIRE(strcmp(str2.GetStringData(), "3456") == 0);
				REQUIRE(strcmp(str1.GetStringData(), "123456") == 0);
				REQUIRE(strcmp(str3.GetStringData(), "56") == 0);
			}
		}

		WHEN("Use addition operation on result of addition operation as left operand")
		{
			CMyString str1("12");
			CMyString str2("34");
			CMyString str3("56");

			(str1 += str2) += str3;

			THEN("+= operation should return concatenation result")
			{
				REQUIRE(strcmp(str2.GetStringData(), "34") == 0);
				REQUIRE(strcmp(str1.GetStringData(), "123456") == 0);
				REQUIRE(strcmp(str3.GetStringData(), "56") == 0);
			}
		}
	}
}

SCENARIO("User can contatenate strings")
{
	WHEN("Use addition operation on strings with one empty string")
	{
		CMyString str1;
		CMyString str2("123");

		CMyString result1 = str1 + str2;
		CMyString result2 = str2 + str1;

		THEN("Result should contain not empty string")
		{
			REQUIRE(strcmp(result1.GetStringData(), str2.GetStringData()) == 0);
			REQUIRE(result1.GetLength() == str2.GetLength());
			REQUIRE(strcmp(result2.GetStringData(), str2.GetStringData()) == 0);
			REQUIRE(result2.GetLength() == str2.GetLength());
		}
	}

	WHEN("Use addition operation on strings with two empty strings")
	{
		CMyString str1;
		CMyString str2;

		CMyString result = str1 + str2;

		THEN("Result should contain empty string")
		{
			REQUIRE(strcmp(result.GetStringData(), "") == 0);
			REQUIRE(result.GetLength() == 0);
		}
	}

	WHEN("Use addition operation on 2 not empty strings")
	{
		CMyString str1("12");
		CMyString str2("34");

		CMyString result = str1 + str2;

		THEN("Result should contain their contatenation")
		{
			REQUIRE(strcmp(result.GetStringData(), "1234") == 0);
			REQUIRE(result.GetLength() == 4);
		}
	}
}

SCENARIO("User can compare strings")
{
	WHEN("Use == operation")
	{
		WHEN("Two strings, which one of them with zero symbol")
		{
			CMyString str1("123\0a", 5);
			CMyString str2("123");

			THEN("Result should be false")
			{
				REQUIRE(str1 != str2);
			}
		}

		WHEN("Two strings are not equal")
		{
			CMyString str1("123");
			CMyString str2("12");

			THEN("Result should be false")
			{
				REQUIRE(!(str1 == str2));
			}
		}

		WHEN("Two strings are empty")
		{
			CMyString str1;
			CMyString str2;

			THEN("Result should be true")
			{
				REQUIRE(str1 == str2);
			}
		}
	}

	WHEN("Use != operation")
	{
		WHEN("Two strings, which one of them with zero symbol")
		{
			CMyString str1("123\0a", 5);
			CMyString str2("123");

			THEN("Result should be true")
			{
				REQUIRE(str1 != str2);
			}
		}

		WHEN("Two strings are equal")
		{
			CMyString str1("123");
			CMyString str2("123");

			THEN("Result should be false")
			{
				REQUIRE(!(str1 != str2));
			}
		}

		WHEN("Two strings are not equal")
		{
			CMyString str1("123");
			CMyString str2("12");

			THEN("Result should be true")
			{
				REQUIRE(str1 != str2);
			}
		}

		WHEN("Two strings are empty")
		{
			CMyString str1;
			CMyString str2;

			THEN("Result should be false")
			{
				REQUIRE(!(str1 != str2));
			}
		}
	}

	WHEN("Use < operation")
	{
		WHEN("Two strings, which one of them with zero symbol")
		{
			CMyString str1("123\0a", 5);
			CMyString str2("123");

			THEN("Result should be false")
			{
				REQUIRE(!(str1 < str2));
			}
		}

		WHEN("Left operand is less than right")
		{
			CMyString str1("0");
			CMyString str2("1");

			THEN("Result should be true")
			{
				REQUIRE(str1 < str2);
			}
		}

		WHEN("Left operand is equals to rights")
		{
			CMyString str1("12");
			CMyString str2("12");

			THEN("Result should be false")
			{
				REQUIRE(!(str1 < str2));
			}
		}

		WHEN("Left operand is more than right")
		{
			CMyString str1("2");
			CMyString str2("1");

			THEN("Result should be false")
			{
				REQUIRE(!(str1 < str2));
			}
		}

		WHEN("Two operands are empty strings")
		{
			CMyString str1;
			CMyString str2;

			THEN("Result should be false")
			{
				REQUIRE(!(str1 < str2));
			}
		}

		WHEN("Left operand is empty string, right operand is not empty string")
		{
			CMyString str1;
			CMyString str2("23");

			THEN("Result should be true")
			{
				REQUIRE(str1 < str2);
			}
		}

		WHEN("Left operand is not empty string, right operand is empty string")
		{
			CMyString str1("23");
			CMyString str2;

			THEN("Result should be false")
			{
				REQUIRE(!(str1 < str2));
			}
		}
	}

	WHEN("Use <= operation")
	{
		WHEN("Two strings, which one of them with zero symbol")
		{
			CMyString str1("123\0a", 5);
			CMyString str2("123");

			THEN("Result should be false")
			{
				REQUIRE(!(str1 <= str2));
			}
		}

		WHEN("Left operand is less than right")
		{
			CMyString str1("0");
			CMyString str2("1");

			THEN("Result should be true")
			{
				REQUIRE(str1 <= str2);
			}
		}

		WHEN("Left operand is equals to rights")
		{
			CMyString str1("12");
			CMyString str2("12");

			THEN("Result should be true")
			{
				REQUIRE(str1 <= str2);
			}
		}

		WHEN("Left operand is more than right")
		{
			CMyString str1("2");
			CMyString str2("1");

			THEN("Result should be false")
			{
				REQUIRE(!(str1 <= str2));
			}
		}

		WHEN("Two operands are empty strings")
		{
			CMyString str1;
			CMyString str2;

			THEN("Result should be true")
			{
				REQUIRE(str1 <= str2);
			}
		}

		WHEN("Left operand is empty string, right operand is not empty string")
		{
			CMyString str1;
			CMyString str2("23");

			THEN("Result should be true")
			{
				REQUIRE(str1 <= str2);
			}
		}

		WHEN("Left operand is not empty string, right operand is empty string")
		{
			CMyString str1("23");
			CMyString str2;

			THEN("Result should be false")
			{
				REQUIRE(!(str1 <= str2));
			}
		}
	}

	WHEN("Use > operation")
	{
		WHEN("Two strings, which one of them with zero symbol")
		{
			CMyString str1("123\0a", 5);
			CMyString str2("123");

			THEN("Result should be true")
			{
				REQUIRE(str1 > str2);
			}
		}

		WHEN("Left operand is less than right")
		{
			CMyString str1("0");
			CMyString str2("1");

			THEN("Result should be false")
			{
				REQUIRE(!(str1 > str2));
			}
		}

		WHEN("Left operand is equals to rights")
		{
			CMyString str1("12");
			CMyString str2("12");

			THEN("Result should be false")
			{
				REQUIRE(!(str1 > str2));
			}
		}

		WHEN("Left operand is more than right")
		{
			CMyString str1("2");
			CMyString str2("1");

			THEN("Result should be true")
			{
				REQUIRE(str1 > str2);
			}
		}

		WHEN("Two operands are empty strings")
		{
			CMyString str1;
			CMyString str2;

			THEN("Result should be false")
			{
				REQUIRE(!(str1 > str2));
			}
		}

		WHEN("Left operand is empty string, right operand is not empty string")
		{
			CMyString str1;
			CMyString str2("23");

			THEN("Result should be false")
			{
				REQUIRE(!(str1 > str2));
			}
		}

		WHEN("Left operand is not empty string, right operand is empty string")
		{
			CMyString str1("23");
			CMyString str2;

			THEN("Result should be true")
			{
				REQUIRE(str1 > str2);
			}
		}
	}

	WHEN("Use >= operation")
	{
		WHEN("Two strings, which one of them with zero symbol")
		{
			CMyString str1("123\0a", 5);
			CMyString str2("123");

			THEN("Result should be true")
			{
				REQUIRE(str1 >= str2);
			}
		}

		WHEN("Left operand is less than right")
		{
			CMyString str1("0");
			CMyString str2("1");

			THEN("Result should be false")
			{
				REQUIRE(!(str1 >= str2));
			}
		}

		WHEN("Left operand is equals to rights")
		{
			CMyString str1("12");
			CMyString str2("12");

			THEN("Result should be true")
			{
				REQUIRE(str1 >= str2);
			}
		}

		WHEN("Left operand is more than right")
		{
			CMyString str1("2");
			CMyString str2("1");

			THEN("Result should be true")
			{
				REQUIRE(str1 >= str2);
			}
		}

		WHEN("Two operands are empty strings")
		{
			CMyString str1;
			CMyString str2;

			THEN("Result should be true")
			{
				REQUIRE(str1 >= str2);
			}
		}

		WHEN("Left operand is empty string, right operand is not empty string")
		{
			CMyString str1;
			CMyString str2("23");

			THEN("Result should be false")
			{
				REQUIRE(!(str1 >= str2));
			}
		}

		WHEN("Left operand is not empty string, right operand is empty string")
		{
			CMyString str1("23");
			CMyString str2;

			THEN("Result should be true")
			{
				REQUIRE(str1 >= str2);
			}
		}
	}
}

SCENARIO("User can use operation access by index")
{
	WHEN("Use [] operation")
	{
		WHEN("Taking index of empty string")
		{
			CMyString str;
			THEN("It should lead to exception")
			{
				REQUIRE_THROWS(str[1]);
			}
		}

		WHEN("Taking index, that is more than string length")
		{
			CMyString str("123");

			THEN("It should lead to exception")
			{
				REQUIRE_THROWS(str[4]);
			}
		}

		WHEN("Taking possible index of not empty string")
		{
			CMyString str("123");

			THEN("It should return symbol under this index")
			{
				REQUIRE(str[0] == '1');
			}
		}

		WHEN("Taking possible index of not empty string and tries to rewrite it")
		{
			CMyString str("123");

			str[0] = '0';

			THEN("Symbol should be rewritten")
			{
				REQUIRE(str[0] == '0');
			}
		}
	}
}

SCENARIO("User can use streams to print and get strings")
{
	WHEN("Use << operation with not empty string")
	{
		std::ostringstream oss;
		CMyString str("123");

		oss << str;

		THEN("String should be added to stream")
		{
			REQUIRE(oss.str() == "123");
		}
	}

	WHEN("Use << operation with empty string")
	{
		std::ostringstream oss;
		CMyString str("");

		oss << str;

		THEN("String should be added to stream")
		{
			REQUIRE(oss.str() == "");
		}
	}

	WHEN("Use >> operation with not empty string")
	{
		std::istringstream iss("123");
		CMyString str;

		iss >> str;

		THEN("String variable should contain this value")
		{

			REQUIRE(strcmp(str.GetStringData(), "123") == 0);
		}
	}

	WHEN("Use >> operation with not empty string with space")
	{
		std::istringstream iss("123 a123");
		CMyString str;

		iss >> str;

		THEN("String variable should contain this value")
		{

			REQUIRE(memcmp(str.GetStringData(), "123", 3) == 0);
		}
	}

	WHEN("Use >> operation with empty string")
	{
		std::istringstream iss("");
		CMyString str;

		iss >> str;

		THEN("String variable should contain this value")
		{
			REQUIRE(strcmp(str.GetStringData(), "") == 0);
		}
	}
}

SCENARIO("User can use move constructor and move assignment operator")
{
	GIVEN("Move constructor")
	{
		WHEN("Move exactly from constructor")
		{
			CMyString str(std::move(CMyString("i like programming")));

			THEN("String should contain string from moved string")
			{
				REQUIRE(strcmp(str.GetStringData(), "i like programming") == 0);
			}
		}

		WHEN("Move from variable")
		{
			CMyString sourceStr("i love JS!");
			CMyString receiveStr(std::move(sourceStr));

			THEN("New str should contain value and source string should contain no value")
			{
				REQUIRE(strcmp(receiveStr.GetStringData(), "i love JS!") == 0);
				REQUIRE(strcmp(sourceStr.GetStringData(), "") == 0);
			}
		}

		WHEN("Move empty string")
		{
			CMyString str(std::move(""));

			THEN("Str should contain empty string")
			{
				REQUIRE(strcmp(str.GetStringData(), "") == 0);
			}
		}
	}

	GIVEN("Move assignment operation")
	{
		WHEN("Move from variable")
		{
			CMyString sourceStr("i love JS!");
			CMyString receiveStr("js is shit");

			receiveStr = std::move(sourceStr);

			THEN("New str should contain value and source string should contain no value")
			{
				REQUIRE(strcmp(receiveStr.GetStringData(), "i love JS!") == 0);
				REQUIRE(strcmp(sourceStr.GetStringData(), "") == 0);
			}
		}

		WHEN("Move empty string")
		{
			CMyString sourceStr("");
			CMyString receiveStr("js is shit");

			receiveStr = std::move(sourceStr);

			THEN("New str should contain no value and source string should contain no value")
			{
				REQUIRE(strcmp(sourceStr.GetStringData(), "") == 0);
				REQUIRE(strcmp(receiveStr.GetStringData(), "") == 0);
			}
		}
	}
}

// Iterators

SCENARIO("User can use iterators on string")
{
	GIVEN("Inconstant iterator")
	{
		WHEN("Use begin() ... end() on string")
		{
			auto it = CMyString("i like JS");
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
			auto it = CMyString("");
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
			auto it = CMyString("i like JS");
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
			auto it = CMyString("");
			std::string result = "";

			std::for_each(it.rbegin(), it.rend(), [&](auto ch) {
				result += ch;
			});

			THEN("Iterator should pass through all string's characters")
			{
				REQUIRE(result == "");
			}
		}

		WHEN("Try to change character, that pointed by iterator")
		{
			CMyString str = "123";
			auto it = str.begin();

			*it = '0';

			THEN("Characted should be changed")
			{
				REQUIRE(strcmp(str.GetStringData(), "023") == 0);
			} 
		}

		WHEN("Try to use access index operator")
		{
			CMyString str = "123";
			auto it = str.begin();

			char ch = it[0];

			THEN("Should return char to which the pointer points")
			{
				REQUIRE(ch == '1');
			}
		}

		WHEN("Try to change using access index operator")
		{
			CMyString str = "123";
			auto it = str.begin();

			it[0] = '0';

			THEN("String should be changed successfully")
			{
				REQUIRE(strcmp(str.GetStringData(), "023") == 0);
			}
		}

		WHEN("Use arithmetic with string")
		{
			WHEN("Use postfix increment")
			{
				CMyString str = CMyString("123");
				auto it = str.begin();

				auto itResult = it++;

				THEN("Returned value should not be equals to incremented value")
				{
					REQUIRE(*it == '2');
					REQUIRE(*itResult == '1');
				}
			}

			WHEN("Use prefix increment")
			{
				CMyString str = CMyString("123");
				auto it = str.begin();

				auto itResult = ++it;

				THEN("Returned value should not be equals to incremented value")
				{
					REQUIRE(*it == '2');
					REQUIRE(*itResult == '2');
				}
			}

			WHEN("Use postfix decrement")
			{
				CMyString str = CMyString("123");
				auto it = str.begin();
				it++;

				auto itResult = it--;

				THEN("Returned value should not be equals to incremented value")
				{
					REQUIRE(*it == '1');
					REQUIRE(*itResult == '2');
				}
			}

			WHEN("Use prefix decrement")
			{
				CMyString str = CMyString("123");
				auto it = str.begin();
				it++;

				auto itResult = --it;

				THEN("Returned value should not be equals to incremented value")
				{
					REQUIRE(*it == '1');
					REQUIRE(*itResult == '1');
				}
			}

			WHEN("Try to add up num to iterator")
			{
				CMyString str = "123";
				auto it = str.begin();

				auto resIt = it + 2;

				THEN("Result iterator should points to character and start iterator should not be changed")
				{
					REQUIRE(*it == '1');
					REQUIRE(*resIt == '3');
				}
			}

			WHEN("Try to add up iterator to num")
			{
				CMyString str = "123";
				auto it = str.begin();

				auto resIt = 2 + it;

				THEN("Result iterator should points to character and start iterator should not be changed")
				{
					REQUIRE(*it == '1');
					REQUIRE(*resIt == '3');
				}
			}

			WHEN("Try to substract two iterators")
			{
				CMyString str = "123";
				auto it = str.begin();

				auto resIt = 2 + it;

				THEN("Subtraction should equals to 2")
				{
					REQUIRE(resIt - it == 2);
					REQUIRE(it - resIt == -2);
				}
			}
		}

		WHEN("Use comparision with string")
		{
			WHEN("Use == operation on equals iterators")
			{
				CMyString str("i love JS");

				auto it1 = str.begin();
				auto it2 = str.begin();

				THEN("Result should be true")
				{
					REQUIRE(it1 == it2);
				}
			}

			WHEN("Use == operation on iterators, that points to equal char")
			{
				CMyString str("oogway master");

				auto it1 = str.begin();
				it1++;
				auto it2 = str.begin();
				it2++;

				THEN("Result should be true")
				{
					REQUIRE(it1 == it2);
				}
			}

			WHEN("Use == operation on unequal iterators")
			{
				CMyString str("i love JS");

				auto it1 = str.begin();
				it1++;
				auto it2 = str.begin();

				THEN("Result should be false")
				{
					REQUIRE(!(it1 == it2));
				}
			}
			WHEN("Use != operation on equal iterators")
			{
				CMyString str("i love JS");

				auto it1 = str.begin();
				auto it2 = str.begin();

				THEN("Result should be false")
				{
					REQUIRE(!(it1 != it2));
				}
			}

			WHEN("Use != operation on unequal iterators")
			{
				CMyString str("i love JS");

				auto it1 = str.begin();
				it1++;
				auto it2 = str.begin();

				THEN("Result should be true")
				{
					REQUIRE(it1 != it2);
				}
			}
			WHEN("Use < operation with left operand less than right")
			{
				CMyString str("abc");

				auto it1 = str.begin();
				auto it2 = str.end();

				THEN("Result should be true")
				{
					REQUIRE(it1 < it2);
				}
			}
			WHEN("Use < operation with left operand greater than right")
			{
				CMyString str("abc");

				auto it1 = str.end();
				auto it2 = str.begin();

				THEN("Result should be false")
				{
					REQUIRE(!(it1 < it2));
				}
			}
			WHEN("Use < operation with left operand equals to right")
			{
				CMyString str("aba");

				auto it1 = str.end();
				auto it2 = str.begin();

				THEN("Result should be false")
				{
					REQUIRE(!(it1 < it2));
				}
			}
			WHEN("Use <= operation with left operand less than right")
			{
				CMyString str("abc");

				auto it1 = str.begin();
				auto it2 = str.end();

				THEN("Result should be true")
				{
					REQUIRE(it1 <= it2);
				}
			}
			WHEN("Use <= operation with left operand greater than right")
			{
				CMyString str("abc");

				auto it1 = str.end();
				auto it2 = str.begin();

				THEN("Result should be false")
				{
					REQUIRE(!(it1 <= it2));
				}
			}
			WHEN("Use <= operation with left operand equals to right")
			{
				CMyString str("aba");

				auto it1 = str.begin();
				auto it2 = str.begin();

				THEN("Result should be true")
				{
					REQUIRE(it1 <= it2);
				}
			}
			WHEN("Use > operation with left operand less than right")
			{
				CMyString str("abc");

				auto it1 = str.begin();
				auto it2 = str.end();

				THEN("Result should be false")
				{
					REQUIRE(!(it1 > it2));
				}
			}
			WHEN("Use > operation with left operand greater than right")
			{
				CMyString str("abc");

				auto it1 = str.end();
				auto it2 = str.begin();

				THEN("Result should be true")
				{
					REQUIRE(it1 > it2);
				}
			}
			WHEN("Use > operation with left operand equals to right")
			{
				CMyString str("aba");

				auto it1 = str.begin();
				auto it2 = str.begin();

				THEN("Result should be false")
				{
					REQUIRE(!(it1 > it2));
				}
			}
			WHEN("Use >= operation with left operand less than right")
			{
				CMyString str("abc");

				auto it1 = str.begin();
				auto it2 = str.end();

				THEN("Result should be false")
				{
					REQUIRE(!(it1 >= it2));
				}
			}
			WHEN("Use >= operation with left operand greater than right")
			{
				CMyString str("abc");

				auto it1 = str.end();
				auto it2 = str.begin();

				THEN("Result should be true")
				{
					REQUIRE(it1 >= it2);
				}
			}
			WHEN("Use >= operation with left operand equals to right")
			{
				CMyString str("aba");

				auto it1 = str.begin();
				auto it2 = str.begin();

				THEN("Result should be true")
				{
					REQUIRE(it1 >= it2);
				}
			}
		}

		WHEN("Use range-based version operator for with not empty string")
		{
			CMyString str("123");
			std::string res = "";

			for (auto& ch : str)
			{
				res += ch;
			}

			THEN("Result should contain all characters from string")
			{
				REQUIRE(res == "123");
			}
		}

		WHEN("Use range-based version operator for with empty string")
		{
			CMyString str("");
			std::string res = "";

			for (auto& ch : str)
			{
				res += ch;
			}

			THEN("Result should contain all characters from string")
			{
				REQUIRE(res == "");
			}
		}
	}

	GIVEN("Constant iterator")
	{
		WHEN("Use cbegin() ... cend() on string")
		{
			auto it = CMyString("i like JS");
			std::string result = "";

			std::for_each(it.cbegin(), it.cend(), [&](auto ch) {
				result += ch;
			});

			THEN("Iterator should pass through all string's characters")
			{
				REQUIRE(result == "i like JS");
			}
		}

		WHEN("Use cbegin() ... cend() on empty string")
		{
			auto it = CMyString("");
			std::string result = "";

			std::for_each(it.cbegin(), it.cend(), [&](auto ch) {
				result += ch;
			});

			THEN("Iterator should pass through all string's characters")
			{
				REQUIRE(result == "");
			}
		}

		WHEN("Use crbegin() ... crend() on string")
		{
			auto it = CMyString("i like JS");
			std::string result = "";

			std::for_each(it.crbegin(), it.crend(), [&](auto ch) {
				result += ch;
			});

			THEN("Iterator should pass through all string's characters")
			{
				REQUIRE(result == "SJ ekil i");
			}
		}

		WHEN("Use crbegin() ... crend() on empty string")
		{
			auto it = CMyString("");
			std::string result = "";

			std::for_each(it.crbegin(), it.crend(), [&](auto ch) {
				result += ch;
			});

			THEN("Iterator should pass through all string's characters")
			{
				REQUIRE(result == "");
			}
		}

		WHEN("Try to use access index operator")
		{
			CMyString str = "123";
			auto it = str.begin();

			char ch = it[0];

			THEN("Should return char to which the pointer points")
			{
				REQUIRE(ch == '1');
			}
		}
	}
}