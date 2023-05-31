#pragma once
#include "ISerializable.h"
#include "CCoutCanvas.h"

class ICanvasDrawable: public ISerializable
{
public:
	/* ������ ����� ��������, ������� ����� ���������� �� ���������� ������ (��������� ������� � �����) */
	virtual void Draw(ICanvas& canvas) const = 0;
};