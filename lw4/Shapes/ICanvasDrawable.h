#pragma once
#include "CCanvas.h"

class ICanvasDrawable
{
public:
	~ICanvasDrawable() {};
	virtual void Draw(ICanvas& canvas) const = 0;
};