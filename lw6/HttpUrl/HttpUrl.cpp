#include "CHttpUrl.h"

int main()
{
	std::string line;

	// TODO: —читывать урлы, пока пользов. не закончит ввод
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cin >> line;

		try
		{
			CHttpUrl httpUrl = CHttpUrl(line);
			std::cout << "Url is correct" << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	return 0;
}