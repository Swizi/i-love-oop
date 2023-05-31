#pragma once
#include <iostream>
#include "ICanvas.h"

class CCoutCanvas final: public ICanvas
{
public:
	CCoutCanvas() = default;

	void DrawLine() override;
	void DrawEllipse() override;
};