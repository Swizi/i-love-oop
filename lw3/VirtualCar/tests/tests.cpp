#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Car.h"

// Машина выключена, но хотим скорость засеттить
// WHEN GIVEN THEN
// end-to-end tests, unit tests разделить

SCENARIO("Initial information about the car")
{
	GIVEN("A car")
	{
		CCar car = CCar();
		std::string errorMsg = "";

		WHEN("Engine is off")
		{
			car.TurnOffEngine(errorMsg);

			THEN("gear, speed and direction should have initial values")
			{
				REQUIRE(car.GetGear() == 0);
				REQUIRE(car.GetSpeed() == 0);
				REQUIRE(car.GetDirection == Direction::None);
			}
		}

		WHEN("Engine is on")
		{
			car.TurnOnEngine();

			THEN("gear, speed and direction should have initial values")
			{
				REQUIRE(car.GetGear() == 0);
				REQUIRE(car.GetSpeed() == 0);
				REQUIRE(car.GetDirection == Direction::None);
			}
		}
	}
}

SCENARIO("Car can change gear")
{
	GIVEN("Turned on car")
	{
		CCar car = CCar();
		car.TurnOnEngine();

		WHEN("Gear is reverse")
		{
			std::string errorMsg = "";
			car.SetGear(-1, errorMsg);

			WHEN("Speed is 0")
			{
				THEN("Car can change gear to reverse, neutral, first")
				{
					std::vector<std::string> errorMsgs = { "", "", "" };

					car.SetGear(-1, errorMsgs[0]);
					car.SetGear(0, errorMsgs[1]);
					car.SetGear(1, errorMsgs[2]);

					INFO("Car can not change gear to reverse");
					REQUIRE(errorMsgs[0] == "");
					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[1] == "");
					INFO("Car can not change gear to first");
					REQUIRE(errorMsgs[2] == "");
				}

				THEN("Car can not change gear to second, third, fourth, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "" };

					car.SetGear(2, errorMsgs[0]);
					car.SetGear(3, errorMsgs[1]);
					car.SetGear(4, errorMsgs[2]);
					car.SetGear(5, errorMsgs[3]);

					INFO("Car can change gear to second");
					REQUIRE(errorMsgs[0] != "");
					INFO("Car can change gear to third");
					REQUIRE(errorMsgs[1] != "");
					INFO("Car can change gear to fourth");
					REQUIRE(errorMsgs[2] != "");
					INFO("Car can change gear to fifth");
					REQUIRE(errorMsgs[3] != "");
				}
			}

			WHEN("Speed is not 0")
			{
				std::string errorMsg = "";
				car.SetSpeed(5, errorMsg);

				THEN("Car can change gear to reverse, neutral")
				{
					std::vector<std::string> errorMsgs = { "", "" };

					car.SetGear(-1, errorMsgs[0]);
					car.SetGear(0, errorMsgs[1]);

					INFO("Car can not change gear to reverse");
					REQUIRE(errorMsgs[0] == "");
					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[1] == "");
				}

				THEN("Car can not change gear to first, second, third, fourth, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "", "" };

					car.SetGear(1, errorMsgs[0]);
					car.SetGear(2, errorMsgs[1]);
					car.SetGear(3, errorMsgs[2]);
					car.SetGear(4, errorMsgs[3]);
					car.SetGear(5, errorMsgs[4]);

					INFO("Car can change gear to first");
					REQUIRE(errorMsgs[0] != "");
					INFO("Car can change gear to second");
					REQUIRE(errorMsgs[1] != "");
					INFO("Car can change gear to third");
					REQUIRE(errorMsgs[2] != "");
					INFO("Car can change gear to fourth");
					REQUIRE(errorMsgs[3] != "");
					INFO("Car can change gear to fifth");
					REQUIRE(errorMsgs[4] != "");
				}
			}
		}

		WHEN("Gear is neutral")
		{
			WHEN("Speed is 0")
			{
				THEN("Car can change gear to reverse, neutral, first")
				{
					std::vector<std::string> errorMsgs = { "", "", "" };

					car.SetGear(-1, errorMsgs[0]);
					car.SetGear(0, errorMsgs[1]);
					car.SetGear(1, errorMsgs[2]);

					INFO("Car can not change gear to reverse");
					REQUIRE(errorMsgs[0] == "");
					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[1] == "");
					INFO("Car can not change gear to first");
					REQUIRE(errorMsgs[2] == "");
				}

				THEN("Car can not change gear to second, third, fourth, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "" };

					car.SetGear(2, errorMsgs[0]);
					car.SetGear(3, errorMsgs[1]);
					car.SetGear(4, errorMsgs[2]);
					car.SetGear(5, errorMsgs[3]);

					INFO("Car can change gear to second");
					REQUIRE(errorMsgs[0] != "");
					INFO("Car can change gear to third");
					REQUIRE(errorMsgs[1] != "");
					INFO("Car can change gear to fourth");
					REQUIRE(errorMsgs[2] != "");
					INFO("Car can change gear to fifth");
					REQUIRE(errorMsgs[3] != "");
				}
			}

			WHEN("Speed is not 0")
			{
				std::string errorMsg = "";
				car.SetSpeed(5, errorMsg);

				THEN("Car can change gear to neutral, first")
				{
					std::vector<std::string> errorMsgs = { "", "" };

					car.SetGear(0, errorMsgs[0]);
					car.SetGear(1, errorMsgs[1]);

					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[0] == "");
					INFO("Car can not change gear to first");
					REQUIRE(errorMsgs[1] == "");
				}

				THEN("Car can not change gear to reverse, second, third, fourth, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "", "" };

					car.SetGear(-1, errorMsgs[0]);
					car.SetGear(2, errorMsgs[1]);
					car.SetGear(3, errorMsgs[2]);
					car.SetGear(4, errorMsgs[3]);
					car.SetGear(5, errorMsgs[4]);

					INFO("Car can change gear to reverse");
					REQUIRE(errorMsgs[0] != "");
					INFO("Car can change gear to second");
					REQUIRE(errorMsgs[1] != "");
					INFO("Car can change gear to third");
					REQUIRE(errorMsgs[2] != "");
					INFO("Car can change gear to fourth");
					REQUIRE(errorMsgs[3] != "");
					INFO("Car can change gear to fifth");
					REQUIRE(errorMsgs[4] != "");
				}
			}
		}

		WHEN("Gear is first")
		{
			std::string errorMsg = "";
			car.SetGear(1, errorMsg);

			WHEN("Speed is 0")
			{
				THEN("Car can change gear to reverse, neutral, first")
				{
					std::vector<std::string> errorMsgs = { "", "", "" };

					car.SetGear(-1, errorMsgs[0]);
					car.SetGear(0, errorMsgs[1]);
					car.SetGear(1, errorMsgs[2]);

					INFO("Car can not change gear to reverse");
					REQUIRE(errorMsgs[0] == "");
					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[1] == "");
					INFO("Car can not change gear to first");
					REQUIRE(errorMsgs[2] == "");
				}

				THEN("Car can not change gear to second, third, fourth, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "" };

					car.SetGear(2, errorMsgs[0]);
					car.SetGear(3, errorMsgs[1]);
					car.SetGear(4, errorMsgs[2]);
					car.SetGear(5, errorMsgs[3]);

					INFO("Car can change gear to second");
					REQUIRE(errorMsgs[0] != "");
					INFO("Car can change gear to third");
					REQUIRE(errorMsgs[1] != "");
					INFO("Car can change gear to fourth");
					REQUIRE(errorMsgs[2] != "");
					INFO("Car can change gear to fifth");
					REQUIRE(errorMsgs[3] != "");
				}
			}

			WHEN("Speed is not 0")
			{
				THEN("Car can change gear to neutral, first")
				{
					std::vector<std::string> errorMsgs = { "", "" };

					car.SetGear(0, errorMsgs[0]);
					car.SetGear(1, errorMsgs[1]);

					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[0] == "");
					INFO("Car can not change gear to first");
					REQUIRE(errorMsgs[1] == "");
				}

				THEN("Car can not change gear to reverse, second, third, fourth, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "", "" };

					car.SetGear(-1, errorMsgs[0]);
					car.SetGear(2, errorMsgs[1]);
					car.SetGear(3, errorMsgs[2]);
					car.SetGear(4, errorMsgs[3]);
					car.SetGear(5, errorMsgs[4]);

					INFO("Car can change gear to reverse");
					REQUIRE(errorMsgs[0] != "");
					INFO("Car can change gear to second");
					REQUIRE(errorMsgs[1] != "");
					INFO("Car can change gear to third");
					REQUIRE(errorMsgs[2] != "");
					INFO("Car can change gear to fourth");
					REQUIRE(errorMsgs[3] != "");
					INFO("Car can change gear to fifth");
					REQUIRE(errorMsgs[4] != "");
				}
			}
		}

		WHEN("Gear is second")
		{

		}
	}
}