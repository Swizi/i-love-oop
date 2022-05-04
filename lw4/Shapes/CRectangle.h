#pragma once
#include "common_libs.h"
#include "IClosedShape.h"

class CRectangle: public IClosedShape
{
public:
	CRectangle(const CPoint& leftTopPoint, const uint32_t width, const uint32_t height, const uint32_t outlineColor, const uint32_t fillColor);
	~CRectangle() {};
	double GetArea() const override final;
	double GetPerimeter() const override final;
	uint32_t GetFillColor() const override final;
	uint32_t GetOutlineColor() const override final;
	std::string GetSpecifiedShapeData() const override final;
	void Draw(CCanvas& canvas) const override final;

private:
	CPoint m_leftTopPoint;
	uint32_t m_width = 0;
	uint32_t m_height = 0;
	uint32_t m_outlineColor = 0;
	uint32_t m_fillColor = 0xffffff;
};