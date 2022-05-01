#pragma once
#include "common_libs.h"
#include "IClosedShape.h"

class CCircle : virtual public IClosedShape
{
public:
	CCircle(const CPoint& centerPoint, const uint32_t radius, const std::string& outlineColor, const std::string& fillColor);
	~CCircle() {};
	double GetArea() const override {};
	double GetPerimeter() const override {};
	std::string GetFillColor() const override {};
	std::string GetOutlineColor() const override {};
	std::string GetSpecifiedShapeData() const override {};
	void Draw(ICanvas& canvas) const override {};

private:
	CPoint m_centerPoint;
	uint32_t m_radius = 0;
	std::string m_outlineColor = "#000";
	std::string m_fillColor = "#fff";
};