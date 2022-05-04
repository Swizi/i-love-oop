#pragma once
#include "common_libs.h"
#include "CPoint.h"

class ICanvas
{
public:
	ICanvas() {};
	~ICanvas() {};
	virtual void DrawLine(const CPoint& from, const CPoint& to, const uint32_t outlineColor = 0) = 0;
	virtual void DrawCircle(const CPoint& center, const uint32_t radius, const uint32_t outlineColor = 0, const uint32_t fillColor = 0xffffff) = 0;
	virtual void DrawPolygon(const std::vector<CPoint>& points, const uint32_t outlineColor = 0, const uint32_t fillColor = 0xffffff) = 0;
	virtual void DrawRectangle(const CPoint& leftTopPoint, const uint32_t width, const uint32_t height, const uint32_t outlineColor = 0, const uint32_t fillColor = 0xffffff) = 0;
};