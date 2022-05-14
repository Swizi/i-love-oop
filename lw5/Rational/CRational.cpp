#include "CRational.h"
#include "common_libs.h"

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{
}

CRational::CRational(int value)
	: m_numerator(value)
	, m_denominator(1)
{
}

CRational::CRational(int numerator, int denominator)
{
	if (denominator == 0)
	{
		numerator = 0;
		denominator = 1;
	}

	if (denominator < 0)
	{
		numerator *= -1;
		denominator *= -1;
	}

	while (gcd(abs(numerator), denominator) != 1)
	{
		int gcdNum = gcd(abs(numerator), denominator);
		numerator /= gcdNum;
		denominator /= gcdNum;
	}

	m_numerator = numerator;
	m_denominator = denominator;
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return static_cast<double>(m_numerator) / m_denominator;
}

// ”нарный плюс
CRational const CRational::operator +()
{
	return *this;
}

// ”нарный минус
CRational const CRational::operator -()
{
	m_numerator *= -1;

	return *this;
}

// Ѕинарный плюс
CRational const operator+(const CRational& leftOperand, const CRational& rightOperand)
{
	if (leftOperand.GetDenominator() > INT_MAX / rightOperand.GetDenominator())
	{
		throw std::exception("Operation was not executed. Integer overflow received");
	}
	if (leftOperand.GetNumerator() >= 0)
	{
		if (leftOperand.GetNumerator() > INT_MAX / rightOperand.GetDenominator())
		{
			throw std::exception("Operation was not executed. Integer overflow received");
		}
	}
	else {
		if (leftOperand.GetNumerator() < INT_MIN / rightOperand.GetDenominator())
		{
			throw std::exception("Operation was not executed. Integer overflow received");
		}
	}
	if (rightOperand.GetNumerator() >= 0)
	{
		if (rightOperand.GetNumerator() > INT_MAX / leftOperand.GetDenominator())
		{
			throw std::exception("Operation was not executed. Integer overflow received");
		}
	}
	else {
		if (rightOperand.GetNumerator() < INT_MIN / leftOperand.GetDenominator())
		{
			throw std::exception("Operation was not executed. Integer overflow received");
		}
	}

	if (leftOperand.GetNumerator() >= 0 && rightOperand.GetNumerator() >= 0)
	{
		if (leftOperand.GetNumerator() * rightOperand.GetDenominator() > INT_MAX - rightOperand.GetNumerator() * leftOperand.GetDenominator())
		{
			throw std::exception("Operation was not executed. Integer overflow received");
		}
	}
	if (leftOperand.GetNumerator() < 0 && rightOperand.GetNumerator() < 0)
	{
		if (leftOperand.GetNumerator() * rightOperand.GetDenominator() < INT_MIN - rightOperand.GetNumerator() * leftOperand.GetDenominator())
		{
			throw std::exception("Operation was not executed. Integer overflow received");
		}
	}

	return CRational(leftOperand.GetNumerator() * rightOperand.GetDenominator() + rightOperand.GetNumerator() * leftOperand.GetDenominator(), leftOperand.GetDenominator() * rightOperand.GetDenominator());
}

// Ѕинарный минус
CRational const operator-(const CRational& leftOperand, const CRational& rightOperand)
{
	CRational rightInvertedOperand = CRational(rightOperand.GetNumerator(), rightOperand.GetDenominator());
	-rightInvertedOperand;
	CRational result = leftOperand + rightInvertedOperand;

	return result;
}

// +=
CRational operator+=(CRational& leftOperand, const CRational& rightOperand)
{
	CRational result = leftOperand + rightOperand;
	
	leftOperand = result;

	return leftOperand;
}

// -=
CRational operator-=(CRational& leftOperand, const CRational& rightOperand)
{
	CRational result = leftOperand - rightOperand;

	leftOperand = result;

	return leftOperand;
}

// *
CRational const operator*(const CRational& leftOperand, const CRational& rightOperand)
{
	if (leftOperand.GetNumerator() > INT_MAX / rightOperand.GetNumerator() || leftOperand.GetDenominator() > INT_MAX / rightOperand.GetDenominator())
	{
		throw std::exception("Operation was not executed. Integer overflow received");
	}

	return CRational(leftOperand.GetNumerator() * rightOperand.GetNumerator(), leftOperand.GetDenominator() * rightOperand.GetDenominator());
}

// /
CRational const operator/(const CRational& leftOperand, const CRational& rightOperand)
{
	if (leftOperand.GetNumerator() > INT_MAX / rightOperand.GetDenominator() || leftOperand.GetDenominator() > INT_MAX / rightOperand.GetNumerator())
	{
		throw std::exception("Operation was not executed. Integer overflow received");
	}

	return CRational(leftOperand.GetNumerator() * rightOperand.GetDenominator(), leftOperand.GetDenominator() * rightOperand.GetNumerator());
}

// *=
CRational operator*=(CRational& leftOperand, const CRational& rightOperand)
{
	CRational result = leftOperand * rightOperand;

	leftOperand = result;

	return leftOperand;
}

// /=
CRational operator/=(CRational& leftOperand, const CRational& rightOperand)
{
	CRational result = leftOperand / rightOperand;

	leftOperand = result;

	return leftOperand;
}

// ==
bool const operator==(const CRational& leftOperand, const CRational& rightOperand)
{
	return leftOperand.GetNumerator() == rightOperand.GetNumerator() && leftOperand.GetDenominator() == rightOperand.GetDenominator();
}

// !=
bool const operator!=(const CRational& leftOperand, const CRational& rightOperand)
{
	return !(leftOperand == rightOperand);
}

bool const operator<(const CRational& leftOperand, const CRational& rightOperand)
{
	return leftOperand.GetNumerator() * rightOperand.GetDenominator() < rightOperand.GetNumerator() * leftOperand.GetDenominator();
}

bool const operator<=(const CRational& leftOperand, const CRational& rightOperand)
{
	return leftOperand.GetNumerator() * rightOperand.GetDenominator() <= rightOperand.GetNumerator() * leftOperand.GetDenominator();
}

bool const operator>(const CRational& leftOperand, const CRational& rightOperand)
{
	return !(leftOperand <= rightOperand);
}

bool const operator>=(const CRational& leftOperand, const CRational& rightOperand)
{
	return !(leftOperand < rightOperand);
}

void operator<<(std::ostream& out, const CRational& num)
{
	out << num.GetNumerator() << "/" << num.GetDenominator();
}

void operator>>(std::istream& in, CRational& num)
{
	std::string inputStr = std::string();
	in >> inputStr;

	const size_t separatorIndex = inputStr.find('/');
	if (separatorIndex == std::string::npos)
	{
		throw std::exception("Incorrect rational number. / was not found");
	}
	int numerator = 0;
	try
	{
		numerator = std::stoi(inputStr.substr(0, separatorIndex));
	} catch(const std::exception& e)
	{
		throw std::exception("Incorrect rational number. Numerator is not correct");
	}
	int denominator = 0;
	try
	{
		denominator = std::stoi(inputStr.substr(separatorIndex+1, inputStr.size() - separatorIndex));
	}
	catch (const std::exception& e)
	{
		throw std::exception("Incorrect rational number. Denominator is not correct");
	}

	num = CRational(numerator, denominator);
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	std::pair<int, CRational> result = { 0, CRational() };

	result.first = m_numerator / m_denominator;
	result.second = CRational(m_numerator - m_denominator * result.first, m_denominator);

	return result;
}