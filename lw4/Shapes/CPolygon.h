#pragma once
#include "common_libs.h"
#include "IClosedShape.h"

class CPolygon: public IClosedShape
{
public:
	CPolygon(const std::vector<CPoint>& points, const uint32_t outlineColor, const uint32_t fillColor);
	~CPolygon() {};
	double GetArea() const override final;
	double GetPerimeter() const override final;
	uint32_t GetFillColor() const override final;
	uint32_t GetOutlineColor() const override final;
	std::string GetSpecifiedShapeData() const override final;
	void Draw(CCanvas& canvas) const override final;

private:
	std::vector<CPoint> m_points;
	uint32_t m_outlineColor = 0;
	uint32_t m_fillColor = 0xffffff;
};