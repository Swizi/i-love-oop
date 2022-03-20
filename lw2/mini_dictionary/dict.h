#pragma once
#include "string_functions.h"
#include <map>
#include <fstream>
#include <iostream>

// Constants
const std::string END_COMMAND = "...";

// Dictionary
std::map<std::string, std::vector<std::string>> get_dict(std::ifstream& dict_file_stream);
void print_dict(std::string dict_file_name, std::map<std::string, std::vector<std::string>>& dict);
void save_dict(std::map<std::string, std::vector<std::string>>& dict, std::string dict_path, std::istream& in);

// Translation
bool has_translation(std::map<std::string, std::vector<std::string>>& dict, const std::string word);
void append_translation(std::map<std::string, std::vector<std::string>>& dict, std::vector<std::string> translation);
void print_translation(std::vector<std::string> translation, std::ostream& out);