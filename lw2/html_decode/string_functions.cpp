#include "string_functions.h";
#include <iostream>

void move_window(std::string &window)
{
	for (int i = 1; i < window.size(); i++)
	{
		window[i - 1] = window[i];
	}
}

bool is_window_string_possible(std::string const window, std::string const str)
{
	bool is_possible = false;

	int i = 0;
	while (i < str.size() && !is_possible)
	{
		is_possible = window.substr(window.size() - 1 - i, i + 1) == str.substr(0, i + 1) ? true : is_possible;
		i++;
	}

	return is_possible;
}

std::string replace_str(std::string source_string, std::string const find_string, std::string const replace_string)
{
	std::string out_string = "";
	std::string window = "";

	for (int i = 0; i < find_string.size(); i++)
	{
		window += ' ';
	}

	std::string reserve = "";

	if (window.size() != 0)
	{
		for (std::string::iterator source_it = source_string.begin(); source_it != source_string.end(); ++source_it)
		{
			move_window(window);
			window[window.size() - 1] = *source_it;

			bool is_find_string_possible = is_window_string_possible(window, find_string);

			reserve += *source_it;

			if (window == find_string)
			{
				out_string += replace_string;
				reserve = "";
			}

			if (!is_find_string_possible)
			{
				out_string += reserve;
				reserve = "";
			}
		}
	}
	else
	{
		out_string = source_string;
	}

	return out_string;
}