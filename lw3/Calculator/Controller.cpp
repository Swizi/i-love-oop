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
		  { "printfns", bind(&CController::PrintFunctions, this, std::placeholders::_1) }
		})
{
}

// Public

bool CController::HandleCommand()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

// Private

std::vector<std::string> CController::ParseExpression(std::istream& args)
{

}

bool CController::CreateVariable(std::istream& args)
{
	const std::string varName = "";
	args >> varName;

	bool result = m_calculator.CreateVar(varName);

	if (!result)
	{
		m_output << "Variable was not created" << std::endl;
	}

	return true;
}

bool CController::AssignVariableWithValue(std::istream& args)
{

}