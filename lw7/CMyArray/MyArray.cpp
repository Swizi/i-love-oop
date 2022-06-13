#include "CMyArray.h"
#include <string>
#include <iostream>

int main()
{
	CMyArray<std::string> stringArray;
	stringArray.Insert("i");
	stringArray.Insert("love");
	stringArray.Insert("you");
	for (auto const& str: stringArray)
	{
		std::cout << str << std::endl;
	}

	CMyArray<double> doubleArray;
	doubleArray.Insert(3);
	doubleArray.Insert(3.2);
	for (auto const& num : doubleArray)
	{
		std::cout << num << std::endl;
	}

	return 0;
}