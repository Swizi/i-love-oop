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
			std::cout << "Protocol: ";
			// TODO: GetStringProtocol()
			if (httpUrl.GetProtocol() == Protocol::HTTP)
			{
				std::cout << "HTTP";
			}
			if (httpUrl.GetProtocol() == Protocol::HTTPS)
			{
				std::cout << "HTTPS";
			}
			std::cout << std::endl;
			std::cout << "Domain: " << httpUrl.GetDomain() << std::endl;
			std::cout << "Port: " << httpUrl.GetPort() << std::endl;
			std::cout << "Document: " << httpUrl.GetDocument() << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	return 0;
}