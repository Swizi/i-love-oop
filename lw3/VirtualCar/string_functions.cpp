#include "string_functions.h"

std::vector<std::string> Split(const std::string s, const char delim)
{
	std::vector<std::string> elems;
	std::istringstream iss(s);
	std::string item;
	while (std::getline(iss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

std::string GetLowercasedString(const std::string inputString)
{
	std::string lowercasedString = inputString;
	std::transform(inputString.begin(), inputString.end(), lowercasedString.begin(),
		[](unsigned char ch)
		{
			return tolower(ch);
		}
	);

	return lowercasedString;
}