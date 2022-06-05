#pragma once
#include "common_libs.h"

class CUrlParsingError : public std::invalid_argument
{
public:
	CUrlParsingError(const std::string& msg);
	CUrlParsingError(const char* msg);
};
