#include "string_functions.h";

std::vector<std::string> split(const std::string s, const char delim)
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

std::string get_lowercased_string(const std::string input_string)
{
	std::string lowercased_string = input_string;
	std::transform(input_string.begin(), input_string.end(), lowercased_string.begin(),
		[](unsigned char ch)
		{
			return tolower(ch);
		}
	);

	return lowercased_string;
}