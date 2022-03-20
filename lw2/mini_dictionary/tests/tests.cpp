#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include <sstream>
#include "../dict.h"

TEST_CASE("Test lowercase strings")
{
	REQUIRE(get_lowercased_string("ABC") == "abc");
	REQUIRE(get_lowercased_string("123") == "123");
	REQUIRE(get_lowercased_string("a") == "a");
}

TEST_CASE("Has translation check")
{
	std::map<std::string, std::vector<std::string>> dict = {};
	std::string word = "snow";

	REQUIRE(has_translation(dict, word) == false);
	dict[word] = { "снег" };
	REQUIRE(has_translation(dict, word) == true);
}

TEST_CASE("Append translation check")
{
	std::map<std::string, std::vector<std::string>> dict = {};
	std::vector<std::string> translation = { "snow", "снег" };

	append_translation(dict, translation);

	REQUIRE(dict["snow"][0] == "снег");
	REQUIRE(dict["снег"][0] == "snow");
}

TEST_CASE("Print translation check")
{
	std::map<std::string, std::vector<std::string>> dict = {};
	std::vector<std::string> snow_translation = { "snow", "снег" };
	append_translation(dict, snow_translation);

	std::ostringstream oss_snow;
	print_translation(dict["snow"], oss_snow);
	REQUIRE(oss_snow.str() == "снег");

	std::vector<std::string> female_cat_translation = { "cat", "кошка" };
	std::vector<std::string> male_cat_translation = { "cat", "кот" };
	append_translation(dict, female_cat_translation);
	append_translation(dict, male_cat_translation);

	std::ostringstream oss_cat;
	print_translation(dict["cat"], oss_cat);

	REQUIRE(oss_cat.str() == "кошка, кот");
}