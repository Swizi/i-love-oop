#pragma once
#include "CCanvas.h"

class ICanvasDrawable
{
public:
	~ICanvasDrawable() {};
	virtual void Draw(CCanvas& canvas) const = 0;
};