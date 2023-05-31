#pragma once
#include <iostream>

class ISerializable
{
public:
	/* �������� ��������� �� ������ �������������� ������� � ������ */
	virtual void CopyState(const ISerializable& from, ISerializable& to) = 0;
};