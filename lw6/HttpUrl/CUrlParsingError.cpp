#include "CUrlParsingError.h"

CUrlParsingError::CUrlParsingError(const std::string& msg)
	: std::invalid_argument(msg)
{
}

CUrlParsingError::CUrlParsingError(const char* msg)
	: std::invalid_argument(msg)
{
}