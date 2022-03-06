#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

void move_window(string& window)
{
	for (int i = 1; i < window.size(); i++)
	{
		window[i - 1] = window[i];
	}
}

bool is_window_string_possible(string const& window, string const& str)
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

string replace(string& source_string, string const& find_string, string const& replace_string)
{
	string out_string = "";
	string window = "";

	for (int i = 0; i < find_string.size(); i++)
	{
		window += ' ';
	}

	string reserve = "";

	if (window.size() != 0)
	{
		for (string::iterator source_it = source_string.begin(); source_it != source_string.end(); ++source_it)
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

string html_decode(string const& html)
{
	map<string, string> decoders = {
		{"&quot;", "\""},
		{"&apos;", "'"},
		{"&lt;", "<"},
		{"&gt;", ">"},
		{"&amp;", "&"}
	};
	string decoded_string = html;

	for (const auto& [find_string, replace_string] : decoders)
	{
		decoded_string = replace(decoded_string, find_string, replace_string);
	}

	return decoded_string;
}

void decode(istream& input_stream, ofstream& decoded_lines)
{
	string input_line = "";

	while (getline(input_stream, input_line))
	{
		decoded_lines << html_decode(input_line) << endl;
	}
}

void print(ifstream& out_lines, ostream& out)
{
	string line = "";

	while (getline(out_lines, line))
	{
		out << line << endl;
	}
}

int main()
{
	char* temp_file = tmpnam(NULL);

	ofstream decoded_lines(temp_file);
	decode(cin, decoded_lines);
	decoded_lines.close();

	ifstream out_lines(temp_file);
	print(out_lines, cout);
	out_lines.close();

	remove(temp_file);

	return 0;
}