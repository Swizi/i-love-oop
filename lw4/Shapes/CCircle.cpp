#include "CCircle.h"
#include "common_libs.h"

CCircle::CCircle(const CPoint& centerPoint, const uint32_t radius, const std::string& outlineColor, const std::string& fillColor)
	: m_centerPoint(centerPoint)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string CCircle::GetFillColor() const
{
	return m_fillColor;
}

std::string CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CCircle::GetSpecifiedShapeData() const
{
	std::ostringstream oss;

	oss << "some shit" << std::endl;

	return oss.str();
}

void CCircle::Draw(ICanvas& canvas) const
{
	canvas.DrawCircle(m_centerPoint, m_radius, m_outlineColor, m_fillColor);
}