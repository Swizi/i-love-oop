#pragma once
#include "ICanvasDrawable.h"

class CTriangle: public ICanvasDrawable
{
public:
	void Draw(ICanvas& canvas) const override;
	void CopyState(const ISerializable& from, ISerializable& to) override;
};