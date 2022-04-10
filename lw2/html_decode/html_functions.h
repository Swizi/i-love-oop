#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <map>

std::string HtmlDecode(std::string const html);
void Decode(std::istream& inputStream, std::ostream& decodedLines);
