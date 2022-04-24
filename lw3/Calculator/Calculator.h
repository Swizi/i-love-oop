#pragma once
#include <string>
#include <map>
#include <vector>

class CCalculator
{
public:
	CCalculator();
	~CCalculator();

	bool CreateVar(const std::string& varName);
	bool AssignVarValue(const std::string& varName, const std::string& value);
	bool CreateFunction(const std::string& functionName, const std::string& expression);
	double GetIdentifierValue(const std::string& identifierName);
	std::map<std::string, double> GetVars() const;
	std::map<std::string, double> GetFunctions();

private:
	std::vector<char> m_operators = { '+', '-', '*', '/' };

	std::map<std::string, double> m_vars;
	std::map<std::string, std::string> m_functions;

	double CalculateFunctionValue(const std::string& functionName);
};