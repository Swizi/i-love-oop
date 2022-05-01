#pragma once
#include "common_libs.h"
#include "IClosedShape.h"

class CRectangle : virtual public IClosedShape
{
public:
	CRectangle(const CPoint& leftTopPoint, const uint32_t width, const uint32_t height, const std::string& outlineColor, const std::string& fillColor);
	~CRectangle() {};
	double GetArea() const override {};
	double GetPerimeter() const override {};
	std::string GetFillColor() const override {};
	std::string GetOutlineColor() const override {};
	std::string GetSpecifiedShapeData() const override {};
	void Draw(ICanvas& canvas) const override {};

private:
	CPoint m_leftTopPoint;
	uint32_t m_width = 0;
	uint32_t m_height = 0;
	std::string m_outlineColor = "#000";
	std::string m_fillColor = "#fff";
};