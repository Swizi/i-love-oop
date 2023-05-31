#include "Calculator.h"

CCalculator::CCalculator()
{
}

CCalculator::~CCalculator()
{
}

// Public

bool CCalculator::CreateVar(const std::string& varName, std::string& errorMsg)
{
	if (m_vars.count(varName) == 0)
	{
		m_vars.insert(std::pair<std::string, double>( varName, NAN ));
	}
	else
	{
		errorMsg = "Variable name is already busy";
		return false;
	}

	return true;
}

bool CCalculator::CreateFunction(const std::string& functionName, const FunctionExpression& expression, std::string& errorMsg)
{
	if (m_functions.count(functionName) != 0 || m_vars.count(functionName) != 0)
	{
		errorMsg = "Function name is already busy";
		return false;
	}

	m_functions.insert(std::pair<std::string, FunctionExpression>(functionName, expression));
	double functionValue = CCalculator::CalculateFunctionValue(functionName, errorMsg);//игнорируй, если не используешь
	if (!errorMsg.empty())
	{
		m_functions.erase(functionName);
		return false;
	}

	return true;
}

double CCalculator::GetIdentifierValue(const std::string& identifierName, std::string& errorMsg)
{
	if (m_vars.count(identifierName) != 0)
	{
		return m_vars[identifierName];
	}

	if (m_functions.count(identifierName) != 0)
	{
		double functionValue = CalculateFunctionValue(identifierName, errorMsg);

		if (!errorMsg.empty())
		{
			return NAN;
		}

		return functionValue;
	}

	errorMsg = "Identifier is not exists";
	return NAN;
}

bool CCalculator::AssignVarValue(const std::string& varName, const std::string& value, std::string& errorMsg)
{
	try
	{
		double doubleValue = std::stod(value);
	}
	catch (std::exception & e)
	{
		if (m_vars.count(value) == 0)
		{
			errorMsg = "Incorrect value";
			return false;
		}
	}

	//TODO: use Create Var
	if (m_vars.count(varName) == 0)
	{
		m_vars.insert(std::pair<std::string, double>(varName, NAN));
	}
	if (m_vars.count(value) != 0)
	{
		m_vars[varName] = m_vars[value];
	}
	else
	{
		m_vars[varName] = std::stod(value);
	}

	return true;
}

std::map<std::string, double> CCalculator::GetVars() const
{
	return m_vars;
}

std::map<std::string, double> CCalculator::GetFunctions()
{
	std::map<std::string, double> calculatedFunctions = {};

	for (auto const &fn : m_functions)
	{
		std::string errorMsg = "";
		double identifierValue = GetIdentifierValue(fn.first, errorMsg);

		calculatedFunctions.insert(std::pair<std::string, double>(fn.first, identifierValue));
	}

	return calculatedFunctions;
}

// Private

double CCalculator::CalculateFunctionValue(const std::string& functionName, std::string& errorMsg)
{
	if (m_functions.count(functionName) == 0)
	{
		errorMsg = "Function is not exists";
		return NAN;
	}

	const FunctionExpression functionExpression = m_functions[functionName];
	if (!functionExpression.secondOperand.empty())
	{
		//TODO: rewrite method
		const std::string firstOperand = functionExpression.firstOperand;
		const std::string secondOperand = functionExpression.secondOperand;
		bool firstIdentiferIsDeclared = m_vars.count(firstOperand) != 0 || m_functions.count(firstOperand) != 0;
		bool secondIdentifierIsDeclared = m_vars.count(secondOperand) != 0 || m_functions.count(secondOperand) != 0;

		if (!firstIdentiferIsDeclared || !secondIdentifierIsDeclared)//TODO: use AND
		{
			try
			{
				double firstDoubleValue = std::stod(firstOperand);
				double secondDoubleValue = std::stod(secondOperand);

				switch (functionExpression.operation)
				{
				case '+':
					return firstDoubleValue + secondDoubleValue;
				case '-':
					return firstDoubleValue - secondDoubleValue;
				case '*':
					return firstDoubleValue * secondDoubleValue;
				case '/':
					if (secondDoubleValue != 0)
					{
						return firstDoubleValue / secondDoubleValue;
					}
					else
					{
						errorMsg = "Can not divide to 0";
						return NAN;
					}
				default:
					return NAN;
				}
			}
			catch (std::exception & e)
			{
				errorMsg = "Incorrect values in expression";
				return NAN;
			}
		}

		double firstIdentifierValue = GetIdentifierValue(firstOperand, errorMsg);
		if (!errorMsg.empty())
		{
			return NAN;
		}
		double secondIdentifierValue = GetIdentifierValue(secondOperand, errorMsg);
		if (!errorMsg.empty())
		{
			return NAN;
		}
		switch (functionExpression.operation)
		{
		case '+':
			return firstIdentifierValue + secondIdentifierValue;
		case '-':
			return firstIdentifierValue - secondIdentifierValue;
		case '*':
			return firstIdentifierValue * secondIdentifierValue;
		case '/':
			if (secondIdentifierValue != 0)
			{
				return firstIdentifierValue / secondIdentifierValue;
			} 
			else
			{
				errorMsg = "Can not divide to 0";
				return NAN;
			}
		default:
			return NAN;
		}
	}
	else
	{
		if (m_vars.count(functionExpression.firstOperand) != 0 || m_functions.count(functionExpression.firstOperand) != 0)
		{
			double result = GetIdentifierValue(functionExpression.firstOperand, errorMsg);
			if (!errorMsg.empty())
			{
				return NAN;
			}
			return result;
		}

		try
		{
			double doubleValue = std::stod(functionExpression.firstOperand);

			return doubleValue;
		}
		catch (std::exception& e)
		{
			errorMsg = "Function expression is incorrect";
			return NAN;
		}
	}

	return NAN;
}

std::vector<char> CCalculator::GetSupportedOperations() const
{
	CCalculator calculator = CCalculator();

	return calculator.m_operations;
}