#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <map>

std::string html_decode(std::string const html);
void decode(std::istream& input_stream, std::ostream& decoded_lines);
