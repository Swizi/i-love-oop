#include <iostream>
#include "Calculator.h"
#include "Controller.h"

int main()
{
	CCalculator virtualCalculator = CCalculator();
	CController controller(virtualCalculator, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!controller.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
}