#include "Calculator.h"
#include "Controller.h"

CController::CController(CCalculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "var", bind(&CController::CreateVariable, this, std::placeholders::_1) },
		  { "let", bind(&CController::AssignVariableWithValue, this, std::placeholders::_1) },
		  { "fn", bind(&CController::CreateFunction, this, std::placeholders::_1) },
		  { "print", bind(&CController::PrintIdentifier, this, std::placeholders::_1) },
		  { "printvars", bind(&CController::PrintVars, this, std::placeholders::_1) },
		  { "printfns", bind(&CController::PrintFunctions, this, std::placeholders::_1) },
		  { "help", bind(&CController::Help, this, std::placeholders::_1) }
		})
{
}

// Public

bool CController::HandleCommand()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream iss(commandLine);

	std::string action;
	iss >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(iss);
	}

	return false;
}

// Private
 
CController::Args CController::ParseArgs(std::istream& args)
{
	Args expression;
	expression.identiferName = "";
	expression.operation = ' ';
	expression.firstOperand = "";
	expression.secondOperand = "";
	std::string str = "";
	int equalSignPos = -1;
	int operationPos = -1;
	args >> str;

	if (str.find('=') != std::string::npos)
	{
		equalSignPos = str.find('=');
	}
	for (auto const& oper : m_calculator.GetSupportedOperations())
	{
		int currOperatorPos = str.find(oper);

		if (str.find(oper) != std::string::npos)
		{
			operationPos = currOperatorPos;
		}
	}
	if (equalSignPos != -1)
	{
		expression.identiferName = str.substr(0, equalSignPos);
		if (operationPos != -1)
		{
			expression.firstOperand = str.substr(equalSignPos + 1, operationPos);
			expression.operation = str[operationPos];
			expression.secondOperand = str.substr(operationPos + 1, str.size());
		}
		else
		{
			expression.firstOperand = str.substr(equalSignPos + 1, str.size());
		}
	}
	else
	{
		expression.identiferName = str.substr(0, str.size());
	}
	
	return expression;
}

bool CController::CreateVariable(std::istream& args)
{
	std::string errorMsg = "";
	const Args parsedArgs = ParseArgs(args);

	m_calculator.CreateVar(parsedArgs.identiferName, errorMsg);
	if (!errorMsg.empty())
	{
		m_output << errorMsg << std::endl;
	}

	return true;
}

bool CController::AssignVariableWithValue(std::istream& args)
{
	std::string errorMsg = "";
	const Args parsedArgs = ParseArgs(args);

	m_calculator.AssignVarValue(parsedArgs.identiferName, parsedArgs.firstOperand, errorMsg);
	if (!errorMsg.empty())
	{
		m_output << errorMsg << std::endl;
	}

	return true;
}

bool CController::CreateFunction(std::istream& args)
{
	std::string errorMsg = "";
	const Args parsedArgs = ParseArgs(args);
	CCalculator::FunctionExpression expression;
	expression.firstOperand = parsedArgs.firstOperand;
	expression.operation = parsedArgs.operation;
	expression.secondOperand = parsedArgs.secondOperand;

	m_calculator.CreateFunction(parsedArgs.identiferName, expression, errorMsg);
	if (!errorMsg.empty())
	{
		m_output << errorMsg << std::endl;
	}

	return true;
}

bool CController::PrintIdentifier(std::istream& args)
{
	std::string errorMsg = "";
	const Args parsedArgs = ParseArgs(args);

	const double result = m_calculator.GetIdentifierValue(parsedArgs.identiferName, errorMsg);

	if (!errorMsg.empty())
	{
		m_output << errorMsg << std::endl;
	}
	else
	{
		m_output << std::setprecision(2) << result << std::endl;
	}

	return true;
}

bool CController::PrintVars(std::istream& args)
{
	const Args parsedArgs = ParseArgs(args);

	const std::map<std::string, double> vars = m_calculator.GetVars();
	for (auto const& var : vars)
	{
		m_output << var.first << ":" << std::setprecision(2) << var.second << std::endl;
	}

	return true;
}

bool CController::PrintFunctions(std::istream& args)
{
	const Args parsedArgs = ParseArgs(args);

	const std::map<std::string, double> functions = m_calculator.GetFunctions();
	for (auto const& fn : functions)
	{
		m_output << fn.first << ":" << std::setprecision(2) << fn.second << std::endl;
	}

	return true;
}

bool CController::Help(std::istream& /*args*/)
{
	m_output << "Available commands:" << std::endl;
	for (auto const& action : m_actionMap)
	{
		m_output << action.first << std::endl;
	}

	return true;
}