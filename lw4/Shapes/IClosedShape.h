#pragma once
#include "common_libs.h"
#include "IShape.h"

class IClosedShape : virtual public IShape
{
public:
	~IClosedShape() {};
	virtual double GetArea() const {};
	virtual double GetPerimeter() const {};
	virtual std::string GetFillColor() const {};

	std::string GetOutlineColor() const override {};
	std::string GetSpecifiedShapeData() const override {};
	void Draw(ICanvas& canvas) const override {};
};