#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Car.h"

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
				REQUIRE(car.GetDirection() == Direction::None);
			}
		}

		WHEN("Engine is on")
		{
			car.TurnOnEngine();

			THEN("gear, speed and direction should have initial values")
			{
				REQUIRE(car.GetGear() == 0);
				REQUIRE(car.GetSpeed() == 0);
				REQUIRE(car.GetDirection() == Direction::None);
			}
		}
	}
}

SCENARIO("Car can be turned on and off")
{
	GIVEN("A car with turned off engine")
	{
		CCar car = CCar();
		REQUIRE(!car.IsTurnedOn());

		WHEN("Car engine turned on")
		{
			car.TurnOnEngine();

			THEN("Car engine becomes turned on")
			{
				REQUIRE(car.IsTurnedOn());
			}
		}

		WHEN("Car engine turned off")
		{
			std::string errorMsg = "";
			car.TurnOffEngine(errorMsg);

			THEN("Car engine becomes turned off")
			{
				REQUIRE(errorMsg.empty());
				REQUIRE(!car.IsTurnedOn());
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

		WHEN("Reversed gear")
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
					REQUIRE(errorMsgs[0].empty());
					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[1].empty());
					INFO("Car can not change gear to first");
					REQUIRE(errorMsgs[2].empty());
				}

				THEN("Car can not change gear to second, third, fourth, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "" };

					car.SetGear(2, errorMsgs[0]);
					car.SetGear(3, errorMsgs[1]);
					car.SetGear(4, errorMsgs[2]);
					car.SetGear(5, errorMsgs[3]);

					INFO("Car can change gear to second");
					REQUIRE(!errorMsgs[0].empty());
					INFO("Car can change gear to third");
					REQUIRE(!errorMsgs[1].empty());
					INFO("Car can change gear to fourth");
					REQUIRE(!errorMsgs[2].empty());
					INFO("Car can change gear to fifth");
					REQUIRE(!errorMsgs[3].empty());
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
					REQUIRE(errorMsgs[0].empty());
					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[1].empty());
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
					REQUIRE(!errorMsgs[0].empty());
					INFO("Car can change gear to second");
					REQUIRE(!errorMsgs[1].empty());
					INFO("Car can change gear to third");
					REQUIRE(!errorMsgs[2].empty());
					INFO("Car can change gear to fourth");
					REQUIRE(!errorMsgs[3].empty());
					INFO("Car can change gear to fifth");
					REQUIRE(!errorMsgs[4].empty());
				}
			}
		}

		WHEN("Neutral gear")
		{
			std::string errorMsg = "";
			car.SetGear(0, errorMsg);

			WHEN("Speed is 0")
			{
				THEN("Car can change gear to reverse, neutral, first")
				{
					std::vector<std::string> errorMsgs = { "", "", "" };

					car.SetGear(-1, errorMsgs[0]);
					car.SetGear(0, errorMsgs[1]);
					car.SetGear(1, errorMsgs[2]);

					INFO("Car can not change gear to reverse");
					REQUIRE(errorMsgs[0].empty());
					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[1].empty());
					INFO("Car can not change gear to first");
					REQUIRE(errorMsgs[2].empty());
				}

				THEN("Car can not change gear to second, third, fourth, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "" };

					car.SetGear(2, errorMsgs[0]);
					car.SetGear(3, errorMsgs[1]);
					car.SetGear(4, errorMsgs[2]);
					car.SetGear(5, errorMsgs[3]);

					INFO("Car can change gear to second");
					REQUIRE(!errorMsgs[0].empty());
					INFO("Car can change gear to third");
					REQUIRE(!errorMsgs[1].empty());
					INFO("Car can change gear to fourth");
					REQUIRE(!errorMsgs[2].empty());
					INFO("Car can change gear to fifth");
					REQUIRE(!errorMsgs[3].empty());
				}
			}

			WHEN("Speed is not 0")
			{
				WHEN("Speed is 1 .. 20")
				{
					std::string errorMsg = "";
					car.SetSpeed(5, errorMsg);

					THEN("Car can change gear to neutral, first")
					{
						std::vector<std::string> errorMsgs = { "", "" };

						car.SetGear(0, errorMsgs[0]);
						car.SetGear(1, errorMsgs[1]);

						INFO("Car can not change gear to neutral");
						REQUIRE(errorMsgs[0].empty());
						INFO("Car can not change gear to first");
						REQUIRE(errorMsgs[1].empty());
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
						REQUIRE(!errorMsgs[0].empty());
						INFO("Car can change gear to second");
						REQUIRE(!errorMsgs[1].empty());
						INFO("Car can change gear to third");
						REQUIRE(!errorMsgs[2].empty());
						INFO("Car can change gear to fourth");
						REQUIRE(!errorMsgs[3].empty());
						INFO("Car can change gear to fifth");
						REQUIRE(!errorMsgs[4].empty());
					}
				}

				WHEN("Speed is 20 .. 30")
				{
				}

				WHEN("Speed is 30 .. 50")
				{
				}

				WHEN("Speed is 40 .. 60")
				{
				}

				WHEN("Speed is 50 .. 90")
				{
				}

				WHEN("Speed is 90 .. 150")
				{
				}
			}
		}

		WHEN("First gear")
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
					REQUIRE(errorMsgs[0].empty());
					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[1].empty());
					INFO("Car can not change gear to first");
					REQUIRE(errorMsgs[2].empty());
				}

				THEN("Car can not change gear to second, third, fourth, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "" };

					car.SetGear(2, errorMsgs[0]);
					car.SetGear(3, errorMsgs[1]);
					car.SetGear(4, errorMsgs[2]);
					car.SetGear(5, errorMsgs[3]);

					INFO("Car can change gear to second");
					REQUIRE(!errorMsgs[0].empty());
					INFO("Car can change gear to third");
					REQUIRE(!errorMsgs[1].empty());
					INFO("Car can change gear to fourth");
					REQUIRE(!errorMsgs[2].empty());
					INFO("Car can change gear to fifth");
					REQUIRE(!errorMsgs[3].empty());
				}
			}

			WHEN("Speed is not 0")
			{
				WHEN("Speed is [1 .. 20)")
				{
					std::string errorMsg = "";
					car.SetSpeed(5, errorMsg);

					THEN("Car can change gear to neutral, first")
					{
						std::vector<std::string> errorMsgs = { "", "" };

						car.SetGear(0, errorMsgs[0]);
						car.SetGear(1, errorMsgs[1]);

						INFO("Car can not change gear to neutral");
						REQUIRE(errorMsgs[0].empty());
						INFO("Car can not change gear to first");
						REQUIRE(errorMsgs[1].empty());
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
						REQUIRE(!errorMsgs[0].empty());
						INFO("Car can change gear to second");
						REQUIRE(!errorMsgs[1].empty());
						INFO("Car can change gear to third");
						REQUIRE(!errorMsgs[2].empty());
						INFO("Car can change gear to fourth");
						REQUIRE(!errorMsgs[3].empty());
						INFO("Car can change gear to fifth");
						REQUIRE(!errorMsgs[4].empty());
					}
				}

				WHEN("Speed is [20 .. 30)")
				{
					std::string errorMsg = "";
					car.SetSpeed(25, errorMsg);

					THEN("Car can change gear to neutral, first, second")
					{
						std::vector<std::string> errorMsgs = { "", "", "" };

						car.SetGear(0, errorMsgs[0]);
						car.SetGear(1, errorMsgs[1]);
						car.SetGear(2, errorMsgs[2]);

						INFO("Car can not change gear to neutral");
						REQUIRE(errorMsgs[0].empty());
						INFO("Car can not change gear to first");
						REQUIRE(errorMsgs[1].empty());
						INFO("Car can not change gear to second");
						REQUIRE(errorMsgs[2].empty());
					}

					THEN("Car can not change gear to reverse, third, fourth, fifth")
					{
						std::vector<std::string> errorMsgs = { "", "", "", "" };

						car.SetGear(-1, errorMsgs[0]);
						car.SetGear(3, errorMsgs[1]);
						car.SetGear(4, errorMsgs[2]);
						car.SetGear(5, errorMsgs[3]);

						INFO("Car can change gear to reverse");
						REQUIRE(!errorMsgs[0].empty());
						INFO("Car can change gear to third");
						REQUIRE(!errorMsgs[1].empty());
						INFO("Car can change gear to fourth");
						REQUIRE(!errorMsgs[2].empty());
						INFO("Car can change gear to fifth");
						REQUIRE(!errorMsgs[3].empty());
					}
				}
			}
		}

		WHEN("Second gear")
		{
			std::string errorMsg = "";
			car.SetGear(1, errorMsg);
			car.SetSpeed(20, errorMsg);
			car.SetGear(2, errorMsg);

			WHEN("Speed is [20 .. 30)")
			{
				std::string errorMsg = "";
				car.SetSpeed(25, errorMsg);

				THEN("Car can change gear to neutral, first, second")
				{
					std::vector<std::string> errorMsgs = { "", "", "" };

					car.SetGear(0, errorMsgs[0]);
					car.SetGear(1, errorMsgs[1]);
					car.SetGear(2, errorMsgs[2]);

					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[0].empty());
					INFO("Car can not change gear to first");
					REQUIRE(errorMsgs[1].empty());
					INFO("Car can not change gear to second");
					REQUIRE(errorMsgs[2].empty());
				}

				THEN("Car can not change gear to reverse, third, fourth, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "" };

					car.SetGear(-1, errorMsgs[0]);
					car.SetGear(3, errorMsgs[1]);
					car.SetGear(4, errorMsgs[2]);
					car.SetGear(5, errorMsgs[3]);

					INFO("Car can change gear to reverse");
					REQUIRE(!errorMsgs[0].empty());
					INFO("Car can change gear to third");
					REQUIRE(!errorMsgs[1].empty());
					INFO("Car can change gear to fourth");
					REQUIRE(!errorMsgs[2].empty());
					INFO("Car can change gear to fifth");
					REQUIRE(!errorMsgs[3].empty());
				}
			}

			WHEN("Speed is [30 .. 50)")
			{
				std::string errorMsg = "";
				car.SetSpeed(45, errorMsg);

				THEN("Car can change gear to neutral, second, third")
				{
					std::vector<std::string> errorMsgs = { "", "", "" };

					car.SetGear(0, errorMsgs[0]);
					car.SetGear(2, errorMsgs[1]);
					car.SetGear(3, errorMsgs[2]);

					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[0].empty());
					INFO("Car can not change gear to second");
					REQUIRE(errorMsgs[1].empty());
					INFO("Car can not change gear to third");
					REQUIRE(errorMsgs[2].empty());
				}

				THEN("Car can not change gear to reverse, first, fourth, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "" };

					car.SetGear(-1, errorMsgs[0]);
					car.SetGear(1, errorMsgs[1]);
					car.SetGear(4, errorMsgs[2]);
					car.SetGear(5, errorMsgs[3]);

					{
						INFO("Car can change gear to reverse");
						REQUIRE(!errorMsgs[0].empty());
					}
					{
						INFO("Car can change gear to first");
						REQUIRE(!errorMsgs[1].empty());
					}
					{
						INFO("Car can change gear to fourth");
						REQUIRE(!errorMsgs[2].empty());
					}
					{
						INFO("Car can change gear to fifth");
						REQUIRE(!errorMsgs[3].empty());
					}
				}
			}
		}

		WHEN("Third gear")
		{
			WHEN("Speed is [30 .. 40)")
			{
				std::string errorMsg = "";
				car.SetSpeed(35, errorMsg);

				THEN("Car can change gear to neutral, second, third")
				{
					std::vector<std::string> errorMsgs = { "", "", "" };

					car.SetGear(0, errorMsgs[0]);
					car.SetGear(2, errorMsgs[1]);
					car.SetGear(3, errorMsgs[2]);

					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[0].empty());
					INFO("Car can not change gear to second");
					REQUIRE(errorMsgs[1].empty());
					INFO("Car can not change gear to third");
					REQUIRE(errorMsgs[2].empty());
				}

				THEN("Car can not change gear to reverse, first, fourth, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "" };

					car.SetGear(-1, errorMsgs[0]);
					car.SetGear(1, errorMsgs[1]);
					car.SetGear(4, errorMsgs[2]);
					car.SetGear(5, errorMsgs[3]);

					INFO("Car can change gear to reverse");
					REQUIRE(!errorMsgs[0].empty());
					INFO("Car can change gear to first");
					REQUIRE(!errorMsgs[1].empty());
					INFO("Car can change gear to fourth");
					REQUIRE(!errorMsgs[2].empty());
					INFO("Car can change gear to fifth");
					REQUIRE(!errorMsgs[3].empty());
				}
			}

			WHEN("Speed is [40 .. 50)")
			{
				std::string errorMsg = "";
				car.SetSpeed(45, errorMsg);

				THEN("Car can change gear to neutral, second, third, fourth")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "" };

					car.SetGear(0, errorMsgs[0]);
					car.SetGear(2, errorMsgs[1]);
					car.SetGear(3, errorMsgs[2]);
					car.SetGear(4, errorMsgs[3]);

					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[0].empty());
					INFO("Car can not change gear to first");
					REQUIRE(errorMsgs[1].empty());
					INFO("Car can not change gear to second");
					REQUIRE(errorMsgs[2].empty());
					INFO("Car can not change gear to fo")
				}

				THEN("Car can not change gear to reverse, first, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "" };

					car.SetGear(-1, errorMsgs[0]);
					car.SetGear(1, errorMsgs[1]);
					car.SetGear(5, errorMsgs[2]);

					INFO("Car can change gear to reverse");
					REQUIRE(!errorMsgs[0].empty());
					INFO("Car can change gear to first");
					REQUIRE(!errorMsgs[1].empty());
					INFO("Car can change gear to fifth");
					REQUIRE(!errorMsgs[2].empty());
				}
			}

			WHEN("Speed is [50 .. 60)")
			{
				std::string errorMsg = "";
				car.SetSpeed(55, errorMsg);

				THEN("Car can change gear to neutral, third, fourth")
				{
					std::vector<std::string> errorMsgs = { "", "", "" };

					car.SetGear(0, errorMsgs[0]);
					car.SetGear(3, errorMsgs[1]);
					car.SetGear(4, errorMsgs[2]);

					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[0].empty());
					INFO("Car can not change gear to third");
					REQUIRE(errorMsgs[1].empty());
					INFO("Car can not change gear to fourth");
					REQUIRE(errorMsgs[2].empty());
				}

				THEN("Car can not change gear to reverse, first, second, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "" };

					car.SetGear(-1, errorMsgs[0]);
					car.SetGear(1, errorMsgs[1]);
					car.SetGear(2, errorMsgs[2]);
					car.SetGear(5, errorMsgs[3]);

					INFO("Car can change gear to reverse");
					REQUIRE(!errorMsgs[0].empty());
					INFO("Car can change gear to first");
					REQUIRE(!errorMsgs[1].empty());
					INFO("Car can change gear to second");
					REQUIRE(!errorMsgs[2].empty());
					INFO("Car can change gear to fifth");
					REQUIRE(!errorMsgs[3].empty());
				}
			}
		}

		WHEN("Fourth gear")
		{
			WHEN("Speed is [40 .. 50)")
			{
				std::string errorMsg = "";
				car.SetSpeed(45, errorMsg);

				THEN("Car can change gear to neutral, third, fourth")
				{
					std::vector<std::string> errorMsgs = { "", "", "" };

					car.SetGear(0, errorMsgs[0]);
					car.SetGear(3, errorMsgs[1]);
					car.SetGear(4, errorMsgs[2]);

					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[0].empty());
					INFO("Car can not change gear to third");
					REQUIRE(errorMsgs[1].empty());
					INFO("Car can not change gear to fourth");
					REQUIRE(errorMsgs[2].empty());
				}

				THEN("Car can not change gear to reverse, first, second, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "" };

					car.SetGear(-1, errorMsgs[0]);
					car.SetGear(1, errorMsgs[1]);
					car.SetGear(2, errorMsgs[2]);
					car.SetGear(5, errorMsgs[3]);

					INFO("Car can change gear to reverse");
					REQUIRE(!errorMsgs[0].empty());
					INFO("Car can change gear to first");
					REQUIRE(!errorMsgs[1].empty());
					INFO("Car can change gear to second");
					REQUIRE(!errorMsgs[2].empty());
					INFO("Car can change gear to fifth");
					REQUIRE(!errorMsgs[2].empty());
				}
			}

			WHEN("Speed is [50 .. 60)")
			{
				std::string errorMsg = "";
				car.SetSpeed(55, errorMsg);

				THEN("Car can change gear to neutral, third, fourth, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "" };

					car.SetGear(0, errorMsgs[0]);
					car.SetGear(3, errorMsgs[1]);
					car.SetGear(4, errorMsgs[2]);
					car.SetGear(5, errorMsgs[3]);

					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[0].empty());
					INFO("Car can not change gear to third");
					REQUIRE(errorMsgs[1].empty());
					INFO("Car can not change gear to fourth");
					REQUIRE(errorMsgs[2].empty());
					INFO("Car can not change gear to fifth");
					REQUIRE(errorMsgs[3].empty());
				}

				THEN("Car can not change gear to reverse, first, second")
				{
					std::vector<std::string> errorMsgs = { "", "", "" };

					car.SetGear(-1, errorMsgs[0]);
					car.SetGear(1, errorMsgs[1]);
					car.SetGear(2, errorMsgs[2]);

					INFO("Car can change gear to reverse");
					REQUIRE(!errorMsgs[0].empty());
					INFO("Car can change gear to first");
					REQUIRE(!errorMsgs[1].empty());
					INFO("Car can change gear to second");
					REQUIRE(!errorMsgs[2].empty());
				}
			}

			WHEN("Speed is [60 .. 90)")
			{
				std::string errorMsg = "";
				car.SetSpeed(65, errorMsg);

				THEN("Car can change gear to neutral, fourth, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "" };

					car.SetGear(0, errorMsgs[0]);
					car.SetGear(4, errorMsgs[1]);
					car.SetGear(5, errorMsgs[2]);

					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[0].empty());
					INFO("Car can not change gear to fourth");
					REQUIRE(errorMsgs[1].empty());
					INFO("Car can not change gear to fifth");
					REQUIRE(errorMsgs[2].empty());
				}

				THEN("Car can not change gear to reverse, first, second, third")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "" };

					car.SetGear(-1, errorMsgs[0]);
					car.SetGear(1, errorMsgs[1]);
					car.SetGear(2, errorMsgs[2]);
					car.SetGear(3, errorMsgs[3]);

					INFO("Car can change gear to reverse");
					REQUIRE(!errorMsgs[0].empty());
					INFO("Car can change gear to first");
					REQUIRE(!errorMsgs[1].empty());
					INFO("Car can change gear to second");
					REQUIRE(!errorMsgs[2].empty());
					INFO("Car can change gear to third");
					REQUIRE(!errorMsgs[3].empty());
				}
			}
		}

		WHEN("Fifth gear")
		{
			WHEN("Speed is [50 .. 90)")
			{
				std::string errorMsg = "";
				car.SetSpeed(65, errorMsg);

				THEN("Car can change gear to neutral, fourth, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "" };

					car.SetGear(0, errorMsgs[0]);
					car.SetGear(4, errorMsgs[1]);
					car.SetGear(5, errorMsgs[2]);

					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[0].empty());
					INFO("Car can not change gear to fourth");
					REQUIRE(errorMsgs[1].empty());
					INFO("Car can not change gear to fifth");
					REQUIRE(errorMsgs[2].empty());
				}

				THEN("Car can not change gear to reverse, first, second, third")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "" };

					car.SetGear(-1, errorMsgs[0]);
					car.SetGear(1, errorMsgs[1]);
					car.SetGear(2, errorMsgs[2]);
					car.SetGear(3, errorMsgs[3]);

					INFO("Car can change gear to reverse");
					REQUIRE(!errorMsgs[0].empty());
					INFO("Car can change gear to first");
					REQUIRE(!errorMsgs[1].empty());
					INFO("Car can change gear to second");
					REQUIRE(!errorMsgs[2].empty());
					INFO("Car can change gear to third");
					REQUIRE(!errorMsgs[3].empty());
				}
			}

			WHEN("Speed is [90 .. 150)")
			{
				std::string errorMsg = "";
				car.SetSpeed(65, errorMsg);

				THEN("Car can change gear to neutral, fifth")
				{
					std::vector<std::string> errorMsgs = { "", "", "" };

					car.SetGear(0, errorMsgs[0]);
					car.SetGear(4, errorMsgs[1]);
					car.SetGear(5, errorMsgs[2]);

					INFO("Car can not change gear to neutral");
					REQUIRE(errorMsgs[0].empty());
					INFO("Car can not change gear to fourth");
					REQUIRE(errorMsgs[1].empty());
					INFO("Car can not change gear to fifth");
					REQUIRE(errorMsgs[2].empty());
				}

				THEN("Car can not change gear to reverse, first, second, third, fourth")
				{
					std::vector<std::string> errorMsgs = { "", "", "", "", "" };

					car.SetGear(-1, errorMsgs[0]);
					car.SetGear(1, errorMsgs[1]);
					car.SetGear(2, errorMsgs[2]);
					car.SetGear(3, errorMsgs[3]);
					car.SetGear(4, errorMsgs[4]);

					INFO("Car can change gear to reverse");
					REQUIRE(!errorMsgs[0].empty());
					INFO("Car can change gear to first");
					REQUIRE(!errorMsgs[1].empty());
					INFO("Car can change gear to second");
					REQUIRE(!errorMsgs[2].empty());
					INFO("Car can change gear to third");
					REQUIRE(!errorMsgs[3].empty());
					INFO("Car can change gear to fourth");
					REQUIRE(!errorMsgs[4].empty());
				}
			}
		}
	}
}

SCENARIO("Car can change speed")
{
	GIVEN("Turned on car")
	{
		WHEN("Gear is reverse")
		{
			THEN("Can change speed in 0 .. 20")
			{
			}
		}

		WHEN("Gear is neutral")
		{
			THEN("Can only reduce speed")
			{
			}
		}

		WHEN("Gear is first")
		{
			THEN("Can change speed in 0 .. 30")
			{
			}
		}

		WHEN("Gear is second")
		{
			THEN("Can change speed in 20 .. 50")
			{
			}
		}

		WHEN("Gear is third")
		{
			THEN("Can change speed in 30 .. 60")
			{
			}
		}

		WHEN("Gear is fourth")
		{
			THEN("Can change speed in 40 .. 90")
			{
			}
		}

		WHEN("Gear is fifth")
		{
			THEN("Can change speed in 50 .. 150")
			{
			}
		}
	}
}