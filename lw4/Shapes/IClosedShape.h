#pragma once
#include "common_libs.h"
#include "IShape.h"

class IClosedShape: public IShape
{
public:
	~IClosedShape() {};
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual uint32_t GetFillColor() const = 0;
};