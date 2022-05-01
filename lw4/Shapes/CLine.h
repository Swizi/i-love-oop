#pragma once
#include "common_libs.h"
#include "IShape.h"

class CLine : virtual public IShape
{
public:
	CLine(const CPoint& from, const CPoint& to, const std::string& fillColor);
	~CLine(){};
	std::string GetOutlineColor() const override {};
	std::string GetSpecifiedShapeData() const override {};
	void Draw(ICanvas& canvas) const override {};
private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	std::string m_outlineColor = "#000";
};