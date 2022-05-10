#pragma once
#include "common_libs.h"
#include "IClosedShape.h"

class CTriangle: public IClosedShape
{
public:
	CTriangle(const CPoint points[3], const uint32_t outlineColor = MIN_HEX_COLOR, const uint32_t fillColor = MAX_HEX_COLOR);
	~CTriangle() {};
	double GetArea() const override final;
	double GetPerimeter() const override final;
	uint32_t GetFillColor() const override final;
	uint32_t GetOutlineColor() const override final;
	std::string GetSpecifiedShapeData() const override final;
	void Draw(ICanvas& canvas) const override final;

private:
	CPoint m_points[3];
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};