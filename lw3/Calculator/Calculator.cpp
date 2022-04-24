#include "Calculator.h";

CCalculator::CCalculator()
{

}

CCalculator::~CCalculator()
{

}

// Public

bool CCalculator::CreateVar(const std::string& varName)
{
	if (m_vars.count(varName) == 0)
	{
		m_vars.insert(std::pair<std::string, double>( varName, NAN ));
	}
	else
	{
		return false;
	}

	return true;
}

bool CCalculator::CreateFunction(const std::string& functionName, const std::string& expression)
{
	if (m_functions.count(functionName) != 0 || m_vars.count(functionName) != 0)
	{
		return false;
	}

	m_functions.insert(std::pair<std::string, std::string>(functionName, expression));

	return true;
}

double CCalculator::GetIdentifierValue(const std::string& identifierName)
{
	if (m_vars.count(identifierName) != 0)
	{
		return m_vars[identifierName];
	}

	if (m_functions.count(identifierName) != 0)
	{
		return CalculateFunctionValue(identifierName);
	}

	return NAN;
}

bool CCalculator::AssignVarValue(const std::string& varName, const std::string& value)
{
	try
	{
		double doubleValue = std::stod(value);
	}
	catch (std::exception & e)
	{
		if (m_vars.count(value) == 0)
		{
			return false;
		}
	}

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
		calculatedFunctions.insert(std::pair<std::string, double>(fn.first, GetIdentifierValue(fn.first)));
	}

	return calculatedFunctions;
}

// Private

double CCalculator::CalculateFunctionValue(const std::string& functionName)
{
	if (m_functions.count(functionName) == 0)
	{
		return NAN;
	}

	const std::string functionExpression = m_functions[functionName];
	int operatorIndex = -1;
	for (auto const &oper : m_operators)
	{
		int currOperatorIndex = functionExpression.find(oper);

		if (functionExpression.find(oper) != std::string::npos)
		{
			operatorIndex = currOperatorIndex;
		}
	}

	if (operatorIndex != -1)
	{
		const std::string firstOperand = functionExpression.substr(0, operatorIndex);
		const std::string secondOperand = functionExpression.substr(operatorIndex + 1, functionExpression.length());
		bool firstIdentiferIsDeclared = m_vars.count(firstOperand) != 0 || m_functions.count(firstOperand) != 0;
		bool secondIdentifierIsDeclared = m_vars.count(secondOperand) != 0 || m_functions.count(secondOperand) != 0;

		if (!firstIdentiferIsDeclared || !secondIdentifierIsDeclared)
		{
			try
			{
				double firstDoubleValue = std::stod(firstOperand);
				double secondDoubleValue = std::stod(secondOperand);

				switch (functionExpression[operatorIndex])
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
						return NAN;
					}
				default:
					return NAN;
				}
			}
			catch (std::exception & e)
			{
				return NAN;
			}
			return NAN;
		}

		double secondIdentifierValue = GetIdentifierValue(secondOperand);
		switch (functionExpression[operatorIndex])
		{
		case '+':
			return GetIdentifierValue(firstOperand) + secondIdentifierValue;
		case '-':
			return GetIdentifierValue(firstOperand) - secondIdentifierValue;
		case '*':
			return GetIdentifierValue(firstOperand) * secondIdentifierValue;
		case '/':
			if (secondIdentifierValue != 0)
			{
				return GetIdentifierValue(firstOperand) / secondIdentifierValue;
			} 
			else
			{
				return NAN;
			}
		default:
			return NAN;
		}
	}
	else
	{
		if (m_vars.count(functionExpression) != 0 || m_functions.count(functionExpression) != 0)
		{
			return GetIdentifierValue(functionExpression);
		}

		try
		{
			double doubleValue = std::stod(functionExpression);

			return doubleValue;
		}
		catch (std::exception& e)
		{
			return NAN;
		}
	}
}