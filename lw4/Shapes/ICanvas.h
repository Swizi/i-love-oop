#pragma once
#include "common_libs.h"
#include "CPoint.h"

class ICanvas
{
public:
	ICanvas() {};
	~ICanvas() {};
	void DrawLine(const CPoint& from, const CPoint& to, const std::string& outlineColor = "#000") const;
	void DrawCircle(const CPoint& center, const uint32_t radius, const std::string& outlineColor = "#000", const std::string& fillColor = "#fff") const;
	void DrawPolygon(const std::vector<CPoint>& points, const std::string& outlineColor = "#000", const std::string& fillColor = "#fff") const;
	void DrawRectangle(const CPoint& leftTopPoint, const uint32_t width, const uint32_t height, const std::string& outlineColor = "#000", const std::string& fillColor = "#fff") const;
};