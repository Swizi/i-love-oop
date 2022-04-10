#pragma once
#include "string_functions.h"
#include <map>
#include <fstream>
#include <iostream>

// Constants
const std::string END_COMMAND = "...";

// Dictionary
std::map<std::string, std::vector<std::string>> GetDict(std::ifstream& dictFileStream);
void PrintDict(std::string dictFileName, std::map<std::string, std::vector<std::string>>& dict);
void SaveDict(std::map<std::string, std::vector<std::string>>& dict, std::string dictPath, std::istream& in);

// Translation
bool HasTranslation(std::map<std::string, std::vector<std::string>>& dict, const std::string word);
void AppendTranslation(std::map<std::string, std::vector<std::string>>& dict, std::vector<std::string> translation);
void PrintTranslation(std::vector<std::string> translation, std::ostream& out);