#include "CMyConstIterator.h"

CMyConstIterator::CMyConstIterator(char* first)
{
	curr = first;
}

const CMyConstIterator CMyConstIterator::operator++(int)
{
	return curr++;
}

const CMyConstIterator CMyConstIterator::operator--(int)
{
	return curr--;
}

const CMyConstIterator CMyConstIterator::operator++()
{
	return ++curr;
}

const CMyConstIterator CMyConstIterator::operator--()
{
	return --curr;
}

CMyConstIterator::reference CMyConstIterator::operator*() const
{
	return *curr;
}

CMyConstIterator::pointer CMyConstIterator::operator->() const
{
	return curr;
}

CMyConstIterator::reference CMyConstIterator::operator[](ptrdiff_t diff)
{
	return *(curr + diff);
}