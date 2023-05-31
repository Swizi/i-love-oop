#include "CTriangle.h"
#include "common_libs.h"
#include <iostream>

CTriangle::CTriangle(const CPoint points[3], const uint32_t outlineColor, const uint32_t fillColor)
	: m_points()
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	m_points[0] = points[0];
	m_points[1] = points[1];
	m_points[2] = points[2];
}

double CTriangle::GetArea() const
{
	// Heron's formula
	double p = this->GetPerimeter() / 2;
	double a = sqrt((m_points[1].x - m_points[0].x) * (m_points[1].x - m_points[0].x) +
		(m_points[1].y - m_points[0].y) * (m_points[1].y - m_points[0].y));
	double b = sqrt((m_points[2].x - m_points[1].x) * (m_points[2].x - m_points[1].x) +
		(m_points[2].y - m_points[1].y) * (m_points[2].y - m_points[1].y));
	double c = sqrt((m_points[0].x - m_points[2].x) * (m_points[0].x - m_points[2].x) +
		(m_points[0].y - m_points[2].y) * (m_points[0].y - m_points[2].y));

	return sqrt(p * (p - a) * (p - b) * (p - c));
}

double CTriangle::GetPerimeter() const
{
	// устранить дублирование
	double a = sqrt((m_points[1].x - m_points[0].x) * (m_points[1].x - m_points[0].x) +
		(m_points[1].y - m_points[0].y) * (m_points[1].y - m_points[0].y));
	double b = sqrt((m_points[2].x - m_points[1].x) * (m_points[2].x - m_points[1].x) +
		(m_points[2].y - m_points[1].y) * (m_points[2].y - m_points[1].y));
	double c = sqrt((m_points[2].x - m_points[0].x) * (m_points[2].x - m_points[0].x) +
		(m_points[2].y - m_points[0].y) * (m_points[2].y - m_points[0].y));

	return a+b+c;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CTriangle::GetSpecifiedShapeData() const
{
	std::ostringstream oss;

	oss << "This is a triangle" << std::endl;

	return oss.str();
}

void CTriangle::Draw(ICanvas& canvas) const
{
	std::vector<CPoint> points(std::begin(m_points), std::end(m_points));

	canvas.DrawPolygon(points, m_outlineColor, m_fillColor);
}