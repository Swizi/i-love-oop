#include "prime_numbers.h"

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::vector<int> numbers = {};
	std::set<int> primeNumbers = {};

	for (int num = 0; num < upperBound; num++)
	{
		numbers.push_back(num);
	}

	for (int i = 2; i < upperBound; i++)
	{
		if (numbers[i] != 0)
		{
			primeNumbers.insert(numbers[i]);
			if (i < INT_MAX / i)
			{
				for (int j = i * i; j < upperBound && j < INT_MAX; j += i)
				{
					numbers[j] = 0;
				}
			}
		}
	}

	return primeNumbers;
}