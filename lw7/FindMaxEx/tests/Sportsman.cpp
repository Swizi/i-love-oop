#include "Sportsman.h"

bool CompareLessHeight(const Sportsman& left, const Sportsman& right) {
	return left.height < right.height;
}

bool CompareLessWeight(const Sportsman& left, const Sportsman& right)
{
	return left.weight < right.weight;
}