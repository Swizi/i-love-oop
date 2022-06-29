#include "CStringListIterator.h"

CStringListIterator::CStringListIterator()
	: curr(nullptr)
{
}

CStringListIterator::CStringListIterator(const NodePtr first)
	: curr(first.get())
{
}

CStringListIterator::CStringListIterator(pointer first)
	: curr(first)
{
}

CStringListIterator CStringListIterator::operator++(int)
{
	if (curr->GetIsFictitious())
	{
		throw std::logic_error("Can not increment end list iterator");
	}
	CStringListIterator::pointer retValue = curr;
	curr = curr->GetNext().get();

	return retValue;
}

CStringListIterator CStringListIterator::operator--(int)
{
	if (curr->GetPrev()->GetIsFictitious())
	{
		throw std::logic_error("Can not decrement begin list iterator");
	}
	CStringListIterator::pointer retValue = curr;
	curr = curr->GetPrev().get();

	return retValue;
}

CStringListIterator CStringListIterator::operator++()
{
	if (curr->GetIsFictitious())
	{
		throw std::logic_error("Can not increment end list iterator");
	}
	CStringListIterator::pointer retValue = curr->GetNext().get();
	curr = retValue;

	return retValue;
}

CStringListIterator CStringListIterator::operator--()
{
	if (curr->GetPrev()->GetIsFictitious())
	{
		throw std::logic_error("Can not decrement begin list iterator");
	}
	CStringListIterator::pointer retValue = curr->GetPrev().get();
	curr = retValue;

	return retValue;
}

CStringListIterator::reference CStringListIterator::operator*() const
{
	return *curr;
}

CStringListIterator::pointer CStringListIterator::operator->() const
{
	return curr;
}

CStringListIterator::reference CStringListIterator::operator[](ptrdiff_t diff) const
{
	if (curr->GetIsFictitious())
	{
		throw std::logic_error("Can not get element of from end list");
	}
	CStringListIterator::reference retValue = *curr;

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

ptrdiff_t CStringListIterator::operator-(const CStringListIterator& rightOperand) const
{
	CStringListIterator::reference temp = *curr;
	ptrdiff_t diff = 0;
	while (temp != *rightOperand)
	{
		diff++;
		temp = *temp.GetPrev();
	}
	if (temp.GetPrev().get() == rightOperand)
	{
		return diff;
	}

	temp = *curr;
	diff = 0;
	while (temp != *rightOperand)
	{
		diff--;
		temp = *temp.GetNext();
	}
	if (temp.GetNext().get() == rightOperand)
	{
		return diff;
	}

	return -1;
}

CStringListIterator CStringListIterator::operator+(ptrdiff_t diff) const
{
	auto itEl = curr;

	if (diff > 0)
	{
		for (int i = 0; i < diff; i++)
		{
			itEl = itEl->GetNext().get();
		}
	}
	else
	{
		for (int i = 0; i > diff; i--)
		{
			itEl = itEl->GetPrev().get();
		}
	}

	return itEl;
}

CStringListIterator CStringListIterator::operator-(ptrdiff_t diff) const
{
	auto itEl = curr;

	if (diff > 0)
	{
		for (int i = 0; i < diff; i++)
		{
			itEl = itEl->GetPrev().get();
		}
	}
	else
	{
		for (int i = 0; i > diff; i--)
		{
			itEl = itEl->GetNext().get();
		}
	}

	return itEl;
}

CStringListIterator operator+(ptrdiff_t diff, const CStringListIterator& iterator)
{
	auto it = iterator;

	if (diff > 0)
	{
		for (int i = 0; i < diff; i++)
		{
			it = it.curr->GetNext().get();
		}
	}
	else
	{
		for (int i = 0; i > diff; i--)
		{
			it = it.curr->GetPrev().get();
		}
	}

	return it;
}

// ==
bool operator==(const CStringListIterator& leftOperand, const CStringListIterator& rightOperand)
{
	return leftOperand.curr == rightOperand.curr;
}

// !=
bool operator!=(const CStringListIterator& leftOperand, const CStringListIterator& rightOperand)
{
	return leftOperand.curr != rightOperand.curr;
}

// <
bool operator<(const CStringListIterator& leftOperand, const CStringListIterator& rightOperand)
{
	return leftOperand.curr < rightOperand.curr;
}

// <=
bool operator<=(const CStringListIterator& leftOperand, const CStringListIterator& rightOperand)
{
	return leftOperand.curr <= rightOperand.curr;
}

// >
bool operator>(const CStringListIterator& leftOperand, const CStringListIterator& rightOperand)
{
	return leftOperand.curr > rightOperand.curr;
}

// >=
bool operator>=(const CStringListIterator& leftOperand, const CStringListIterator& rightOperand)
{
	return leftOperand.curr >= rightOperand.curr;
}