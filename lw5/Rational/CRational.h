#pragma once
#include "common_libs.h"

class CRational
{
public:
	// Конструирует рациональное число, равное нулю (0/1)
	CRational();

	// Конструирует рациональное число, равное value (value/1)
	CRational(int value);

	// Конструирует рациональное число, равное numerator/denominator
	// Рациональное число должно храниться в нормализованном виде:
	//	знаменатель положительный (числитель может быть отрицательным)
	//	числитель и знаменатель не имеют общиз делителей (6/8 => 3/4 и т.п.)
	// Если знаменатель равен нулю, должно сконструироваться рациональное число, равное нулю,
	// либо должно быть выброшено исключение std::invalid_argument.
	CRational(int numerator, int denominator);

	// Возвращает числитель
	int GetNumerator() const;

	// Возвращает знаменатель (натуральное число)
	int GetDenominator() const;

	// Возвращает отношение числителя и знаменателя в виде числа double
	double ToDouble() const;

	// Унарный плюс
	CRational const operator +();
	// Унарный минус
	CRational const operator-();

	// >>
	/*void operator>>(std::istream& in);*/

private:
	int m_numerator;
	int m_denominator;
};

// Бинарный плюс
CRational const operator+(const CRational& leftOperand, const CRational& rightOperand);

// Бинарный минус
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