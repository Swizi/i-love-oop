#include "string_functions.h";
#include <iostream>

void MoveWindow(std::string &window)
{
	for (int i = 1; i < window.size(); i++)
	{
		window[i - 1] = window[i];
	}
}

bool IsWindowStringPossible(std::string const window, std::string const str)
{
	bool isPossible = false;

	int i = 0;
	while (i < str.size() && !isPossible)
	{
		isPossible = window.substr(window.size() - 1 - i, i + 1) == str.substr(0, i + 1) ? true : isPossible;
		i++;
	}

	return isPossible;
}

std::string ReplaceStr(const std::string sourceString, std::string const findString, std::string const replaceString)
{
	std::string outString = "";
	std::string window = "";

	for (int i = 0; i < findString.size(); i++)
	{
		window += ' ';
	}

	std::string reserve = "";

	if (window.size() != 0)
	{
		for (auto sourceIt = sourceString.cbegin(); sourceIt != sourceString.end(); ++sourceIt)
		{
			MoveWindow(window);
			window[window.size() - 1] = *sourceIt;

			bool isFindStringPossible = IsWindowStringPossible(window, findString);

			reserve += *sourceIt;

			if (window == findString)
			{
				outString += replaceString;
				reserve = "";
			}

			if (!isFindStringPossible)
			{
				outString += reserve;
				reserve = "";
			}
		}
	}
	else
	{
		outString = sourceString;
	}

	return outString;
}