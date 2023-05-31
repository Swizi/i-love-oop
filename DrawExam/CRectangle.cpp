#include "CRectangle.h"

void CRectangle::Draw(ICanvas& canvas) const
{
	canvas.DrawLine();
	canvas.DrawLine();
	canvas.DrawLine();
	canvas.DrawLine();
}

void CRectangle::CopyState(const ISerializable& from, ISerializable& to)
{
	// do nothing
}