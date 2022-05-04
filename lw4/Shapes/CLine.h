#pragma once
#include "common_libs.h"
#include "IShape.h"

class CLine: public IShape
{
public:
	CLine(const CPoint& from, const CPoint& to, const uint32_t fillColor);
	~CLine(){};
	uint32_t GetOutlineColor() const override final;
	std::string GetSpecifiedShapeData() const override final;
	void Draw(CCanvas& canvas) const override final;

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	uint32_t m_outlineColor = 0;
};