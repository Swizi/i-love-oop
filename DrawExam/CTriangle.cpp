#include "CTriangle.h"

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.DrawLine();
	canvas.DrawLine();
	canvas.DrawLine();
}

void CTriangle::CopyState(const ISerializable& from, ISerializable& to)
{
	// do nothing
}