#pragma once
#include "common_libs.h"

class CMyIterator
{
public:
	using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = char;
    using pointer = char*;
    using reference = char&;

	CMyIterator();
	CMyIterator(char* first);

	CMyIterator operator++(int);
	CMyIterator operator--(int);
	CMyIterator operator++();
	CMyIterator operator--();

	reference operator*();
	pointer operator->();

	reference operator[](ptrdiff_t diff);

	ptrdiff_t operator-(CMyIterator& rightOperand) const;
	CMyIterator operator+(ptrdiff_t diff) const;
	friend CMyIterator operator+(ptrdiff_t diff, const CMyIterator& iterator);

	// ==
	friend bool const operator==(const CMyIterator& leftOperand, const CMyIterator& rightOperand);

	// !=
	friend bool const operator!=(const CMyIterator& leftOperand, const CMyIterator& rightOperand);

	// <
	friend bool const operator<(const CMyIterator& leftOperand, const CMyIterator& rightOperand);

	// <=
	friend bool const operator<=(const CMyIterator& leftOperand, const CMyIterator& rightOperand);

	// >
	friend bool const operator>(const CMyIterator& leftOperand, const CMyIterator& rightOperand);

	// >=
	friend bool const operator>=(const CMyIterator& leftOperand, const CMyIterator& rightOperand);

protected:
	pointer curr;
};