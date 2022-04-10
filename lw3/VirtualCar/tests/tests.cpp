#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../CCar.h"

TEST_CASE("Min boundary speed")
{
	CCar car = CCar();
	std::string errorMsg = "";

	car.TurnOnEngine();
	car.SetGear(-1, errorMsg);
	car.SetSpeed(0, errorMsg);

	REQUIRE(errorMsg == "");
}

TEST_CASE("Max boundary speed")
{
	CCar car = CCar();
	std::string errorMsg = "";

	car.TurnOnEngine();
	car.SetGear(1, errorMsg);
	car.SetSpeed(30, errorMsg);
	car.SetGear(2, errorMsg);
	car.SetSpeed(50, errorMsg);
	car.SetGear(3, errorMsg);
	car.SetSpeed(60, errorMsg);
	car.SetGear(4, errorMsg);
	car.SetSpeed(90, errorMsg);
	car.SetGear(5, errorMsg);
	car.SetSpeed(150, errorMsg);

	REQUIRE(errorMsg == "");
}

TEST_CASE("Invalid speed")
{
	CCar car = CCar();
	std::string errorMsg = "";

	car.TurnOnEngine();
	car.SetSpeed(151, errorMsg);

	REQUIRE(errorMsg == "Speed should be in 0 .. 150");
}

TEST_CASE("Driving to job")
{
	CCar car = CCar();
	std::string errorMsg = "";

	car.TurnOnEngine();
	car.SetGear(1, errorMsg);
	car.SetSpeed(20, errorMsg);
	car.SetGear(2, errorMsg);
	car.SetSpeed(50, errorMsg);
	car.SetGear(3, errorMsg);
	car.SetSpeed(60, errorMsg);
	car.SetGear(0, errorMsg);
	car.SetSpeed(0, errorMsg);
	car.TurnOffEngine();

	REQUIRE(errorMsg == "");
}

TEST_CASE("Parking")
{
	CCar car = CCar();
	std::string errorMsg = "";

	car.TurnOnEngine();
	car.SetGear(-1, errorMsg);
	car.SetSpeed(-5, errorMsg);
	car.SetGear(0, errorMsg);
	car.SetSpeed(5, errorMsg);
	car.SetSpeed(-5, errorMsg);
	car.TurnOffEngine();

	REQUIRE(errorMsg == "");
}

TEST_CASE("Racing")
{
	CCar car = CCar();
	std::string errorMsg = "";

	car.TurnOnEngine();
	car.SetGear(1, errorMsg);
	car.SetSpeed(30, errorMsg);
	car.SetGear(2, errorMsg);
	car.SetSpeed(50, errorMsg);
	car.SetGear(3, errorMsg);
	car.SetSpeed(60, errorMsg);
	car.SetGear(4, errorMsg);
	car.SetSpeed(90, errorMsg);
	car.SetGear(5, errorMsg);
	car.SetSpeed(150, errorMsg);
	car.SetSpeed(60, errorMsg);
	car.SetSpeed(100, errorMsg);
	car.SetSpeed(120, errorMsg);
	car.SetSpeed(50, errorMsg);
	car.SetGear(4, errorMsg);
	car.SetSpeed(40, errorMsg);
	car.SetGear(3, errorMsg);
	car.SetSpeed(30, errorMsg);
	car.SetGear(2, errorMsg);
	car.SetSpeed(20, errorMsg);
	car.SetGear(1, errorMsg);
	car.SetSpeed(0, errorMsg);
	car.SetGear(0, errorMsg);
	car.TurnOffEngine();

	REQUIRE(errorMsg == "");
}