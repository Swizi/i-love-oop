#pragma once
#include <string>

struct Sportsman
{
	std::string name;
	size_t height;
	size_t weight;
};

bool GetMinHeight(const Sportsman& left, const Sportsman& right);
bool GetMinWeight(const Sportsman& left, const Sportsman& right);