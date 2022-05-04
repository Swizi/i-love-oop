#pragma once
#include "common_libs.h"
#include "IClosedShape.h"

class CCircle: public IClosedShape
{
public:
	CCircle(const CPoint& centerPoint, const uint32_t radius, const uint32_t outlineColor, const uint32_t fillColor);
	~CCircle() {};
	double GetArea() const override final;
	double GetPerimeter() const override final;
	uint32_t GetFillColor() const override final;
	uint32_t GetOutlineColor() const override final;
	std::string GetSpecifiedShapeData() const override final;
	void Draw(CCanvas& canvas) const override final;

private:
	CPoint m_centerPoint;
	uint32_t m_radius = 0;
	uint32_t m_outlineColor = 0;
	uint32_t m_fillColor = 0xffffff;
};