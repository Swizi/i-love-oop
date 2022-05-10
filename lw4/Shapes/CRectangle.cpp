#include "CRectangle.h"
#include "common_libs.h"

CRectangle::CRectangle(const CPoint& leftTopPoint, const uint32_t width, const uint32_t height, const uint32_t outlineColor, const uint32_t fillColor)
	: m_leftTopPoint(leftTopPoint)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_width + m_height);
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CRectangle::GetSpecifiedShapeData() const
{
	std::ostringstream oss;

	oss << "This is a rectangle" << std::endl;

	return oss.str();
}

void CRectangle::Draw(ICanvas& canvas) const
{
	std::vector<CPoint> points = {};
	points.push_back(m_leftTopPoint);
	points.push_back({ m_leftTopPoint.x + m_width, m_leftTopPoint.y });
	points.push_back({ m_leftTopPoint.x + m_width, m_leftTopPoint.y + m_height });
	points.push_back({ m_leftTopPoint.x, m_leftTopPoint.y + m_height });

	canvas.DrawPolygon(points, m_outlineColor, m_fillColor);
}