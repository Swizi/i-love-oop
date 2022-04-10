#include <iostream>
#include <string>
#include "prime_numbers.h"

class Args
{
public:
	int upperBound;
	bool wasError;
};

Args ParseArgs(int argc, char* argv[])
{
	Args args = Args();

	args.wasError = argc != 2;
	if (args.wasError)
	{
		std::cout << "Incorrect arguments count. Arguments should be: <upperBound>" << std::endl;
		return args;
	}
	try
	{
		args.upperBound = argc == 2 ? std::stoi(argv[1]) : -1;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		args.wasError = true;
	}

	return args;
}

int main(int argc, char* argv[])
{
	Args parsedArgs = ParseArgs(argc, argv);
	if (parsedArgs.wasError)
	{
		return 1;
	}

	std::set<int> primeNumbers = GeneratePrimeNumbersSet(parsedArgs.upperBound);
	for (auto primeNumber : primeNumbers)
	{
		std::cout << primeNumber << std::endl;
	}

	return 0;
}