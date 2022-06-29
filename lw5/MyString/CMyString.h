#pragma once
#include "common_libs.h"
#include "CMyIterator.h"
#include "CMyConstIterator.h"

class CMyString
{
public:
	// ����������� �� ���������
	CMyString();

	// �����������, ���������������� ������ ������� ������
    // � ����������� ������� ��������
	CMyString(const char* pString);

	// �����������, ���������������� ������ ������� �� 
    // ����������� ������� �������� �����
	CMyString(const char* pString, size_t length);

	// ����������� �����������
	CMyString(CMyString const& other);

	// ������������ ����������� (��� ������������, ����������� � C++11)
	//  ����������� ��������� � ������������ ���������� ������������ 
	CMyString(CMyString&& other) noexcept;

	// �����������, ���������������� ������ ������� �� 
    // ������ ����������� ���������� C++
	CMyString(std::string const& stlString);

	// ���������� ������ - ����������� ������, ���������� ��������� ������
	~CMyString();

	// ���������� ����� ������ (��� ����� ������������ �������� �������)
	size_t GetLength()const;

	// ���������� ��������� �� ������ �������� ������.
	// � ����� ������� ����������� ������ ���� ����������� ������� ������
	// ���� ���� ������ ������ 
	const char* GetStringData()const;

	// ���������� ��������� � �������� ������� ������ �� ������ length ��������
	CMyString SubString(const size_t start, const size_t length = SIZE_MAX)const;

	// ������� ������ (������ ���������� ����� ������� �����)
	void Clear();

	// =
	CMyString& operator=(const CMyString& other);

	// && =
	CMyString& operator=(CMyString&& other) noexcept;

	// []
	char const operator[](const size_t index) const;
	char& operator[](const size_t index);

	// CMyIterator
	CMyIterator begin() const;
	CMyIterator end() const;
	std::reverse_iterator<CMyIterator> rbegin() const;
	std::reverse_iterator<CMyIterator> rend() const;

	// CMyConstIterator
	CMyConstIterator cbegin() const;
	CMyConstIterator cend() const;
	std::reverse_iterator<CMyConstIterator> crbegin() const;
	std::reverse_iterator<CMyConstIterator> crend() const;

private:
	char* m_string;
	size_t m_stringSize;
};

// +
CMyString operator+(const CMyString& leftOperand, const CMyString& rightOperand);

// +=
CMyString& operator+=(CMyString& leftOperand, const CMyString& rightOperand);

// ==
bool operator==(const CMyString& leftOperand, const CMyString& rightOperand);

// !=
bool operator!=(const CMyString& leftOperand, const CMyString& rightOperand);

// <
bool operator<(const CMyString& leftOperand, const CMyString& rightOperand);

// <=
bool operator<=(const CMyString& leftOperand, const CMyString& rightOperand);

// >
bool operator>(const CMyString& leftOperand, const CMyString& rightOperand);

// >=
bool operator>=(const CMyString& leftOperand, const CMyString& rightOperand);

// <<
std::ostream& operator<<(std::ostream& out, const CMyString& str);

// >>
std::istream& operator>>(std::istream& in, CMyString& str);

