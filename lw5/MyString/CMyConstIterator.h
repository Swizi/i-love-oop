#pragma once
#include "CMyIterator.h"

class CMyConstIterator : public CMyIterator
{
public:
    using pointer = const char*;
    using reference = const char&;

	CMyConstIterator(char* first);

	const CMyConstIterator operator++(int);
	const CMyConstIterator operator--(int);
	const CMyConstIterator operator++();
	const CMyConstIterator operator--();

	reference operator*() const;
	pointer operator->() const;

	reference operator[](ptrdiff_t diff);
};
