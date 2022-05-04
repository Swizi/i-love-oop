#include "CController.h"
#include "CLine.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "IClosedShape.h"
#include "CPolygon.h"

const int NEW_LINE_SYMBOL = -1;
const int MAX_HEX_COLOR = 0xffffff;

CController::CController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "line", bind(&CController::HandleLine, this, std::placeholders::_1) },
		  { "circle", bind(&CController::HandleCircle, this, std::placeholders::_1) },
		  { "polygon", bind(&CController::HandlePolygon, this, std::placeholders::_1) },
		  { "rectangle", bind(&CController::HandleRectangle, this, std::placeholders::_1) },
		  { "help", bind(&CController::Help, this, std::placeholders::_1) }
		})
{
}

// Public
bool CController::GetShape()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		try
		{
			return it->second(strm);
		}
		catch (std::exception& e)
		{
			throw e;
		}
	}

	return false;
}

bool CController::GetShapesInfo()
{
	auto maxAreaShapeIt = std::max_element(m_closedShapes.begin(), m_closedShapes.end(),
		[&](const std::unique_ptr<IClosedShape>& firstShape, const std::unique_ptr<IClosedShape>& secondShape) {
			return firstShape->GetArea() < secondShape->GetArea();
		});
	auto minPerimeterShapeIt = std::min_element(m_closedShapes.begin(), m_closedShapes.end(),
		[&](const std::unique_ptr<IClosedShape>& firstShape, const std::unique_ptr<IClosedShape>& secondShape) {
			return firstShape->GetPerimeter() > secondShape->GetPerimeter();
		});

	if (maxAreaShapeIt != m_closedShapes.end()) {
		m_output << "Max area shape:" << std::endl;
		m_output << "Area: " << (*maxAreaShapeIt)->GetArea() << std::endl;
		m_output << "Perimeter: " << (*maxAreaShapeIt)->GetPerimeter() << std::endl;
		m_output << "Outline color: " << (*maxAreaShapeIt)->GetOutlineColor() << std::endl;
		m_output << "Fill color: " << (*maxAreaShapeIt)->GetFillColor() << std::endl;
		m_output << "Specific data: " << (*maxAreaShapeIt)->GetSpecifiedShapeData() << std::endl;
	}
	if (minPerimeterShapeIt != m_closedShapes.end()) {
		m_output << "Min perimeter shape:" << std::endl;
		m_output << "Area: " << (*minPerimeterShapeIt)->GetArea() << std::endl;
		m_output << "Perimeter: " << (*minPerimeterShapeIt)->GetPerimeter() << std::endl;
    	m_output << "Outline color: " << (*minPerimeterShapeIt)->GetOutlineColor() << std::endl;
		m_output << "Fill color: " << (*minPerimeterShapeIt)->GetFillColor() << std::endl;
		m_output << "Specific data: " << (*minPerimeterShapeIt)->GetSpecifiedShapeData() << std::endl;
	}

	return true;
}

bool CController::DrawShapes()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Shapes");
	CCanvas canvas(window);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		window.clear();

		for (int i = 0; i < m_shapes.size(); i++)
		{
			m_shapes[i]->Draw(canvas);
		}

		window.display();
	}

	return true;
}

// Private
bool CController::HandleLine(std::istream& args)
{
	try
	{
		CController::LineArgs parsedArgs = ParseLineArgs(args);

		CLine line = CLine(parsedArgs.fromPoint, parsedArgs.toPoint, parsedArgs.outlineColor);
		m_shapes.push_back(std::make_unique<CLine>(line));
	}
	catch (std::exception& e)
	{
		throw e;
	}

	return true;
}

bool CController::HandleCircle(std::istream& args)
{
	CController::CircleArgs parsedArgs = ParseCircleArgs(args);

	CCircle circle = CCircle(parsedArgs.centerPoint, parsedArgs.radius, parsedArgs.outlineColor, parsedArgs.fillColor);
	m_shapes.push_back(std::make_unique<CCircle>(circle));
	m_closedShapes.push_back(std::make_unique<CCircle>(circle));

	return true;
}

bool CController::HandlePolygon(std::istream& args)
{
	CController::PolygonArgs parsedArgs = ParsePolygonArgs(args);

	CPolygon polygon = CPolygon(parsedArgs.points, parsedArgs.outlineColor, parsedArgs.fillColor);
	m_shapes.push_back(std::make_unique<CPolygon>(polygon));
	m_closedShapes.push_back(std::make_unique<CPolygon>(polygon));

	return true;
}

bool CController::HandleRectangle(std::istream& args)
{
	CController::RectangleArgs parsedArgs = ParseRectangleArgs(args);

	CRectangle rectangle = CRectangle(parsedArgs.leftTopPoint, parsedArgs.width, parsedArgs.height, parsedArgs.outlineColor, parsedArgs.fillColor);
	m_shapes.push_back(std::make_unique<CRectangle>(rectangle));
	m_closedShapes.push_back(std::make_unique<CRectangle>(rectangle));

	return true;
}

bool CController::Help(std::istream& /*args*/)
{
	m_output << "Available commands:" << std::endl;
	m_output << "line <from x> <from y> <to x> <to y> <outlineColor(hex)>" << std::endl;
	m_output << "circle <center x> <center y> <radius> <outlineColor(hex)> <fillColor(hex)>" << std::endl;
	m_output << "polygon <points separated by a space>(<point1 x> <point1 y> <point2 x> <point2 y>; <outlineColor(hex)> <fillColor(hex)>" << std::endl;
	m_output << "rectangle <left top x> <left top y> <width> <height> <outlineColor(hex)> <fillColor(hex)>" << std::endl;

	return true;
}

CController::LineArgs CController::ParseLineArgs(std::istream& args)
{
	uint32_t fromX = 0;
	uint32_t fromY = 0;
	if (args.peek() == NEW_LINE_SYMBOL)
	{
		throw std::exception("Args are invalid. <from x> has not passed");
	}
	args >> fromX;
	if (fromX < 0)
	{
		throw std::exception("<from x> can not be negative");
	}
	if (args.peek() == NEW_LINE_SYMBOL)
	{
		throw std::exception("Args are invalid. <from y> has not passed");
	}
	args >> fromY;
	if (fromY < 0)
	{
		throw std::exception("<from y> can not be negative");
	}
	CPoint from = CPoint(fromX, fromY);
	uint32_t toX = 0;
	uint32_t toY = 0;
	if (args.peek() == NEW_LINE_SYMBOL)
	{
		throw std::exception("Args are invalid. <to x> has not passed");
	}
	args >> toX;
	if (toX < 0)
	{
		throw std::exception("<to x> can not be negative");
	}
	if (args.peek() == NEW_LINE_SYMBOL)
	{
		throw std::exception("Args are invalid. <to y> has not passed");
	}
	args >> toY;
	if (toY < 0)
	{
		throw std::exception("<to y> can not be negative");
	}
	CPoint to = CPoint(toX, toY);
	uint32_t outlineColor = 0;
	if (args.peek() == NEW_LINE_SYMBOL)
	{
		throw std::exception("Args are invalid. <outlineColor> has not passed");
	}
	args >> std::hex >> outlineColor;
	if (outlineColor < 0 || outlineColor > MAX_HEX_COLOR)
	{
		throw std::exception("<outlineColor> can be in 0 .. ffffff");
	}

	return {from, to, outlineColor};
}

CController::RectangleArgs CController::ParseRectangleArgs(std::istream& args)
{
	uint32_t leftTopX = 0;
	uint32_t leftTopY = 0;
	args >> leftTopX;
	args >> leftTopY;
	CPoint leftTop = CPoint(leftTopX, leftTopY);
	uint32_t width = 0;
	args >> width;
	uint32_t height = 0;
	args >> height;
	uint32_t outlineColor = 0;
	args >> std::hex >> outlineColor;
	uint32_t fillColor = 0;
	args >> std::hex >> fillColor;

	return { leftTop, width, height, outlineColor, fillColor };
}

CController::CircleArgs CController::ParseCircleArgs(std::istream& args)
{
	uint32_t centerX = 0;
	uint32_t centerY = 0;
	args >> centerX;
	args >> centerY;
	CPoint center = CPoint(centerX, centerY);
	uint32_t radius = 0;
	args >> radius;
	uint32_t outlineColor = 0;
	args >> std::hex >> outlineColor;
	uint32_t fillColor = 0;
	args >> std::hex >> fillColor;

	return { center, radius, outlineColor, fillColor };
}

CController::PolygonArgs CController::ParsePolygonArgs(std::istream& args)
{
	std::string str1 = "";
	std::string str2 = "";
	uint32_t outlineColor = 0;
	uint32_t fillColor = 0;
	std::vector<CPoint> points = {};

	args >> str1;
	args >> str2;
	while (str1 != ";" && args.peek() != '\n')
	{
		uint32_t x = std::stoul(str1);
		uint32_t y = std::stoul(str2);
		CPoint point = CPoint(x, y);
		points.push_back(point);

		args >> str1;
		if (args.peek() != '\n') {
			args >> str2;
		}
	}
	if (args.peek() != '\n') {
		args >> std::hex >> outlineColor;
	}
	if (args.peek() != '\n') {
		args >> std::hex >> fillColor;
	}

	return { points, outlineColor, fillColor };
}