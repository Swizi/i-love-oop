#pragma once
#include "ISerializable.h"
#include "CCoutCanvas.h"

class ICanvasDrawable: public ISerializable
{
public:
	/* Рисует набор объектов, которые можно нарисовать на переданном холсте (принимает объекты и холст) */
	virtual void Draw(ICanvas& canvas) const = 0;
};