#include "html_functions.h";
#include "string_functions.h";

std::string HtmlDecode(std::string const html)
{
	std::map<std::string, std::string> decoders = {
		{"&quot;", "\""},
		{"&apos;", "'"},
		{"&lt;", "<"},
		{"&gt;", ">"},
		{"&amp;", "&"}
	};
	std::string decodedString = html;

	for (const auto& [findString, replaceString] : decoders)
	{
		decodedString = ReplaceStr(html, findString, replaceString);
	}

	return decodedString;
}

void Decode(std::istream& inputStream, std::ostream& decodedLines)
{
	std::string inputLine = "";

	while (getline(inputStream, inputLine))
	{
		decodedLines << HtmlDecode(inputLine) << "\n";
	}
}
