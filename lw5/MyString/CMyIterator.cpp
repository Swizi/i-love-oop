#include "CMyIterator.h"

CMyIterator::CMyIterator()
	: curr(nullptr)
{
}

CMyIterator::CMyIterator(char* first)
	: curr(first)
{
}

CMyIterator CMyIterator::operator++(int)
{
	return curr++;
}

CMyIterator CMyIterator::operator--(int)
{
	return curr--;
}

CMyIterator CMyIterator::operator++()
{
	return ++curr;
}

CMyIterator CMyIterator::operator--()
{
	return --curr;
}

CMyIterator::reference CMyIterator::operator*()
{
	return *curr;
}

CMyIterator::pointer CMyIterator::operator->()
{
	return curr;
}

CMyIterator::reference CMyIterator::operator[](ptrdiff_t diff)
{
	return *(curr + diff);
}

ptrdiff_t CMyIterator::operator-(CMyIterator& rightOperand) const
{
	return curr - rightOperand.curr;
}

CMyIterator CMyIterator::operator+(ptrdiff_t diff) const
{
	auto it = curr;

	it = (it + diff);

	return it;
}

CMyIterator operator+(ptrdiff_t diff, const CMyIterator& iterator)
{
	return iterator + diff;
}

// ==
bool operator==(const CMyIterator& leftOperand, const CMyIterator& rightOperand)
{
	return leftOperand.curr == rightOperand.curr;
}

// !=
bool operator!=(const CMyIterator& leftOperand, const CMyIterator& rightOperand)
{
	return leftOperand.curr != rightOperand.curr;
}

// <
bool operator<(const CMyIterator& leftOperand, const CMyIterator& rightOperand)
{
	return leftOperand.curr < rightOperand.curr;
}

// <=
bool operator<=(const CMyIterator& leftOperand, const CMyIterator& rightOperand)
{
	return leftOperand.curr <= rightOperand.curr;
}

// >
bool operator>(const CMyIterator& leftOperand, const CMyIterator& rightOperand)
{
	return leftOperand.curr > rightOperand.curr;
}

// >=
bool operator>=(const CMyIterator& leftOperand, const CMyIterator& rightOperand)
{
	return leftOperand.curr >= rightOperand.curr;
}
