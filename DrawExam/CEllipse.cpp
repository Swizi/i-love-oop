#include "CEllipse.h"

void CEllipse::Draw(ICanvas& canvas) const
{
	canvas.DrawEllipse();
}

void CEllipse::CopyState(const ISerializable& from, ISerializable& to)
{
	// do nothing
}