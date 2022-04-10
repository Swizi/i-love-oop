#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp";
#include "../html_functions.h";

TEST_CASE("Empty")
{
	std::istringstream iss("");
	std::ostringstream oss;

	Decode(iss, oss);
	REQUIRE(oss.str().empty());
}

TEST_CASE("Standard")
{
	std::istringstream iss("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
	std::ostringstream oss;

	Decode(iss, oss);

	REQUIRE(oss.str() == "Cat <says> \"Meow\". M&M's\n");
}