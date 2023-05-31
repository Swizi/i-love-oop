#pragma once
#include "ISpeakable.h"

class CPerson final : public ISpeakable
{
public:
	CPerson(const std::string& name, const size_t yearOfBirth);
	/* Ведёт разговор с набором объектов, с которыми можно побеседовать */
	void SmallTalk(const ISpeakable& object) const override;
	void CopyState(const ISerializable& from, ISerializable& to) override;

	void MakeGreeting() const override;

private:
	std::string m_name = "";
	size_t m_YearOfBirth = 0;
};