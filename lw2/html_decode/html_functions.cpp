#include "html_functions.h";
#include "string_functions.h";

std::string html_decode(std::string const html)
{
	std::map<std::string, std::string> decoders = {
		{"&quot;", "\""},
		{"&apos;", "'"},
		{"&lt;", "<"},
		{"&gt;", ">"},
		{"&amp;", "&"}
	};
	std::string decoded_string = html;

	for (const auto& [find_string, replace_string] : decoders)
	{
		decoded_string = replace_str(decoded_string, find_string, replace_string);
	}

	return decoded_string;
}

void decode(std::istream& input_stream, std::ostream& decoded_lines)
{
	std::string input_line = "";

	while (getline(input_stream, input_line))
	{
		decoded_lines << html_decode(input_line) << "\n";
	}
}
