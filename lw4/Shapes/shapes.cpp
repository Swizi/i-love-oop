#include <iostream>
#include "CController.h"

int main()
{
	CController controller(std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		try
		{
			controller.GetShape();
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	try
	{
		controller.DrawShapes();
		controller.GetShapesInfo();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}