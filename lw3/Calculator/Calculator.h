#pragma once
#include <string>
#include <map>
#include <vector>

class CCalculator
{
public:
	CCalculator();
	~CCalculator();

	struct FunctionExpression
	{
		std::string firstOperand;
		char operation;
		std::string secondOperand;
	};

	bool CreateVar(const std::string& varName, std::string& errorMsg);
	bool AssignVarValue(const std::string& varName, const std::string& value, std::string& errorMsg);
	bool CreateFunction(const std::string& functionName, const FunctionExpression& expression, std::string& errorMsg);
	double GetIdentifierValue(const std::string& identifierName, std::string& errorMsg);
	std::map<std::string, double> GetVars() const;
	std::map<std::string, double> GetFunctions();

	std::vector<char> GetSupportedOperations() const;

private:
	const std::vector<char> m_operations = { '+', '-', '*', '/' };

	std::map<std::string, double> m_vars;
	std::map<std::string, FunctionExpression> m_functions;

	double CalculateFunctionValue(const std::string& functionName, std::string& errorMsg);
};