#include "CPerson.h"

CPerson::CPerson(const std::string& name, const size_t yearOfBirth)
	:m_name(name)
	, m_YearOfBirth(yearOfBirth)
{
}

void CPerson::SmallTalk(const ISpeakable& object) const
{
	this->MakeGreeting();
	object.MakeGreeting();
}

void CPerson::MakeGreeting() const
{
	std::cout << "Hello, I'm " << m_name << std::endl;
	std::cout << "I have been born at " << m_YearOfBirth << std::endl;
}

void CPerson::CopyState(const ISerializable& from, ISerializable& to)
{
	// do nothing
}