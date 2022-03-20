#pragma once
#include <string>

void move_window(std::string &window);
bool is_window_string_possible(std::string const window, std::string const str);
std::string replace_str(std::string source_string, std::string const find_string, std::string const replace_string);