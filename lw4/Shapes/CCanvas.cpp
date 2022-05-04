#include "CCanvas.h"
#include "common_libs.h"

sf::Color GetColor(uint32_t color)
{
	uint32_t blue = color % 256;
	uint32_t green = (color / 256) % 256;
	uint32_t red = ((color / 256) / 256) % 256;

	return sf::Color(red, green, blue);
}

CCanvas::CCanvas(sf::RenderWindow& window):
	m_window(window)
{
}

CCanvas::~CCanvas()
{
	m_window.close();
}

void CCanvas::DrawLine(const CPoint& from, const CPoint& to, const uint32_t outlineColor)
{
	sf::Vertex line[2];
	sf::Color color = GetColor(outlineColor);
	line[0].position = sf::Vector2f(from.x, from.y);
	line[0].color = color;
	line[1].position = sf::Vector2f(to.x, to.y);
	line[1].color = color;

	m_window.draw(line, 2, sf::Lines);
}

void CCanvas::DrawRectangle(const CPoint& leftTopPoint, const uint32_t width, const uint32_t height, const uint32_t outlineColor, const uint32_t fillColor)
{
	if (m_window.isOpen())
	{
		sf::RectangleShape rect;
		rect.setOutlineColor(GetColor(outlineColor));
		rect.setFillColor(GetColor(fillColor));
		rect.setPosition(sf::Vector2f(leftTopPoint.x, leftTopPoint.y));
		rect.setSize(sf::Vector2f(width, height));

		m_window.draw(rect);
	}
}

void CCanvas::DrawCircle(const CPoint& center, const uint32_t radius, const uint32_t outlineColor, const uint32_t fillColor)
{
	if (m_window.isOpen())
	{
		sf::CircleShape circle;
		circle.setOutlineColor(GetColor(outlineColor));
		circle.setFillColor(GetColor(fillColor));
		circle.setRadius(radius);
		circle.setPosition(center.x, center.y);

		m_window.draw(circle);
	}
}

void CCanvas::DrawPolygon(const std::vector<CPoint>& points, const uint32_t outlineColor, const uint32_t fillColor)
{
	if (m_window.isOpen())
	{
		sf::ConvexShape polygon;
		polygon.setPointCount(points.size());
		polygon.setOutlineColor(GetColor(outlineColor));
		polygon.setFillColor(GetColor(fillColor));
		for (int i = 0; i < points.size(); i++)
		{
			polygon.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
		}

		m_window.draw(polygon);
	}
}

