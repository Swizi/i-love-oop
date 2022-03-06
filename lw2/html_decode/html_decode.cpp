#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

string replace(string const& source_string, string const& find_string, string const& replace_string)
{
	string replaced_string = source_string;
	size_t find_pos = replaced_string.find(find_string);

	while (find_pos != string::npos)
	{
		replaced_string.replace(find_pos, find_string.length(), replace_string);
		find_pos = replaced_string.find(find_string);
	}

	return replaced_string;
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

	for (pair<string, string> decoder : decoders)
	{
		string find_string = decoder.first;
		string replace_string = decoder.second;

		decoded_string = replace(decoded_string, find_string, replace_string);
	}

	return decoded_string;
}

int main()
{
	string input_line = "";

	while (getline(cin, input_line))
	{
		cout << html_decode(input_line) << endl;
	}

	return 0;
}