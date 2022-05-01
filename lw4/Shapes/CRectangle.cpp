#include "CRectangle.h"
#include "common_libs.h"

CRectangle::CRectangle(const CPoint& leftTopPoint, const uint32_t width, const uint32_t height, const std::string& outlineColor, const std::string& fillColor)
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
	return m_width + m_height;
}

std::string CRectangle::GetFillColor() const
{
	return m_fillColor;
}

std::string CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CRectangle::GetSpecifiedShapeData() const
{
	std::ostringstream oss;

	oss << "some shit" << std::endl;

	return oss.str();
}

void CRectangle::Draw(ICanvas& canvas) const
{
	canvas.DrawRectangle(m_leftTopPoint, m_width, m_height, m_outlineColor, m_fillColor);
}