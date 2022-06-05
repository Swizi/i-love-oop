#include "string_libs.h"

std::string lower(const std::string& str)
{
	std::string lowercasedStr = str;

	std::for_each(lowercasedStr.begin(), lowercasedStr.end(), [](char& c) {
		c = std::tolower(c);
	});
	
	return lowercasedStr;
}