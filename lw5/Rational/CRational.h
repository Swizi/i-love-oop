#pragma once
#include "common_libs.h"

class CRational
{
public:
	//  онструирует рациональное число, равное нулю (0/1)
	CRational();

	//  онструирует рациональное число, равное value (value/1)
	CRational(int value);

	//  онструирует рациональное число, равное numerator/denominator
	// –ациональное число должно хранитьс€ в нормализованном виде:
	//	знаменатель положительный (числитель может быть отрицательным)
	//	числитель и знаменатель не имеют общиз делителей (6/8 => 3/4 и т.п.)
	// ≈сли знаменатель равен нулю, должно сконструироватьс€ рациональное число, равное нулю,
	// либо должно быть выброшено исключение std::invalid_argument.
	CRational(int numerator, int denominator);

	// ¬озвращает числитель
	int GetNumerator() const;

	// ¬озвращает знаменатель (натуральное число)
	int GetDenominator() const;

	// ¬озвращает отношение числител€ и знаменател€ в виде числа double
	double ToDouble() const;

	// ”нарный плюс
	CRational operator +();
	// ”нарный минус
	CRational operator-();

	// ¬озвращает представление рационального числа в виде смешанной дроби
	std::pair<int, CRational> ToCompoundFraction() const;

private:
	int m_numerator;
	int m_denominator;
};

// Ѕинарный плюс
CRational operator+(const CRational& leftOperand, const CRational& rightOperand);

// Ѕинарный минус
CRational operator-(const CRational& leftOperand, const CRational& rightOperand);

// +=
CRational operator+=(CRational& leftOperand, const CRational& rightOperand);

// -=
CRational operator-=(CRational& leftOperand, const CRational& rightOperand);

// *
CRational operator*(const CRational& leftOperand, const CRational& rightOperand);

// /
CRational operator/(const CRational& leftOperand, const CRational& rightOperand);

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