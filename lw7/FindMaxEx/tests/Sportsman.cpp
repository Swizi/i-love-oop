#include "Sportsman.h"

bool GetMinHeight(const Sportsman& left, const Sportsman& right)
{
	return left.height < right.height;
}

bool GetMinWeight(const Sportsman& left, const Sportsman& right)
{
	return left.weight < right.weight;
}