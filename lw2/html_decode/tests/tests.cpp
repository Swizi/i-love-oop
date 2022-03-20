#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp";
#include "../html_functions.h";
#include "../string_functions.h";

TEST_CASE("Empty")
{
	std::istringstream iss("");
	std::ostringstream oss;

	decode(iss, oss);
	REQUIRE(oss.str().empty());
}

TEST_CASE("Standard")
{
	std::istringstream iss("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
	std::ostringstream oss;

	decode(iss, oss);

	REQUIRE(oss.str() == "Cat <says> \"Meow\". M&M's\n");
}