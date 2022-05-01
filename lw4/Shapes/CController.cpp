#include "CController.h"
#include "CLine.h"
#include "CCircle.h"
#include "CRectangle.h"

template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

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
		return it->second(strm);
	}

	return false;
}

bool CController::GetShapesInfo()
{
	IClosedShape maxAreaShape;
	for (int i = 0; i < m_shapes.size(); i++)
	{
		if (instanceof<IClosedShape>(m_shapes[i]))
	}
}

// Private
bool CController::HandleLine(std::istream& args)
{
	uint32_t fromX = 0;
	uint32_t fromY = 0;
	args >> fromX;
	args >> fromY;
	CPoint from = CPoint(fromX, fromY);

	uint32_t toX = 0;
	uint32_t toY = 0;
	args >> toX;
	args >> toY;
	CPoint to = CPoint(toX, toY);

	std::string outlineColor = "";
	args >> outlineColor;

	CLine line = CLine(from, to, outlineColor);
	m_shapes.push_back(line);
	line.Draw(m_canvas);

	return true;
}

bool CController::HandleCircle(std::istream& args)
{
	uint32_t centerX = 0;
	uint32_t centerY = 0;
	args >> centerX;
	args >> centerY;
	CPoint center = CPoint(centerX, centerY);

	uint32_t radius = 0;
	args >> radius;

	std::string outlineColor = "";
	args >> outlineColor;

	std::string fillColor = "";
	args >> fillColor;

	CCircle circle = CCircle(center, radius, outlineColor, fillColor);
	m_shapes.push_back(circle);
	circle.Draw(m_canvas);

	return true;
}

bool CController::HandlePolygon(std::istream& args)
{
	

	return true;
}

bool CController::HandleRectangle(std::istream& args)
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

	std::string outlineColor = "";
	args >> outlineColor;

	std::string fillColor = "";
	args >> fillColor;

	CRectangle rectangle = CRectangle(leftTop, width, height, outlineColor, fillColor);
	m_shapes.push_back(rectangle);
	rectangle.Draw(m_canvas);

	return true;
}

bool CController::Help(std::istream& /*args*/)
{
	m_output << "Available commands:" << std::endl;
	m_output << "line <from x> <from y> <to x> <to y> <outlineColor>" << std::endl;
	m_output << "circle <center x> <center y> <radius> <outlineColor> <fillColor>" << std::endl;
	m_output << "polygon <points> <outlineColor> <fillColor>" << std::endl;
	m_output << "rectangle <left top x> <left top y> <width> <height> <outlineColor> <fillColor" << std::endl;
}