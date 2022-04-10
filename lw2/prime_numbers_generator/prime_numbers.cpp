#include "prime_numbers.h"
#include <iostream>

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < 2)
	{
		return {};
	}

	std::vector<bool> primeIndexes(upperBound + 1, true);

	primeIndexes[0] = false;
	primeIndexes[1] = false;
	for (int j = 4; j <= upperBound && j < INT_MAX; j += 2)
	{
		primeIndexes[j] = false;
	}

	for (int i = 3; i * i <= upperBound; i += 2)
	{
		if (primeIndexes[i] == true)
		{
			if (i < INT_MAX / i)
			{
				for (int j = i * i; j <= upperBound && j < INT_MAX; j += i)
				{
					primeIndexes[j] = false;
				}
			}
		}
	}

	std::set<int> primeNumbers = {};
	for (int i = 0; i < primeIndexes.size(); i++)
	{
		if (primeIndexes[i] == true)
		{
			primeNumbers.insert(i);
		}
	}

	return primeNumbers;
}