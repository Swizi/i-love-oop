#include "CPolygon.h"
#include "common_libs.h"

CPolygon::CPolygon(const std::vector<CPoint>& points, const uint32_t outlineColor, const uint32_t fillColor)
	: m_points(points)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CPolygon::GetArea() const
{
	double area = 0;

	for (int i = 0; i < m_points.size() - 1; i++)
	{
		area += (m_points[i].x * m_points[i + 1].y - m_points[i].y * m_points[i + 1].x);
	}
	area = area / 2;

	return area;
}

double CPolygon::GetPerimeter() const
{
	double perimeter = 0;

	for (int i = 0; i < m_points.size() - 1; i++)
	{
		perimeter += sqrt((m_points[i].x - m_points[i + 1].x) * (m_points[i].x - m_points[i + 1].x) + (m_points[i].y - m_points[i + 1].y) * (m_points[i].y - m_points[i + 1].y));
		perimeter += sqrt((m_points[0].x - m_points[m_points.size() - 1].x) * (m_points[0].x - m_points[m_points.size() - 1].x) + (m_points[0].y - m_points[m_points.size() - 1].y) * (m_points[0].y - m_points[m_points.size() - 1].y));
	}

	return perimeter;
}

uint32_t CPolygon::GetFillColor() const
{
	return m_fillColor;
}

uint32_t CPolygon::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CPolygon::GetSpecifiedShapeData() const
{
	std::ostringstream oss;

	oss << "This is a polygon" << std::endl;

	return oss.str();
}

void CPolygon::Draw(CCanvas& canvas) const
{
	canvas.DrawPolygon(m_points, m_outlineColor, m_fillColor);
}