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
	void DrawLine(const CPoint& from, const CPoint& to, const uint32_t outlineColor = MIN_HEX_COLOR) override final;
	void DrawCircle(const CPoint& center, const uint32_t radius, const uint32_t outlineColor = MIN_HEX_COLOR, const uint32_t fillColor = MAX_HEX_COLOR) override final;
	void DrawPolygon(const std::vector<CPoint>& points, const uint32_t outlineColor = MIN_HEX_COLOR, const uint32_t fillColor = MAX_HEX_COLOR) override final;

private:
	sf::RenderWindow& m_window;
};
