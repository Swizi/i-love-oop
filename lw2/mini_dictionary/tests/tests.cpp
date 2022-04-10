#define CATCH_CONFIG_MAIN
#include <sstream>
#include "../../../Catch2/catch.hpp"
#include "../dict.h"

TEST_CASE("Test lowercase strings")
{
	REQUIRE(GetLowercasedString("ABC") == "abc");
	REQUIRE(GetLowercasedString("123") == "123");
	REQUIRE(GetLowercasedString("АБВ") == "абв");
	REQUIRE(GetLowercasedString("a") == "a");
}

TEST_CASE("Check empty dictionary")
{
   std::map<std::string, std::vector<std::string>> dict = {};

	REQUIRE(HasTranslation(dict, "snow") == false);
}

TEST_CASE("Check not empty dictionary")
{
	std::map<std::string, std::vector<std::string>> dict = {};
	std::vector<std::string> translation = { "snow", "снег" };

	AppendTranslation(dict, translation);

	REQUIRE(HasTranslation(dict, "snow") == true);
}

TEST_CASE("Check translation existing")
{
	std::map<std::string, std::vector<std::string>> dict = {};
	std::vector<std::string> translation = { "snow", "снег" };

	AppendTranslation(dict, translation);

	REQUIRE(dict["snow"][0] == "снег");
	REQUIRE(dict["снег"][0] == "snow");
}

TEST_CASE("Check translation output")
{
	std::map<std::string, std::vector<std::string>> dict = {};
	std::vector<std::string> snow_translation = { "snow", "снег" };
	AppendTranslation(dict, snow_translation);
	std::vector<std::string> female_cat_translation = { "cat", "кошка" };
	std::vector<std::string> male_cat_translation = { "cat", "кот" };
	AppendTranslation(dict, female_cat_translation);
	AppendTranslation(dict, male_cat_translation);

	std::ostringstream oss_snow;
	PrintTranslation(dict["snow"], oss_snow);
	std::ostringstream oss_cat;
	PrintTranslation(dict["cat"], oss_cat);

	REQUIRE(oss_snow.str() == "снег\n");
	REQUIRE(oss_cat.str() == "кошка, кот\n");
}