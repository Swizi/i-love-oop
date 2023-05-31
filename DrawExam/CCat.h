#pragma once
#include "ISpeakable.h"

class CCat final: public ISpeakable
{
public:
	CCat(const std::string& nickname);
	/* ���� �������� � ������� ��������, � �������� ����� ������������ */
	void SmallTalk(const ISpeakable& object) const override;
	void CopyState(const ISerializable& from, ISerializable& to) override;

	void MakeGreeting() const override;

private:
	std::string m_nickname = "";
};