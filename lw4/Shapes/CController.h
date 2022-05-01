#pragma once
#include "common_libs.h"
#include "IShape.h"

class CController
{
public:
	class CController(std::istream& input, std::ostream& output);
	bool GetShape();
	bool GetShapesInfo();

private:
	bool AddShape(IShape shape);
	bool HandleLine(std::istream& args);
	bool HandleCircle(std::istream& args);
	bool HandlePolygon(std::istream& args);
	bool HandleRectangle(std::istream& args);
	bool Help(std::istream& args);

private:
	using Handler = std::function<bool(std::istream & args)>;

	using ActionMap = std::map<std::string, Handler>;

	std::vector<IShape> m_shapes = {};
	std::istream& m_input;
	std::ostream& m_output;
	ICanvas m_canvas;

	const ActionMap m_actionMap;
};