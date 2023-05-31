#pragma once
#include "common_libs.h"
#include "ICanvasDrawable.h"

class IShape: public ICanvasDrawable
{
public:
	// Деструктор?
	~IShape() {};
	// == 0? для чего
	// добавить GetPerimeter()
	virtual uint32_t GetOutlineColor() const = 0;
	virtual std::string GetSpecifiedShapeData() const = 0;
};