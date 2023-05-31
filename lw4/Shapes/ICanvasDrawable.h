#pragma once
#include "CCanvas.h"

class ICanvasDrawable
{
public:
	// Для чего здесь дестркутор? 
	~ICanvasDrawable() {};
	virtual void Draw(ICanvas& canvas) const = 0;
};