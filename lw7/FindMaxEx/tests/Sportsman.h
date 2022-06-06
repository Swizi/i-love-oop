#pragma once
#include <string>

struct Sportsman
{
	std::string name;
	size_t height;
	size_t weight;
};

bool CompareLessHeight(const Sportsman& left, const Sportsman& right);
bool CompareLessWeight(const Sportsman& left, const Sportsman& right);