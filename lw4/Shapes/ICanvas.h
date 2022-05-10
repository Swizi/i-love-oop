#pragma once
#include "common_libs.h"
#include "CPoint.h"

const int MAX_HEX_COLOR = 0xffffff;
const int MIN_HEX_COLOR = 0;

class ICanvas
{
public:
	ICanvas() {};
	~ICanvas() {};
	virtual void DrawLine(const CPoint& from, const CPoint& to, const uint32_t outlineColor = MIN_HEX_COLOR) = 0;
	virtual void DrawCircle(const CPoint& center, const uint32_t radius, const uint32_t outlineColor = MIN_HEX_COLOR, const uint32_t fillColor = MAX_HEX_COLOR) = 0;
	virtual void DrawPolygon(const std::vector<CPoint>& points, const uint32_t outlineColor = MIN_HEX_COLOR, const uint32_t fillColor = MAX_HEX_COLOR) = 0;
};