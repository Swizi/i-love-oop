#pragma once
#include "common_libs.h"

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
	CMyString(CMyString&& other);

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
	CMyString& operator=(CMyString&& other);

	// []
	char const operator[](const size_t index) const;
	char& operator[](const size_t index);

private:
	char* m_string;
	size_t m_stringSize;
};

// +
CMyString const operator+(const CMyString& leftOperand, const CMyString& rightOperand);

// +=
CMyString operator+=(CMyString& leftOperand, const CMyString& rightOperand);

// ==
bool const operator==(const CMyString& leftOperand, const CMyString& rightOperand);

// !=
bool const operator!=(const CMyString& leftOperand, const CMyString& rightOperand);

// <
bool const operator<(const CMyString& leftOperand, const CMyString& rightOperand);

// <=
bool const operator<=(const CMyString& leftOperand, const CMyString& rightOperand);

// >
bool const operator>(const CMyString& leftOperand, const CMyString& rightOperand);

// >=
bool const operator>=(const CMyString& leftOperand, const CMyString& rightOperand);

// <<
std::ostream& operator<<(std::ostream& out, const CMyString& str);

// >>
std::istream& operator>>(std::istream& in, CMyString& str);

