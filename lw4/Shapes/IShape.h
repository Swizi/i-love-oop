#pragma once
#include "common_libs.h"
#include "ICanvasDrawable.h"

class IShape: virtual public ICanvasDrawable
{
public:
	~IShape() {};
	virtual std::string GetOutlineColor() const {};
	virtual std::string GetSpecifiedShapeData() const {};

	void Draw(ICanvas& canvas) const override {};
};