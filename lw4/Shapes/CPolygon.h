#pragma once
#include "common_libs.h"
#include "IClosedShape.h"

class CPolygon : virtual public IClosedShape
{
public:
	CPolygon(const std::vector<CPoint>& points, const std::string& outlineColor, const std::string& fillColor);
	~CPolygon() {};
	double GetArea() const override {};
	double GetPerimeter() const override {};
	std::string GetFillColor() const override {};
	std::string GetOutlineColor() const override {};
	std::string GetSpecifiedShapeData() const override {};
	void Draw(ICanvas& canvas) const override {};

private:
	std::vector<CPoint> m_points;
	std::string m_outlineColor = "#000";
	std::string m_fillColor = "#fff";
};