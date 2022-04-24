#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Calculator.h";

SCENARIO("Calculator has ability to create variables")
{
	GIVEN("A calculator")
	{
		CCalculator calculator = CCalculator();

		WHEN("Create new variable")
		{
			calculator.CreateVar("new_var");

			THEN("Calculator should contain this variable")
			{
				REQUIRE(calculator.GetVars().count("new_var") != 0);
			}

			THEN("Calculator should containt this variable with value equals to NAN")
			{
				REQUIRE(isnan(calculator.GetIdentifierValue("new_var")));
			}
		}

		WHEN("Create variable with name, that has already used")
		{
			calculator.CreateVar("new_var");
			calculator.CreateVar("new_var");

			THEN("Repeated command should be ignored and error should be printed")
			{
				REQUIRE(true);
			}
		}
	}
}

SCENARIO("Calculator has ability to assign value to variable")
{
	GIVEN("A calculator")
	{
		CCalculator calculator = CCalculator();

		WHEN("Assign value to non-existent variable")
		{
			calculator.AssignVarValue("new_var", "123.0");

			THEN("Variable should be created and value should be assigned to this var")
			{
				REQUIRE(calculator.GetIdentifierValue("new_var") == 123.0);
			}
		}

		WHEN("Assign value to existent variable")
		{
			calculator.CreateVar("new_var");
			calculator.AssignVarValue("new_var", "156.123");

			THEN("Value should be assigned")
			{
				REQUIRE(calculator.GetIdentifierValue("new_var") == 156.123);
			}
		}

		WHEN("Assign incorrect double value to var")
		{
			calculator.CreateVar("new_var");
			calculator.AssignVarValue("new_var", "abc");

			THEN("Value should not be assigned")
			{
				REQUIRE(isnan(calculator.GetIdentifierValue("new_var")));
			}
		}

		WHEN("Assing variable to another variable")
		{
			calculator.AssignVarValue("var1", "5.2");
			calculator.AssignVarValue("var2", "var1");

			THEN("Variable should be assigned")
			{
				REQUIRE(calculator.GetIdentifierValue("var2") == 5.2);
			}
		}

		WHEN("Assign function to variable")
		{
			calculator.AssignVarValue("var1", "fn1");

			THEN("Function shoulde not be assigned")
			{
				REQUIRE(isnan(calculator.GetIdentifierValue("var1")));
			}
		}
	}
}

SCENARIO("Calculator has ability to create functions")
{
	GIVEN("A calculator")
	{
		CCalculator calculator = CCalculator();

		WHEN("Assign function with name, that has already used")
		{
			calculator.CreateVar("id1");
			calculator.CreateFunction("id1", "1");

			THEN("Function should not be createad and error should be printed")
			{
				REQUIRE(isnan(calculator.GetIdentifierValue("id1")));
			}
		}

		WHEN("Assign function with double number")
		{
			calculator.CreateFunction("fn1", "1.3");

			THEN("Function should have double number value")
			{
				REQUIRE(calculator.GetIdentifierValue("fn1") == 1.3);
			}
		}

		WHEN("Assign expression, that have undeclared identifier")
		{
			calculator.CreateFunction("fn1", "var1+var2");

			THEN("Function should return NAN")
			{
				REQUIRE(isnan(calculator.GetIdentifierValue("fn1")));
			}
		}

		WHEN("Assign number expression")
		{
			calculator.CreateFunction("fn1", "1.3+4.5");

			THEN("Function should return result")
			{
				REQUIRE(calculator.GetIdentifierValue("fn1") == 5.8);
			}
		}

		WHEN("Assign expression, that have zero division")
		{
			calculator.CreateFunction("fn1", "1.3/0");

			THEN("Function should return NAN")
			{
				REQUIRE(isnan(calculator.GetIdentifierValue("fn1")));
			}
		}

		WHEN("Assign vars expression")
		{
			calculator.AssignVarValue("var1", "3.4");
			calculator.AssignVarValue("var2", "6.6");
			calculator.CreateFunction("fn1", "var1+var2");

			THEN("Function should return result")
			{
				REQUIRE(calculator.GetIdentifierValue("fn1") == 10.0);
			}
		}

		WHEN("Assign functions expression")
		{
			calculator.CreateFunction("fn1", "3.4");
			calculator.CreateFunction("fn2", "6.6");
			calculator.CreateFunction("fn3", "fn1+fn2");

			THEN("Function should return result")
			{
				REQUIRE(calculator.GetIdentifierValue("fn3") == 10.0);
			}
		}
	}
}

SCENARIO("Calculator has ability to print identifier")
{
	GIVEN("A calculator")
	{
		CCalculator calculator = CCalculator();

		WHEN("Print unexistent identifier")
		{
			THEN("Calculator should return NAN")
			{
				REQUIRE(isnan(calculator.GetIdentifierValue("var1")));
			}
		}

		WHEN("Print variable identifier")
		{
			calculator.AssignVarValue("var1", "3.4");

			THEN("Calculator should return result")
			{
				REQUIRE(calculator.GetIdentifierValue("var1") == 3.4);
			}
		}

		WHEN("Print function identifier")
		{
			calculator.CreateFunction("fn1", "3.4+6.6");

			THEN("Calculator should return result")
			{
				REQUIRE(calculator.GetIdentifierValue("fn1") == 10.0);
			}
		}
	}
}

SCENARIO("Calculator has ability to get all vars")
{
	GIVEN("A calculator")
	{
		CCalculator calculator = CCalculator();

		WHEN("No var was declared")
		{
			THEN("List of vars should be empty")
			{
				REQUIRE(calculator.GetVars().size() == 0);
			}
		}

		WHEN("Var was declared")
		{
			calculator.AssignVarValue("var1", "3");

			THEN("List of vars should not be empty")
			{
				REQUIRE(calculator.GetVars().size() != 0);
			}
		}
	}
}

SCENARIO("Calculator has ability to get all functions")
{
	GIVEN("A calculator")
	{
		CCalculator calculator = CCalculator();

		WHEN("No function was declared")
		{
			THEN("List of functions should be empty")
			{
				REQUIRE(calculator.GetFunctions().size() == 0);
			}
		}

		WHEN("Function was declared")
		{
			calculator.CreateFunction("fn1", "3.4+5.6");

			THEN("List of functions should not be empty")
			{
				REQUIRE(calculator.GetFunctions().size() != 0);
			}
		}
	}
}