#pragma once
#include <istream>
#include <functional>
#include <map>

class CCalculator;

class CController
{
public:
	class CController(CCalculator& calculator, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool CreateVariable(std::istream& args);
	bool AssignVariableWithValue(std::istream& args);
	bool CreateFunction(std::istream& args);
	bool PrintIdentifier(std::istream& args);
	bool PrintVars(std::istream& args);
	bool PrintFunctions(std::istream& args);
	bool Help(std::istream& args);

	struct Expression
	{
		std::string identiferName;
		char operation;
		std::string firstOperand;
		std::string secondOperand;
	};

	std::vector<std::string> ParseExpression(std::istream& args);

private:
	using Handler = std::function<bool(std::istream & args)>;

	using ActionMap = std::map<std::string, Handler>;

	CCalculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};