#include "CCat.h"

CCat::CCat(const std::string& nickname)
	:m_nickname(nickname)
{
}

void CCat::SmallTalk(const ISpeakable& object) const
{
	this->MakeGreeting();
	object.MakeGreeting();
}

void CCat::MakeGreeting() const
{
	std::cout << "Hello, I'm " << m_nickname << std::endl;
	std::cout << "I'm a cat" << std::endl;
}

void CCat::CopyState(const ISerializable& from, ISerializable& to)
{
	// do nothing
}