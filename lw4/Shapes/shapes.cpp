#include <iostream>
#include "CController.h"

int main()
{
	CController controller(std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		controller.GetShape();
	}

	controller.GetShapesInfo();

	return 0;
}