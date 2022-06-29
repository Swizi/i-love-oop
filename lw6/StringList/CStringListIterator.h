#pragma once
#include "CNode.h"

class CStringListIterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = CNode;
	using pointer = CNode*;
	using reference = CNode&;

	CStringListIterator();
	CStringListIterator(const NodePtr first);
	CStringListIterator(pointer first);

	CStringListIterator operator++(int);
	CStringListIterator operator--(int);
	CStringListIterator operator++();
	CStringListIterator operator--();

	reference operator*() const;
	pointer operator->() const;

	reference operator[](ptrdiff_t diff) const;

	ptrdiff_t operator-(const CStringListIterator& rightOperand) const;
	CStringListIterator operator+(ptrdiff_t diff) const;
	CStringListIterator operator-(ptrdiff_t diff) const;
	friend CStringListIterator operator+(ptrdiff_t diff, const CStringListIterator& iterator);

	// ==
	friend bool operator==(const CStringListIterator& leftOperand, const CStringListIterator& rightOperand);

	// !=
	friend bool operator!=(const CStringListIterator& leftOperand, const CStringListIterator& rightOperand);

	// <
	friend bool operator<(const CStringListIterator& leftOperand, const CStringListIterator& rightOperand);

	// <=
	friend bool operator<=(const CStringListIterator& leftOperand, const CStringListIterator& rightOperand);

	// >
	friend bool operator>(const CStringListIterator& leftOperand, const CStringListIterator& rightOperand);

	// >=
	friend bool operator>=(const CStringListIterator& leftOperand, const CStringListIterator& rightOperand);

protected:
	pointer curr;
};