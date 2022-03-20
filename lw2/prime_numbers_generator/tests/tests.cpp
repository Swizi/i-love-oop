#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../prime_numbers.h"

TEST_CASE("Zero upper bound")
{
	std::set<int> primeNums = GeneratePrimeNumbersSet(0);

	REQUIRE(primeNums.size() == 0);
}

TEST_CASE("Top limit upper bound")
{
	std::set<int> primeNums = GeneratePrimeNumbersSet(100000000);

	REQUIRE(primeNums.size() == 5761455);
}

TEST_CASE("Standard upper bound")
{
	std::set<int> primeNums = GeneratePrimeNumbersSet(5);

	REQUIRE(primeNums.size() == 2);
}
