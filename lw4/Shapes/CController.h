#pragma once
#include "common_libs.h"
#include <SFML/Graphics.hpp>
#include "IShape.h"
#include "IClosedShape.h"

class CController
{
public:
	class CController(std::istream& input, std::ostream& output);
	bool GetShape();
	bool GetShapesInfo();
	bool DrawShapes();

private:
	bool HandleLine(std::istream& args);
	bool HandleCircle(std::istream& args);
	bool HandlePolygon(std::istream& args);
	bool HandleRectangle(std::istream& args);
	bool Help(std::istream& args);

	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	std::vector<std::unique_ptr<IShape>> m_shapes;
	std::vector<std::unique_ptr<IClosedShape>> m_closedShapes;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;

	// Args

	struct LineArgs
	{
		CPoint fromPoint;
		CPoint toPoint;
		uint32_t outlineColor;
	};

	struct CircleArgs
	{
		CPoint centerPoint;
		uint32_t radius;
		uint32_t outlineColor;
		uint32_t fillColor;
	};

	struct PolygonArgs
	{
		std::vector<CPoint> points;
		uint32_t outlineColor;
		uint32_t fillColor;
	};

	struct RectangleArgs
	{
		CPoint leftTopPoint;
		uint32_t width;
		uint32_t height;
		uint32_t outlineColor;
		uint32_t fillColor;
	};

	LineArgs ParseLineArgs(std::istream& args);
	CircleArgs ParseCircleArgs(std::istream& args);
	PolygonArgs ParsePolygonArgs(std::istream& args);
	RectangleArgs ParseRectangleArgs(std::istream& args);
};