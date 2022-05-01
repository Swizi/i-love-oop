#include "CLine.h"
#include "common_libs.h"

CLine::CLine(const CPoint& from, const CPoint& to, const std::string& outlineColor)
	: m_startPoint(from)
	, m_endPoint(to)
	, m_outlineColor(outlineColor)
{
}

std::string CLine::GetOutlineColor() const
{
	return CLine::m_outlineColor;
}

std::string CLine::GetSpecifiedShapeData() const
{
	std::ostringstream oss;

	oss << "some shit" << std::endl;

	return oss.str();
}

void CLine::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}