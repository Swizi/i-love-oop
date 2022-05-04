#pragma once
#include "common_libs.h"
#include "CPoint.h"
#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class CCanvas: public ICanvas
{
public:
	CCanvas(sf::RenderWindow& window);
	~CCanvas();
	void DrawLine(const CPoint& from, const CPoint& to, const uint32_t outlineColor = 0) override;
	void DrawCircle(const CPoint& center, const uint32_t radius, const uint32_t outlineColor = 0, const uint32_t fillColor = 0xffffff) override;
	void DrawPolygon(const std::vector<CPoint>& points, const uint32_t outlineColor = 0, const uint32_t fillColor = 0xffffff) override;
	void DrawRectangle(const CPoint& leftTopPoint, const uint32_t width, const uint32_t height, const uint32_t outlineColor = 0, const uint32_t fillColor = 0xffffff) override;

private:
	sf::RenderWindow& m_window;
};
