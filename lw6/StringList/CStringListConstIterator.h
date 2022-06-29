#pragma once
#include "CStringListIterator.h"

class CStringListConstIterator: public CStringListIterator
{
public:
	using pointer = const CNode*;
	using reference = const CNode&;

	CStringListConstIterator();
	CStringListConstIterator(const NodePtr first);
	CStringListConstIterator(CNode* first);

	CStringListConstIterator operator++(int);
	CStringListConstIterator operator--(int);
	CStringListConstIterator operator++();
	CStringListConstIterator operator--();

	reference operator*() const;
	pointer operator->() const;

	reference operator[](ptrdiff_t diff) const;
};
