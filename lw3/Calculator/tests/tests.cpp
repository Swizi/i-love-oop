#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Calculator.h"
#include "../Controller.h"

SCENARIO("Calculator has ability to create variables")
{
	GIVEN("A calculator")
	{
		CCalculator calculator = CCalculator();

		WHEN("Create new variable")
		{
			std::string errorMsg = "";
			calculator.CreateVar("new_var", errorMsg);
			REQUIRE(errorMsg.empty());

			THEN("Calculator should contain this variable")
			{
				REQUIRE(calculator.GetVars().count("new_var") != 0);
			}

			THEN("Calculator should containt this variable with value equals to NAN")
			{
				std::string errorMsg = "";
				REQUIRE(isnan(calculator.GetIdentifierValue("new_var", errorMsg)));
				REQUIRE(errorMsg.empty());
			}
		}

		WHEN("Create variable with name, that has already used")
		{
			std::string errorMsg = "";
			calculator.CreateVar("new_var", errorMsg);
			calculator.CreateVar("new_var", errorMsg);

			THEN("Repeated command should be ignored and error should be printed")
			{
				REQUIRE(!errorMsg.empty());
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
			std::string errorMsg = "";
			calculator.AssignVarValue("new_var", "123.0", errorMsg);
			REQUIRE(errorMsg.empty());

			THEN("Variable should be created and value should be assigned to this var")
			{
				std::string errorMsg = "";
				REQUIRE(calculator.GetIdentifierValue("new_var", errorMsg) == 123.0);
				REQUIRE(errorMsg.empty());
			}
		}

		WHEN("Assign value to existent variable")
		{
			std::string errorMsg = "";
			calculator.CreateVar("new_var", errorMsg);
			calculator.AssignVarValue("new_var", "156.123", errorMsg);
			REQUIRE(errorMsg.empty());

			THEN("Value should be assigned")
			{
				std::string errorMsg = "";
				REQUIRE(calculator.GetIdentifierValue("new_var", errorMsg) == 156.123);
				REQUIRE(errorMsg.empty());
			}
		}

		WHEN("Assign incorrect double value to var")
		{
			std::string errorMsg = "";
			calculator.CreateVar("new_var", errorMsg);
			calculator.AssignVarValue("new_var", "abc", errorMsg);
			REQUIRE(!errorMsg.empty());

			THEN("Value should not be assigned")
			{
				std::string errorMsg = "";
				REQUIRE(isnan(calculator.GetIdentifierValue("new_var", errorMsg)));
				REQUIRE(errorMsg.empty());
			}
		}

		WHEN("Assing variable to another variable")
		{
			std::string errorMsg = "";
			calculator.AssignVarValue("var1", "5.2", errorMsg);
			calculator.AssignVarValue("var2", "var1", errorMsg);
			REQUIRE(errorMsg.empty());

			THEN("Variable should be assigned")
			{
				std::string errorMsg = "";
				REQUIRE(calculator.GetIdentifierValue("var2", errorMsg) == 5.2);
				REQUIRE(errorMsg.empty());
			}
		}

		WHEN("Assign function to variable")
		{
			std::string errorMsg = "";
			calculator.AssignVarValue("var1", "fn1", errorMsg);
			REQUIRE(!errorMsg.empty());

			THEN("Function shoulde not be assigned")
			{
				std::string errorMsg = "";
				REQUIRE(isnan(calculator.GetIdentifierValue("var1", errorMsg)));
				REQUIRE(!errorMsg.empty());
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
			std::string errorMsg = "";
			calculator.CreateVar("id1", errorMsg);
			REQUIRE(errorMsg.empty());
			CCalculator::FunctionExpression expression;
			expression.firstOperand = "1";
			calculator.CreateFunction("id1", expression, errorMsg);
			REQUIRE(!errorMsg.empty());

			THEN("Function should not be createad and error should be printed")
			{
				std::string errorMsg = "";
				REQUIRE(isnan(calculator.GetIdentifierValue("id1", errorMsg)));
				REQUIRE(errorMsg.empty());
			}
		}

		WHEN("Assign function with double number")
		{
			std::string errorMsg = "";
			CCalculator::FunctionExpression expression;
			expression.firstOperand = "1.3";
			calculator.CreateFunction("fn1", expression, errorMsg);
			REQUIRE(errorMsg.empty());

			THEN("Function should have double number value")
			{
				std::string errorMsg = "";
				REQUIRE(calculator.GetIdentifierValue("fn1", errorMsg) == 1.3);
				REQUIRE(errorMsg.empty());
			}
		}

		WHEN("Assign expression, that have undeclared identifier")
		{
			std::string errorMsg = "";
			CCalculator::FunctionExpression expression;
			expression.firstOperand = "var1";
			expression.operation = '+';
			expression.secondOperand = "var2";
			calculator.CreateFunction("fn1", expression, errorMsg);
			REQUIRE(errorMsg.empty());

			THEN("Function should return NAN")
			{
				std::string errorMsg = "";
				REQUIRE(isnan(calculator.GetIdentifierValue("fn1", errorMsg)));
				REQUIRE(errorMsg.empty());
			}
		}

		WHEN("Assign number expression")
		{
			std::string errorMsg = "";
			CCalculator::FunctionExpression expression;
			expression.firstOperand = "1.3";
			expression.operation = '+';
			expression.secondOperand = "4.5";
			calculator.CreateFunction("fn1", expression, errorMsg);
			REQUIRE(errorMsg.empty());

			THEN("Function should return result")
			{
				std::string errorMsg = "";
				REQUIRE(calculator.GetIdentifierValue("fn1", errorMsg) == 5.8);
				REQUIRE(errorMsg.empty());
			}
		}

		WHEN("Assign expression, that have zero division")
		{
			std::string errorMsg = "";
			CCalculator::FunctionExpression expression;
			expression.firstOperand = "1";
			expression.operation = '/';
			expression.secondOperand = "0";
			calculator.CreateFunction("fn1", expression, errorMsg);
			REQUIRE(errorMsg.empty());

			THEN("Function should return NAN")
			{
				std::string errorMsg = "";
				REQUIRE(isnan(calculator.GetIdentifierValue("fn1", errorMsg)));
				REQUIRE(errorMsg.empty());
			}
		}

		WHEN("Assign vars expression")
		{
			std::string errorMsg = "";
			calculator.AssignVarValue("var1", "3.4", errorMsg);
			calculator.AssignVarValue("var2", "6.6", errorMsg);
			CCalculator::FunctionExpression expression;
			expression.firstOperand = "var1";
			expression.operation = '+';
			expression.secondOperand = "var2";
			calculator.CreateFunction("fn1", expression, errorMsg);
			REQUIRE(errorMsg.empty());

			THEN("Function should return result")
			{
				std::string errorMsg = "";
				REQUIRE(calculator.GetIdentifierValue("fn1", errorMsg) == 10.0);
				REQUIRE(errorMsg.empty());
			}
		}

		WHEN("Assign functions expression")
		{
			std::string errorMsg = "";
			CCalculator::FunctionExpression expression;
			expression.firstOperand = "3.4";
			calculator.CreateFunction("fn1", expression, errorMsg);
			expression.firstOperand = "6.6";
			calculator.CreateFunction("fn2", expression, errorMsg);
			expression.firstOperand = "fn1";
			expression.operation = '+';
			expression.secondOperand = "fn2";
			calculator.CreateFunction("fn3", expression, errorMsg);
			REQUIRE(errorMsg.empty());

			THEN("Function should return result")
			{
				std::string errorMsg = "";
				REQUIRE(calculator.GetIdentifierValue("fn3", errorMsg) == 10.0);
				REQUIRE(errorMsg.empty());
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
				std::string errorMsg = "";
				REQUIRE(isnan(calculator.GetIdentifierValue("var1", errorMsg)));
				REQUIRE(!errorMsg.empty());
			}
		}

		WHEN("Print variable identifier")
		{
			std::string errorMsg = "";
			calculator.AssignVarValue("var1", "3.4", errorMsg);
			REQUIRE(errorMsg.empty());

			THEN("Calculator should return result")
			{
				std::string errorMsg = "";
				REQUIRE(calculator.GetIdentifierValue("var1", errorMsg) == 3.4);
				REQUIRE(errorMsg.empty());
			}
		}

		WHEN("Print function identifier")
		{
			std::string errorMsg = "";
			CCalculator::FunctionExpression expression;
			expression.firstOperand = "3.4";
			expression.operation = '+';
			expression.secondOperand = "6.6";
			calculator.CreateFunction("fn1", expression, errorMsg);
			REQUIRE(errorMsg.empty());

			THEN("Calculator should return result")
			{
				std::string errorMsg = "";
				REQUIRE(calculator.GetIdentifierValue("fn1", errorMsg) == 10.0);
				REQUIRE(errorMsg.empty());
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
			std::string errorMsg = "";
			calculator.AssignVarValue("var1", "3", errorMsg);
			REQUIRE(errorMsg.empty());

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
			std::string errorMsg = "";
			CCalculator::FunctionExpression expression;
			expression.firstOperand = "3.4";
			expression.operation = '+';
			expression.secondOperand = "5.6";
			calculator.CreateFunction("fn1", expression, errorMsg);
			REQUIRE(errorMsg.empty());

			THEN("List of functions should not be empty")
			{
				REQUIRE(calculator.GetFunctions().size() != 0);
			}
		}
	}
}

SCENARIO("Calculator can be controlled by controller")
{
	GIVEN("A calculator")
	{
		CCalculator calculator = CCalculator();
		
		WHEN("User controls to create variable")
		{
			std::string errorMsg = "";
			std::istringstream iss("var new_var");
			std::ostringstream oss;
			CController controller = CController(calculator, iss, oss);
			controller.HandleCommand();

			THEN("Calculator should have this variable")
			{
				REQUIRE(isnan(calculator.GetIdentifierValue("new_var", errorMsg)));
				REQUIRE(errorMsg.empty());
			}
		}

		WHEN("User controls to assign value to variable")
		{
			std::string errorMsg = "";
			std::istringstream iss("let new_var=3.2");
			std::ostringstream oss;
			CController controller = CController(calculator, iss, oss);
			controller.HandleCommand();

			THEN("Calculator should assign this value")
			{
				REQUIRE(calculator.GetIdentifierValue("new_var", errorMsg) == 3.2);
				REQUIRE(errorMsg.empty());
			}
		}

		WHEN("User controls to create function")
		{
			std::string errorMsg = "";
			std::istringstream iss("fn new_fn=3.2");
			std::ostringstream oss;
			CController controller = CController(calculator, iss, oss);
			controller.HandleCommand();

			THEN("Calculator should save this function")
			{
				REQUIRE(calculator.GetIdentifierValue("new_fn", errorMsg) == 3.2);
				REQUIRE(errorMsg.empty());
			}
		}

		WHEN("User controls to print identifier")
		{
			std::istringstream iss("let new_var=3.2\nprint new_var");
			std::ostringstream oss;
			CController controller = CController(calculator, iss, oss);
			controller.HandleCommand();
			controller.HandleCommand();

			THEN("Calculator print value of this identifier")
			{
				REQUIRE(oss.str() == "3.2\n");
			}
		}

		WHEN("User controls to get all vars")
		{
			std::istringstream iss("let new_var=3.2\nprintvars");
			std::ostringstream oss;
			CController controller = CController(calculator, iss, oss);
			controller.HandleCommand();
			controller.HandleCommand();

			THEN("Calculator should print all vars")
			{
				REQUIRE(oss.str() == "new_var:3.2\n");
			}
		}

		WHEN("User controls to get all functions")
		{
			std::istringstream iss("fn new_fn=3.2\nprintfns");
			std::ostringstream oss;
			CController controller = CController(calculator, iss, oss);
			controller.HandleCommand();
			controller.HandleCommand();

			THEN("Calculator should print all functions")
			{
				REQUIRE(oss.str() == "new_fn:3.2\n");
			}
		}
	}
}