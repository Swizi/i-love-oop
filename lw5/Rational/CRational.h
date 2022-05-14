#pragma once
#include "common_libs.h"

class CRational
{
public:
	// ������������ ������������ �����, ������ ���� (0/1)
	CRational();

	// ������������ ������������ �����, ������ value (value/1)
	CRational(int value);

	// ������������ ������������ �����, ������ numerator/denominator
	// ������������ ����� ������ ��������� � ��������������� ����:
	//	����������� ������������� (��������� ����� ���� �������������)
	//	��������� � ����������� �� ����� ����� ��������� (6/8 => 3/4 � �.�.)
	// ���� ����������� ����� ����, ������ ����������������� ������������ �����, ������ ����,
	// ���� ������ ���� ��������� ���������� std::invalid_argument.
	CRational(int numerator, int denominator);

	// ���������� ���������
	int GetNumerator() const;

	// ���������� ����������� (����������� �����)
	int GetDenominator() const;

	// ���������� ��������� ��������� � ����������� � ���� ����� double
	double ToDouble() const;

	// ������� ����
	CRational const operator +();
	// ������� �����
	CRational const operator-();

	// >>
	/*void operator>>(std::istream& in);*/

private:
	int m_numerator;
	int m_denominator;
};

// �������� ����
CRational const operator+(const CRational& leftOperand, const CRational& rightOperand);

// �������� �����
CRational const operator-(const CRational& leftOperand, const CRational& rightOperand);

// +=
CRational operator+=(CRational& leftOperand, const CRational& rightOperand);

// -=
CRational operator-=(CRational& leftOperand, const CRational& rightOperand);

// *
CRational const operator*(const CRational& leftOperand, const CRational& rightOperand);

// /
CRational const operator/(const CRational& leftOperand, const CRational& rightOperand);

// *=
CRational operator*=(CRational& leftOperand, const CRational& rightOperand);

// /=
CRational operator/=(CRational& leftOperand, const CRational& rightOperand);

// ==
bool const operator==(const CRational& leftOperand, const CRational& rightOperand);

// !=
bool const operator!=(const CRational& leftOperand, const CRational& rightOperand);

// <
bool const operator<(const CRational& leftOperand, const CRational& rightOperand);

// <=
bool const operator<=(const CRational& leftOperand, const CRational& rightOperand);

// >
bool const operator>(const CRational& leftOperand, const CRational& rightOperand);

// >=
bool const operator>=(const CRational& leftOperand, const CRational& rightOperand);

// <<
void operator<<(std::ostream& out, const CRational& num);

// >>
void operator>>(std::istream& in, CRational& num);