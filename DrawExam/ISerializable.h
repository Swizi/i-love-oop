#pragma once
#include <iostream>

class ISerializable
{
public:
	/* Копирует состояние из одного сериализуемого объекта в другой */
	virtual void CopyState(const ISerializable& from, ISerializable& to) = 0;
};