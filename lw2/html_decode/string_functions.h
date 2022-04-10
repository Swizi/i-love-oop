#pragma once
#include <string>

void MoveWindow(std::string &window);
bool IsWindowStringPossible(std::string const window, std::string const str);
std::string ReplaceStr(std::string sourceString, std::string const findString, std::string const replaceString);