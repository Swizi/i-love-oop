#pragma once
#include "ISerializable.h"

class ISpeakable : public ISerializable
{
public:
	/* Ведёт разговор с набором объектов, с которыми можно побеседовать */
	virtual void SmallTalk(const ISpeakable& object) const = 0;
	virtual void MakeGreeting() const = 0;
};