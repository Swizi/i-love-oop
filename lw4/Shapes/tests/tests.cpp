#pragma once
#define CATCH_CONFIG_MAIN
#include "../common_libs.h"
#include "../../../Catch2/catch.hpp"
#include "../../../FakeIt/fakeit.hpp"
#include "../CController.h"
#include "../CLine.h"
#include "../CCircle.h"
#include "../CTriangle.h"
#include "../CRectangle.h"

// APPROX заменить
bool double_equals(double a, double b, double epsilon = 0.01)
{
	return std::abs(a - b) < epsilon;
}

// Standard tests
SCENARIO("Program has ability to create lines")
{
	GIVEN("A Line")
	{
		const CLine line = CLine({ 0, 0 }, { 50, 50 }, 0xfff);

		WHEN("Taking outline color")
		{
			THEN("Color should be 0xfff")
			{
				REQUIRE(line.GetOutlineColor() == 0xfff);
			}
		}

		WHEN("Taking specific data")
		{
			THEN("Data should be 'This is a line'")
			{
				REQUIRE(line.GetSpecifiedShapeData() == "This is a line\n");
			}
		}
	}

	GIVEN("A line with default outline color")
	{
		const CLine line = CLine({ 0, 0 }, { 50, 50 });

		WHEN("Taking outline color")
		{
			THEN("Color should be 0")
			{
				REQUIRE(line.GetOutlineColor() == 0);
			}
		}
	}
}

SCENARIO("Program has ability to create circles")
{
	GIVEN("A circle")
	{
		const CCircle circle = CCircle({ 20, 20 }, 30, 0xdddddd, 0xffffff);

		WHEN("Taking area")
		{
			THEN("It should return PI * 30^2")
			{
				REQUIRE(double_equals(circle.GetArea(), M_PI * 30 * 30));
			}
		}

		WHEN("Taking perimeter")
		{
			THEN("It should return 2 * PI * R")
			{
				REQUIRE(double_equals(circle.GetPerimeter(), 2 * M_PI * 30));
			}
		}

		WHEN("Taking outline color")
		{
			THEN("It should return 0xdddddd")
			{
				REQUIRE(circle.GetOutlineColor() == 0xdddddd);
			}
		}

		WHEN("Taking fill color")
		{
			THEN("It should return 0xffffff")
			{
				REQUIRE(circle.GetFillColor() == 0xffffff);
			}
		}
	}

	GIVEN("A circle with default colors")
	{
		const CCircle circle = CCircle({ 20, 20 }, 30);

		WHEN("Taking outline color")
		{
			THEN("It should return 0")
			{
				REQUIRE(circle.GetOutlineColor() == 0);
			}
		}

		WHEN("Taking fill color")
		{
			THEN("It should return 0xffffff")
			{
				REQUIRE(circle.GetFillColor() == 0xffffff);
			}
		}
	}
}

SCENARIO("Program has ability to create triangles")
{
	GIVEN("A triangle")
	{
		CPoint points[3];
		points[0] = { 0, 0 };
		points[1] = { 20, 20 };
		points[2] = { 30, 0 };
		const CTriangle triangle = CTriangle(points, 0xddd, 0xabc);

		WHEN("Taking area")
		{
			THEN("Area should be 300")
			{
				REQUIRE(double_equals(triangle.GetArea(), 300.0));
			}
		}

		WHEN("Taking perimeter")
		{
			THEN("Perimeter should be 80.64")
			{
				REQUIRE(double_equals(triangle.GetPerimeter(), 80.64));
			}
		}

		WHEN("Taking outline color")
		{
			THEN("Outline color should be 0xddd")
			{
				REQUIRE(triangle.GetOutlineColor() == 0xddd);
			}
		}

		WHEN("Taking fill color")
		{
			THEN("Fill color should be 0xabc")
			{
				REQUIRE(triangle.GetFillColor() == 0xabc);
			}
		}
	}

	GIVEN("A triangle with default colors")
	{
		CPoint points[3];
		points[0] = { 0, 0 };
		points[1] = { 20, 20 };
		points[2] = { 30, 0 };
		const CTriangle triangle = CTriangle(points);

		WHEN("Taking outline color")
		{
			THEN("Outline color should be 0")
			{
				REQUIRE(triangle.GetOutlineColor() == 0);
			}
		}

		WHEN("Taking fill color")
		{
			THEN("Fill color should be 0xfff")
			{
				REQUIRE(triangle.GetFillColor() == 0xffffff);
			}
		}
	}
}

SCENARIO("Program has ability to create rectangles")
{
	GIVEN("A rectangle")
	{
		const CRectangle rectangle = CRectangle({ 0, 0 }, 20, 30, 0xffffff, 0xffffff);

		WHEN("Taking an area")
		{
			THEN("It should return 600")
			{
				REQUIRE(double_equals(rectangle.GetArea(), 600));
			}
		}

		WHEN("Taking a perimeter")
		{
			THEN("It should return 100")
			{
				REQUIRE(double_equals(rectangle.GetPerimeter(), 100));
			}
		}

		WHEN("Taking an outline color")
		{
			THEN("It should return 0xffffff")
			{
				REQUIRE(rectangle.GetOutlineColor() == 0xffffff);
			}
		}

		WHEN("Taking a fill color")
		{
			THEN("It should return 0xffffff")
			{
				REQUIRE(rectangle.GetFillColor() == 0xffffff);
			}
		}
	}

	GIVEN("A rectangle with default colors")
	{
		const CRectangle rectangle = CRectangle({ 0, 0 }, 20, 30);

		WHEN("Taking an outline color")
		{
			THEN("It should return 0")
			{
				REQUIRE(rectangle.GetOutlineColor() == 0);
			}
		}

		WHEN("Taking a fill color")
		{
			THEN("It should return 0xffffff")
			{
				REQUIRE(rectangle.GetFillColor() == 0xffffff);
			}
		}
	}
}

SCENARIO("Program has ability to run himself via controller")
{
	WHEN("A controller runs <help>")
	{
		std::istringstream iss("help\n");
		std::ostringstream oss;
		CController controller = CController(iss, oss);

		controller.HandleCommand();

		THEN("It should print help info")
		{
			REQUIRE(oss.str() == "Available commands:\nline <from x> <from y> <to x> <to y> <outlineColor(hex)>\ncircle <center x> <center y> <radius> <outlineColor(hex)> <fillColor(hex)>\nrectangle <left top x> <left top y> <width> <height> <outlineColor(hex)> <fillColor(hex)>\ntriangle <first x> <first y> <second x> <second y> <third x> <third y> <outlineColor(hex)> <fillColor(hex)>\n");
		}
	}

	WHEN("A controller processes triangle and get shapes info")
	{
		std::istringstream iss("triangle 0 0 20 20 30 0 ff ff\n");
		std::ostringstream oss;
		CController controller = CController(iss, oss);

		controller.HandleCommand();
		controller.GetShapesInfo();

		THEN("It should print shapes info with the same triangle")
		{
			const std::string shapesInfo = "Max area shape:\n"
				"Area: 300\n"
				"Perimeter: 80.645\n"
				"Outline color: ff\n"
				"Fill color: ff\n"
				"Specific data: This is a triangle\n\n"
				"Min perimeter shape:\n"
				"Area: 300\n"
				"Perimeter: 80.645\n"
				"Outline color: ff\n"
				"Fill color: ff\n"
				"Specific data: This is a triangle\n\n";
			REQUIRE(oss.str() == shapesInfo);
		}
	}

	WHEN("A controller processes triangle and circle and get shapes info")
	{
		std::istringstream iss("triangle 0 0 20 20 30 0 ff ff\ncircle 20 20 5 ff ff\n");
		std::ostringstream oss;
		CController controller = CController(iss, oss);

		controller.HandleCommand();
		controller.HandleCommand();
		controller.GetShapesInfo();

		THEN("It should print shapes info with the same triangle")
		{
			const std::string shapesInfo = "Max area shape:\n"
				"Area: 300\n"
				"Perimeter: 80.645\n"
				"Outline color: ff\n"
				"Fill color: ff\n"
				"Specific data: This is a triangle\n\n"
				"Min perimeter shape:\n"
				"Area: 78.5398\n"
				"Perimeter: 31.4159\n"
				"Outline color: ff\n"
				"Fill color: ff\n"
				"Specific data: This is a circle\n\n";
			REQUIRE(oss.str() == shapesInfo);
		}
	}

	WHEN("Controller processes line and gets shapes info")
	{
		std::istringstream iss("line 0 0 20 20 ff");
		std::ostringstream oss;
		CController controller = CController(iss, oss);

		controller.HandleCommand();
		controller.GetShapesInfo();

		THEN("It prints nothing")
		{
			REQUIRE(oss.str() == "");
		}
	}

	WHEN("Controller processes rectangle and prints shapes info")
	{
		std::istringstream iss("rectangle 0 0 20 30 ff ff");
		std::ostringstream oss;
		CController controller = CController(iss, oss);

		controller.HandleCommand();
		controller.GetShapesInfo();

		THEN("It prints shapes info")
		{
			const std::string shapesInfo = "Max area shape:\n"
				"Area: 600\n"
				"Perimeter: 100\n"
				"Outline color: ff\n"
				"Fill color: ff\n"
				"Specific data: This is a rectangle\n\n"
				"Min perimeter shape:\n"
				"Area: 600\n"
				"Perimeter: 100\n"
				"Outline color: ff\n"
				"Fill color: ff\n"
				"Specific data: This is a rectangle\n\n";
			REQUIRE(oss.str() == shapesInfo);
		}
	}
}

// Mock tests

SCENARIO("Program has ability to draw figures")
{
	WHEN("Program draws line")
	{
		THEN("Line appears on window")
		{
			fakeit::Mock<ICanvas> mock;

			fakeit::Fake(Method(mock, DrawLine));

			const CPoint start(0, 0), end(2, 2);
			const uint32_t outlineColor = 0xfff;
			const CLine line(start, end, outlineColor);

			line.Draw(mock.get());

			fakeit::Verify(Method(mock, DrawLine).Using(start, end, outlineColor)).Once();
		}
	}

	WHEN("Program draws circle")
	{
		THEN("Circle appears on window")
		{
			fakeit::Mock<ICanvas> mock;

			fakeit::Fake(Method(mock, DrawCircle));

			const CPoint centerPoint(0, 0);
			const uint32_t radius = 20;
			const uint32_t outlineColor = 0xfff;
			const uint32_t fillColor = 0;
			const CCircle circle(centerPoint, radius, outlineColor, fillColor);

			circle.Draw(mock.get());

			fakeit::Verify(Method(mock, DrawCircle).Using(centerPoint, radius, outlineColor, fillColor)).Once();
		}
	}

	WHEN("Program draws triangle")
	{
		THEN("Circle appears on window")
		{
			fakeit::Mock<ICanvas> mock;

			fakeit::Fake(Method(mock, DrawPolygon));

		    CPoint points[3];
			points[0] = CPoint(0, 0);
			points[1] = CPoint(20, 20);
			points[2] = CPoint(30, 0);
			const uint32_t outlineColor = 0xfff;
			const uint32_t fillColor = 0;
			const CTriangle triangle(points, outlineColor, fillColor);

			triangle.Draw(mock.get());

			fakeit::Verify(Method(mock, DrawPolygon).Using(fakeit::Any<std::vector<CPoint>>(), outlineColor, fillColor)).Once();
		}
	}

	WHEN("Program draws rectangle")
	{
		THEN("Rectangle appears on window")
		{
			fakeit::Mock<ICanvas> mock;

			fakeit::Fake(Method(mock, DrawPolygon));

			const CPoint leftTopPoint = { 0, 0 };
			const uint32_t width = 20;
			const uint32_t height = 30;
			const uint32_t outlineColor = 0xfff;
			const uint32_t fillColor = 0;
			const CRectangle rectangle(leftTopPoint, width, height, outlineColor, fillColor);

			rectangle.Draw(mock.get());

			fakeit::Verify(Method(mock, DrawPolygon).Using(fakeit::Any<std::vector<CPoint>>(), outlineColor, fillColor)).Once();
		}
	}

	WHEN("Program draws line, rectangle")
	{
		THEN("Line, rectangle appear on window")
		{
			fakeit::Mock<ICanvas> mock;

			fakeit::Fake(Method(mock, DrawPolygon));
			fakeit::Fake(Method(mock, DrawLine));

			const CPoint leftTopPoint = { 0, 0 };
			const uint32_t width = 20;
			const uint32_t height = 30;
			const uint32_t outlineColor = 0xfff;
			const uint32_t fillColor = 0;
			const CRectangle rectangle(leftTopPoint, width, height, outlineColor, fillColor);
			const CPoint start(0, 0), end(2, 2);
			const CLine line(start, end, outlineColor);

			rectangle.Draw(mock.get());
			line.Draw(mock.get());

			fakeit::Verify(Method(mock, DrawPolygon).Using(fakeit::Any<std::vector<CPoint>>(), outlineColor, fillColor)).Once();
			fakeit::Verify(Method(mock, DrawLine).Using(start, end, outlineColor)).Once();
		}
	}
}