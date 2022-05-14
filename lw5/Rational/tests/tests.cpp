#pragma once
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../CRational.h"

SCENARIO("User can create rational numbers")
{
	WHEN("Construct rational number without parameters")
	{
		CRational num = CRational();

		THEN("Numerator should be 0")
		{
			REQUIRE(num.GetNumerator() == 0);
		}

		THEN("Denominator should be 1")
		{
			REQUIRE(num.GetDenominator() == 1);
		}
	}

	WHEN("Construct rational number with 1 parameter")
	{
		CRational num = CRational(15);

		THEN("Numerator should be equals to parameter")
		{
			REQUIRE(num.GetNumerator() == 15);
		}

		THEN("Denominator should be 1")
		{
			REQUIRE(num.GetDenominator() == 1);
		}
	}

	WHEN("Construct rational number with not zero 2 parameters")
	{
		CRational num = CRational(15, 12);

		THEN("Number should be in normalized view")
		{
			REQUIRE(num.GetNumerator() == 5);
			REQUIRE(num.GetDenominator() == 4);
		}
	}

	WHEN("Construct rational number with 2 parameters with zero denominator")
	{
		CRational num = CRational(15, 0);

		THEN("Numerator should be 0")
		{
			REQUIRE(num.GetNumerator() == 0);
		}

		THEN("Denominator should be 1")
		{
			REQUIRE(num.GetDenominator() == 1);
		}
	}
}

SCENARIO("User has ability to get raional number in double view")
{
	WHEN("Creating rational number and get its double view")
	{
		CRational num = CRational(15, 12);

		THEN("Double should be returned")
		{
			REQUIRE(num.ToDouble() == 1.25);
		}
	}
}

SCENARIO("User has ability to execute unary operations on rational number")
{
	WHEN("Use unary plus on rational number")
	{
		CRational num = CRational();

		+num;

		THEN("Number should not be changed")
		{
			REQUIRE(num.GetNumerator() == 0);
			REQUIRE(num.GetDenominator() == 1);
		}
	}

	WHEN("User unary minus on rational number")
	{
		CRational num = CRational(1, 1);

		-num;

		THEN("Number should change his sign")
		{
			REQUIRE(num.GetNumerator() == -1);
			REQUIRE(num.GetDenominator() == 1);
		}
	}
}

SCENARIO("User has ability to execute binary operations on rational numbers")
{
	GIVEN("A binary plus")
	{
		WHEN("Add up two rational numbers")
		{
			CRational num1 = CRational(1, 1);
			CRational num2 = CRational(2, 2);
			CRational result = num1 + num2;

			THEN("Result should be result of its sum")
			{
				REQUIRE(result.ToDouble() == 2.0);
			}
		}

		WHEN("Add up rational number and int")
		{
			CRational num1 = CRational(1, 1);
			int num2 = 2;
			CRational result = num1 + num2;

			THEN("Result should be result of its sum")
			{
				REQUIRE(result.ToDouble() == 3.0);
			}
		}

		WHEN("Add up int and rational number")
		{
			int num1 = 2;
			CRational num2 = CRational(1, 1);
			CRational result = num1 + num2;

			THEN("Result should be result of its sum")
			{
				REQUIRE(result.ToDouble() == 3.0);
			}
		}

		WHEN("Add up two numbers with integer overflow")
		{
			CRational num1 = CRational(INT_MAX + 1, 2);
			CRational num2 = CRational(INT_MAX, 2);
			
			THEN("Adding up should return exception")
			{
				try {
					CRational result = num1 + num2;
					REQUIRE(false);
				}
				catch (const std::exception& e)
				{
					REQUIRE(!std::string(e.what()).empty());
				}
			}
		}
	}

	GIVEN("A binary minus")
	{
		WHEN("Subtracting two rational numbers")
		{
			CRational num1 = CRational(1, 1);
			CRational num2 = CRational(2, 2);
			CRational result = num2 - num1;

			THEN("Result should be result of its substraction")
			{
				REQUIRE(result.ToDouble() == 0.0);
			}
		}

		WHEN("Subtracting rational number and int")
		{
			CRational num1 = CRational(1, 1);
			int num2 = 2;
			CRational result = num1 - num2;

			THEN("Result should be result of its subtraction")
			{
				REQUIRE(result.ToDouble() == -1.0);
			}
		}

		WHEN("Subtracting int and rational number")
		{
			int num1 = 2;
			CRational num2 = CRational(1, 1);
			CRational result = num1 - num2;

			THEN("Result should be result of its subtraction")
			{
				REQUIRE(result.ToDouble() == 1.0);
			}
		}

		WHEN("Subtracting two numbers with integer overflow")
		{
			CRational num1 = CRational(-(INT_MAX + 1), 2);
			CRational num2 = CRational(INT_MAX, 2);

			THEN("Subtracting should return exception")
			{
				try
				{
					CRational result = num1 - num2;
					REQUIRE(false);
				}
				catch (const std::exception& e)
				{
					REQUIRE(!std::string(e.what()).empty());
				}
			}
		}
	}

	GIVEN("A binary *")
	{
		WHEN("Multiply two rational numbers")
		{
			CRational num1 = CRational(2, 5);
			CRational num2 = CRational(1, 2);

			CRational result = num1 * num2;

			THEN("Result should contain its multiplication")
			{
				REQUIRE(result.ToDouble() == 0.2);
			}
		}

		WHEN("Multiply rational number and int")
		{
			CRational num1 = CRational(2, 5);
			int num2 = 3;

			CRational result = num1 * num2;

			THEN("Result should containt its multiplication")
			{
				REQUIRE(result.ToDouble() == 1.2);
			}
		}

		WHEN("Multiply int and rational number")
		{
			int num1 = 3;
			CRational num2 = CRational(2, 5);

			CRational result = num1 * num2;

			THEN("Result should containt its multiplication")
			{
				REQUIRE(result.ToDouble() == 1.2);
			}
		}

		WHEN("Multiply two numbers with integer overflow")
		{
			CRational num1 = CRational(INT_MAX / 2, 1);
			CRational num2 = CRational(INT_MAX / 2, 1);

			THEN("Adding up should return exception")
			{
				try
				{
					CRational result = num1 * num2;
					REQUIRE(false);
				}
				catch (const std::exception& e)
				{
					REQUIRE(!std::string(e.what()).empty());
				}
			}
		}
	}

	GIVEN("A binary /")
	{
		WHEN("Divide two rational numbers")
		{
			CRational num1 = CRational(2, 5);
			CRational num2 = CRational(1, 2);

			CRational result = num1 / num2;

			THEN("Result should contain its division")
			{
				REQUIRE(result.ToDouble() == 0.8);
			}
		}

		WHEN("Divide rational number and int")
		{
			CRational num1 = CRational(2, 5);
			int num2 = 3;

			CRational result = num1 / num2;

			THEN("Result should containt its division")
			{
				REQUIRE(result.ToDouble() == static_cast<double>(2) / 15);
			}
		}

		WHEN("Divide int and rational number")
		{
			int num1 = 3;
			CRational num2 = CRational(2, 5);

			CRational result = num1 / num2;

			THEN("Result should containt its division")
			{
				REQUIRE(result.ToDouble() == 7.5);
			}
		}

		WHEN("Divide two numbers with integer overflow")
		{
			CRational num1 = CRational(INT_MAX / 2, 1);
			CRational num2 = CRational(1, INT_MAX / 2);

			THEN("Adding up should return exception")
			{
				try
				{
					CRational result = num1 / num2;
					REQUIRE(false);
				}
				catch (const std::exception& e)
				{
					REQUIRE(!std::string(e.what()).empty());
				}
			}
		}
	}
}

SCENARIO("User has ability to use operations with assignment")
{
	GIVEN("+=")
	{
		WHEN("Add up rational number and rational number")
		{
			CRational num1 = CRational(1, 2);
			CRational num2 = CRational(3);

			THEN("Left operand should contain its sum")
			{
				REQUIRE((num1 += num2).ToDouble() == 3.5);
				REQUIRE(num1.ToDouble() == 3.5);
			}
		}

		WHEN("Add up rational number and int")
		{
			CRational num1 = CRational(1, 2);
			int num2 = 3;

			THEN("Left operand should containt its sum")
			{
				REQUIRE((num1 += num2).ToDouble() == 3.5);
				REQUIRE(num1.ToDouble() == 3.5);
			}
		}

		WHEN("Add up rational numbers with overflow")
		{
			CRational num1 = CRational(INT_MAX, 2);
			CRational num2 = CRational(INT_MAX, 2);

			THEN("Adding up should return exception")
			{
				try
				{
					num1 += num2;
					REQUIRE(false);
				}
				catch (const std::exception& e)
				{
					REQUIRE(!std::string(e.what()).empty());
				}
			}
		}
	}

	GIVEN("-=")
	{
		WHEN("Subtracting rational number and rational number")
		{
			CRational num1 = CRational(1, 2);
			CRational num2 = CRational(3);

			THEN("Left operand should contain its substraction")
			{
				REQUIRE((num1 -= num2).ToDouble() == -2.5);
				REQUIRE(num1.ToDouble() == -2.5);
			}
		}

		WHEN("Subtracting rational number and int")
		{
			CRational num1 = CRational(1, 2);
			int num2 = 3;

			THEN("Left operand should containt its substraction")
			{
				REQUIRE((num1 -= num2).ToDouble() == -2.5);
				REQUIRE(num1.ToDouble() == -2.5);
			}
		}

		WHEN("Subtracting rational numbers with overflow")
		{
			CRational num1 = CRational(-INT_MAX, 2);
			CRational num2 = CRational(-INT_MAX, 2);

			THEN("Adding up should return exception")
			{
				try
				{
					num1 -= num2;
					REQUIRE(false);
				}
				catch (const std::exception& e)
				{
					REQUIRE(!std::string(e.what()).empty());
				}
			}
		}
	}

	GIVEN("*=")
	{
		WHEN("Multiplication rational number and rational number")
		{
			CRational num1 = CRational(1, 2);
			CRational num2 = CRational(3);

			THEN("Left operand should contain its multiplication")
			{
				REQUIRE((num1 *= num2).ToDouble() == 1.5);
				REQUIRE(num1.ToDouble() == 1.5);
			}
		}

		WHEN("Multiplication rational number and int")
		{
			CRational num1 = CRational(1, 2);
			int num2 = 3;

			THEN("Left operand should containt its multiplication")
			{
				REQUIRE((num1 *= num2).ToDouble() == 1.5);
				REQUIRE(num1.ToDouble() == 1.5);
			}
		}

		WHEN("Multiplication rational numbers with overflow")
		{
			CRational num1 = CRational(INT_MAX / 2, 1);
			CRational num2 = CRational(INT_MAX / 2, 1);

			THEN("Multiplication should return exception")
			{
				try
				{
					num1 *= num2;
					REQUIRE(false);
				}
				catch (const std::exception& e)
				{
					REQUIRE(!std::string(e.what()).empty());
				}
			}
		}
	}

	GIVEN("/=")
	{
		WHEN("Division rational number and rational number")
		{
			CRational num1 = CRational(1, 2);
			CRational num2 = CRational(3);

			THEN("Left operand should contain its division")
			{
				REQUIRE((num1 /= num2).ToDouble() == static_cast<double>(1) / 6);
				REQUIRE(num1.ToDouble() == static_cast<double>(1)/6);
			}
		}

		WHEN("Division rational number and int")
		{
			CRational num1 = CRational(1, 2);
			int num2 = 3;

			THEN("Left operand should containt its division")
			{
				REQUIRE((num1 /= num2).ToDouble() == static_cast<double>(1) / 6);
				REQUIRE(num1.ToDouble() == static_cast<double>(1) / 6);
			}
		}

		WHEN("Division rational numbers with overflow")
		{
			CRational num1 = CRational(INT_MAX / 2, 1);
			CRational num2 = CRational(1, INT_MAX / 2);

			THEN("Division should return exception")
			{
				try
				{
					num1 /= num2;
					REQUIRE(false);
				}
				catch (const std::exception& e)
				{
					REQUIRE(!std::string(e.what()).empty());
				}
			}
		}
	}
}

SCENARIO("User has ability to use comparison operations")
{
	GIVEN("== operation")
	{
		WHEN("Compare two equal rational numbers")
		{
			CRational num1 = CRational(1, 1);
			CRational num2 = CRational(1, 1);

			THEN("Result should be true")
			{
				REQUIRE(num1 == num2);
			}
		}

		WHEN("Compare two doesnt equal rational numbers")
		{
			CRational num1 = CRational(1, 1);
			CRational num2 = CRational(3, 1);

			THEN("Result should be false")
			{
				REQUIRE(!(num1 == num2));
			}
		}

		WHEN("Compare equal rational number and int")
		{
			CRational num1 = CRational(1, 1);
			int num2 = 1;

			THEN("Result should be true")
			{
				REQUIRE(num1 == num2);
			}
		}

		WHEN("Compare doesnt equal rational number and int")
		{
			CRational num1 = CRational(1, 1);
			int num2 = 3;

			THEN("Result should be false")
			{
				REQUIRE(!(num1 == num2));
			}
		}

		WHEN("Compare equal int and rational number")
		{
			int num1 = 1;
			CRational num2 = CRational(1, 1);

			THEN("Result should be true")
			{
				REQUIRE(num1 == num2);
			}
		}

		WHEN("Compare doesnt equal int and rational number")
		{
			int num1 = 1;
			CRational num2 = CRational(3, 1);

			THEN("Result should be false")
			{
				REQUIRE(!(num1 == num2));
			}
		}
	}

	GIVEN("!= operation")
	{
		WHEN("Compare two equal rational numbers")
		{
			CRational num1 = CRational(1, 1);
			CRational num2 = CRational(1, 1);

			THEN("Result should be false")
			{
				REQUIRE(!(num1 != num2));
			}
		}

		WHEN("Compare two doesnt equal rational numbers")
		{
			CRational num1 = CRational(1, 1);
			CRational num2 = CRational(3, 1);

			THEN("Result should be true")
			{
				REQUIRE(num1 != num2);
			}
		}

		WHEN("Compare equal rational number and int")
		{
			CRational num1 = CRational(1, 1);
			int num2 = 1;

			THEN("Result should be false")
			{
				REQUIRE(!(num1 != num2));
			}
		}

		WHEN("Compare doesnt equal rational number and int")
		{
			CRational num1 = CRational(1, 1);
			int num2 = 3;

			THEN("Result should be true")
			{
				REQUIRE(num1 != num2);
			}
		}

		WHEN("Compare equal int and rational number")
		{
			int num1 = 1;
			CRational num2 = CRational(1, 1);

			THEN("Result should be false")
			{
				REQUIRE(!(num1 != num2));
			}
		}

		WHEN("Compare doesnt equal int and rational number")
		{
			int num1 = 1;
			CRational num2 = CRational(3, 1);

			THEN("Result should be true")
			{
				REQUIRE(num1 != num2);
			}
		}
	}

	GIVEN("< operation")
	{
		WHEN("Compare two rational numbers, the first of which is greater or equals")
		{
			CRational num1 = CRational(1, 1);
			CRational num2 = CRational(1, 1);

			THEN("Result should be false")
			{
				REQUIRE(!(num1 < num2));
			}
		}

		WHEN("Compare two rational numbers, the first of which is smaller")
		{
			CRational num1 = CRational(1, 1);
			CRational num2 = CRational(3, 1);

			THEN("Result should be true")
			{
				REQUIRE(num1 < num2);
			}
		}

		WHEN("Compare rational number and int, where rational number is greater or equals")
		{
			CRational num1 = CRational(1, 1);
			int num2 = 1;

			THEN("Result should be false")
			{
				REQUIRE(!(num1 < num2));
			}
		}

		WHEN("Compare rational number and int, where rational number is smaller")
		{
			CRational num1 = CRational(1, 1);
			int num2 = 3;

			THEN("Result should be true")
			{
				REQUIRE(num1 < num2);
			}
		}

		WHEN("Compare int and rational number, where int is greater or equals")
		{
			int num1 = 1;
			CRational num2 = CRational(1, 1);

			THEN("Result should be false")
			{
				REQUIRE(!(num1 < num2));
			}
		}

		WHEN("Compare int and rational number, where int is smaller")
		{
			int num1 = 1;
			CRational num2 = CRational(3, 1);

			THEN("Result should be true")
			{
				REQUIRE(num1 < num2);
			}
		}
	}

	GIVEN("<= operation")
	{
		WHEN("Compare two rational numbers, the first of which is greater")
		{
			CRational num1 = CRational(2, 1);
			CRational num2 = CRational(1, 1);

			THEN("Result should be false")
			{
				REQUIRE(!(num1 <= num2));
			}
		}

		WHEN("Compare two rational numbers, the first of which is smaller or equals")
		{
			CRational num1 = CRational(1, 1);
			CRational num2 = CRational(3, 1);

			THEN("Result should be true")
			{
				REQUIRE(num1 <= num2);
			}
		}

		WHEN("Compare rational number and int, where rational number is greater")
		{
			CRational num1 = CRational(2, 1);
			int num2 = 1;

			THEN("Result should be false")
			{
				REQUIRE(!(num1 <= num2));
			}
		}

		WHEN("Compare rational number and int, where rational number is smaller or equals")
		{
			CRational num1 = CRational(1, 1);
			int num2 = 3;

			THEN("Result should be true")
			{
				REQUIRE(num1 <= num2);
			}
		}

		WHEN("Compare int and rational number, where int is greater")
		{
			int num1 = 2;
			CRational num2 = CRational(1, 1);

			THEN("Result should be false")
			{
				REQUIRE(!(num1 <= num2));
			}
		}

		WHEN("Compare int and rational number, where int is smaller or equals")
		{
			int num1 = 1;
			CRational num2 = CRational(3, 1);

			THEN("Result should be true")
			{
				REQUIRE(num1 <= num2);
			}
		}
	}

	GIVEN("> operation")
	{
		WHEN("Compare two rational numbers, the first of which is greater")
		{
			CRational num1 = CRational(2, 1);
			CRational num2 = CRational(1, 1);

			THEN("Result should be true")
			{
				REQUIRE(num1 > num2);
			}
		}

		WHEN("Compare two rational numbers, the first of which is smaller or equals")
		{
			CRational num1 = CRational(1, 1);
			CRational num2 = CRational(3, 1);

			THEN("Result should be false")
			{
				REQUIRE(!(num1 > num2));
			}
		}

		WHEN("Compare rational number and int, where rational number is greater")
		{
			CRational num1 = CRational(2, 1);
			int num2 = 1;

			THEN("Result should be true")
			{
				REQUIRE(num1 > num2);
			}
		}

		WHEN("Compare rational number and int, where rational number is smaller or equals")
		{
			CRational num1 = CRational(1, 1);
			int num2 = 3;

			THEN("Result should be false")
			{
				REQUIRE(!(num1 > num2));
			}
		}

		WHEN("Compare int and rational number, where int is greater")
		{
			int num1 = 2;
			CRational num2 = CRational(1, 1);

			THEN("Result should be true")
			{
				REQUIRE(num1 > num2);
			}
		}

		WHEN("Compare int and rational number, where int is smaller or equals")
		{
			int num1 = 1;
			CRational num2 = CRational(3, 1);

			THEN("Result should be false")
			{
				REQUIRE(!(num1 > num2));
			}
		}
	}

	GIVEN(">= operation")
	{
		WHEN("Compare two rational numbers, the first of which is greater or equals")
		{
			CRational num1 = CRational(1, 1);
			CRational num2 = CRational(1, 1);

			THEN("Result should be true")
			{
				REQUIRE(num1 >= num2);
			}
		}

		WHEN("Compare two rational numbers, the first of which is smaller")
		{
			CRational num1 = CRational(1, 1);
			CRational num2 = CRational(3, 1);

			THEN("Result should be false")
			{
				REQUIRE(!(num1 >= num2));
			}
		}

		WHEN("Compare rational number and int, where rational number is greater or equals")
		{
			CRational num1 = CRational(1, 1);
			int num2 = 1;

			THEN("Result should be true")
			{
				REQUIRE(num1 >= num2);
			}
		}

		WHEN("Compare rational number and int, where rational number is smaller")
		{
			CRational num1 = CRational(1, 1);
			int num2 = 3;

			THEN("Result should be false")
			{
				REQUIRE(!(num1 >= num2));
			}
		}

		WHEN("Compare int and rational number, where int is greater or equals")
		{
			int num1 = 1;
			CRational num2 = CRational(1, 1);

			THEN("Result should be true")
			{
				REQUIRE(num1 >= num2);
			}
		}

		WHEN("Compare int and rational number, where int is smaller")
		{
			int num1 = 1;
			CRational num2 = CRational(3, 1);

			THEN("Result should be false")
			{
				REQUIRE(!(num1 >= num2));
			}
		}
	}
}

SCENARIO("User has ability to print rational number")
{
	GIVEN("<< operation")
	{
		WHEN("Use << with rational number")
		{
			std::ostringstream os;
			CRational num = CRational(3, 1);

			os << num;

			THEN("Output should containt rational number's numerator, / and denominator")
			{
				REQUIRE(os.str() == "3/1");
			}
		}
	}

	GIVEN(">> operation")
	{
		WHEN("Use >> with string without /")
		{
			std::istringstream is("12");
			CRational num;

			THEN("Operation should return exception")
			{
				try
				{
					is >> num;
					REQUIRE(false);
				}
				catch (const std::exception& e)
				{
					REQUIRE(!(std::string(e.what()).empty()));
				}
			}
		}

		WHEN("Use >> with string with incorrect numerator")
		{
			std::istringstream is("a/2");
			CRational num;

			THEN("Operation should return exception")
			{
				try
				{
					is >> num;
					REQUIRE(false);
				}
				catch (const std::exception& e)
				{
					REQUIRE(!(std::string(e.what()).empty()));
				}
			}
		}

		WHEN("Use >> with string with incorrect denominator")
		{
			std::istringstream is("1/b");
			CRational num;

			THEN("Operation should return exception")
			{
				try
				{
					is >> num;
					REQUIRE(false);
				}
				catch (const std::exception& e)
				{
					REQUIRE(!(std::string(e.what()).empty()));
				}
			}
		}

		WHEN("Use >> with string with correct rational number")
		{
			std::istringstream is("1/2");
			CRational num;

			is >> num;

			THEN("Operation should return exception")
			{
				REQUIRE(num.GetNumerator() == 1);
				REQUIRE(num.GetDenominator() == 2);
			}
		}
	}
}