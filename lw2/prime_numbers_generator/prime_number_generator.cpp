#include <iostream>
#include <string>
#include "prime_numbers.h";

using namespace std;

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
		cout << "Incorrect arguments count. Arguments should be: <upperBound>" << endl;
	}
	try
	{
		args.upperBound = argc == 2 ? stoi(argv[1]) : -1;
	}
	catch (std::exception e)
	{
		cout << e.what() << endl;
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
		cout << primeNumber << endl;
	}

	return 0;
}