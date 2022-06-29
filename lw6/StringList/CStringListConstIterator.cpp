#include "CStringListConstIterator.h"

CStringListConstIterator::CStringListConstIterator()
	: CStringListIterator(nullptr)
{
}

CStringListConstIterator::CStringListConstIterator(const NodePtr first)
	: CStringListIterator(first)
{
}

CStringListConstIterator::CStringListConstIterator(CNode* first)
	: CStringListIterator(first)
{
}

CStringListConstIterator CStringListConstIterator::operator++(int)
{
	if (curr == nullptr)
	{
		throw std::logic_error("Iterator is pointing to null element");
	}
	if (curr->GetNext() == nullptr)
	{
		throw std::out_of_range("Going beyond the boundaries of the list 0");
	}
	CNode* retValue = curr;
	curr = curr->GetNext().get();

	return retValue;
}

CStringListConstIterator CStringListConstIterator::operator--(int)
{
	if (curr == nullptr)
	{
		throw std::logic_error("Iterator is pointing to null element");
	}
	if (curr->GetPrev() == nullptr)
	{
		throw std::out_of_range("Going beyond the boundaries of the list 0");
	}
	CNode* retValue = curr;
	curr = curr->GetPrev().get();

	return retValue;
}

CStringListConstIterator CStringListConstIterator::operator++()
{
	if (curr == nullptr)
	{
		throw std::logic_error("Iterator is pointing to null element");
	}
	if (curr->GetNext() == nullptr)
	{
		throw std::out_of_range("Going beyond the boundaries of the list 0");
	}
	CNode* retValue = curr->GetNext().get();
	curr = retValue;

	return retValue;
}

CStringListConstIterator CStringListConstIterator::operator--()
{
	if (curr == nullptr)
	{
		throw std::logic_error("Iterator is pointing to null element");
	}
	if (curr->GetPrev() == nullptr)
	{
		throw std::out_of_range("Going beyond the boundaries of the list 0");
	}
	CNode* retValue = curr->GetPrev().get();
	curr = retValue;

	return retValue;
}

CStringListConstIterator::reference CStringListConstIterator::operator*() const
{
	return *curr;
}

CStringListConstIterator::pointer CStringListConstIterator::operator->() const
{
	return curr;
}

CStringListConstIterator::reference CStringListConstIterator::operator[](ptrdiff_t diff) const
{
	CNode& retValue = *curr;

	if (diff > 0)
	{
		for (int i = 0; i < diff; i++)
		{
			retValue = *retValue.GetNext();
		}
	}
	else
	{
		for (int i = 0; i > diff; i--)
		{
			retValue = *retValue.GetNext();
		}
	}

	return retValue;
}