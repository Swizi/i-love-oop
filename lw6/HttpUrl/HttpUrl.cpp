#include "CHttpUrl.h"

int main()
{
	std::string line;
	std::cin >> line;

	try
	{
		CHttpUrl httpUrl = CHttpUrl(line);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}