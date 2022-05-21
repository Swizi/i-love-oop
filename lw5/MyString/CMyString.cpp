#include "CMyString.h"

CMyString::CMyString()
	: m_string(new char[1])
	, m_stringSize(0)
{
	m_string[0] = '\0';
}

CMyString::CMyString(const char* pString)
	: m_string(new char[strlen(pString) + 1])
	, m_stringSize(strlen(pString))
{
	if (m_stringSize != 0)
	{
		strcpy_s(m_string, m_stringSize + 1, pString);
	}
	m_string[m_stringSize] = '\0';
}

CMyString::CMyString(const char* pString, size_t length)
{
	if (strlen(pString) < length)
	{
		throw std::exception("The passed length is longer than the length of the passed string's length");
	}

	m_string = new char[length + 1];
	m_stringSize = length;
	for (int i = 0; i < m_stringSize; i++)
	{
		m_string[i] = pString[i];
	}
	m_string[m_stringSize] = '\0';
}

CMyString::CMyString(CMyString const& other)
{
	m_string = new char[other.GetLength() + 1];
	m_stringSize = other.GetLength();
	strcpy_s(m_string, m_stringSize+1, other.GetStringData());
}

CMyString::CMyString(CMyString&& other)
	: m_string(other.m_string)
	, m_stringSize(other.m_stringSize + 1)
{
	other.m_string = new char[1];
	other.m_string[0] = '\0';
	other.m_stringSize = 0;
}

CMyString::CMyString(std::string const& stlString)
	: m_string(new char[stlString.size() + 1])
	, m_stringSize(stlString.size())
{
	for (int i = 0; i < m_stringSize; i++)
	{
		m_string[i] = stlString[i];
	}
	m_string[stlString.size()] = '\0';
}

CMyString::~CMyString()
{
	delete[] m_string;
	m_stringSize = NULL;
}

size_t CMyString::GetLength()const
{
	return m_stringSize;
}

const char* CMyString::GetStringData()const
{
	return m_string;
}

CMyString CMyString::SubString(const size_t start, const size_t length)const
{
	if (start > m_stringSize - 1)
	{
		throw std::exception("Start index is more than length of string");
	}
	if (length > m_stringSize - 1 - start)
	{
		throw std::exception("The substring goes beyond the bounds of the string");
	}

	char* resultArray = new char[length];

	for (int i = 0; i < length; i++)
	{
		resultArray[i] = m_string[start + i];
	}

	return CMyString(resultArray, length);
}

void CMyString::Clear()
{
	delete[] m_string;
	m_string = new char[1];
	m_string[0] = '\0';
	m_stringSize = 0;
}

// =
CMyString& CMyString::operator=(const CMyString& other)
{
	if (*this == other)
	{
		return *this;
	}

	delete[] m_string;
	m_string = new char[other.GetLength() + 1];
	m_stringSize = other.GetLength();
	strcpy_s(m_string, m_stringSize + 1, other.GetStringData());
	m_string[m_stringSize] = '\0';

	return *this;
}

// && =
CMyString& CMyString::operator=(CMyString&& other)
{
	if (*this == other)
	{
		return *this;
	}

	delete[] m_string;
	m_string = other.m_string;
	m_stringSize = other.m_stringSize;
	other.m_string = new char[1]{'\0'};
	other.m_stringSize = 0;

	return *this;
}

// +
CMyString const operator+(const CMyString& leftOperand, const CMyString& rightOperand)
{
	char* resultArray = new char[leftOperand.GetLength() + rightOperand.GetLength() + 1];

	strncpy_s(resultArray, leftOperand.GetLength() + rightOperand.GetLength() + 1, leftOperand.GetStringData(), leftOperand.GetLength());
	strncat_s(resultArray, leftOperand.GetLength() + rightOperand.GetLength() + 1, rightOperand.GetStringData(), rightOperand.GetLength());

	return CMyString(resultArray);
}

// +=
CMyString operator+=(CMyString& leftOperand, const CMyString& rightOperand)
{
	leftOperand = leftOperand + rightOperand;
	return leftOperand;
}

// ==
bool const operator==(const CMyString& leftOperand, const CMyString& rightOperand)
{
	return strcmp(leftOperand.GetStringData(), rightOperand.GetStringData()) == 0;
}

// !=
bool const operator!=(const CMyString& leftOperand, const CMyString& rightOperand)
{
	return !(leftOperand == rightOperand);
}

// []
char const CMyString::operator[](const size_t index) const
{
	if (index > m_stringSize)
	{
		throw std::exception("Index is more than string size");
	}

	return m_string[index];
}

char& CMyString::operator[](const size_t index)
{
	if (index > m_stringSize)
	{
		throw std::exception("Index is more than string size");
	}

	return m_string[index];
}

// <
bool const operator<(const CMyString& leftOperand, const CMyString& rightOperand)
{
	return strcmp(leftOperand.GetStringData(), rightOperand.GetStringData()) < 0;
}

// <=
bool const operator<=(const CMyString& leftOperand, const CMyString& rightOperand)
{
	int result = strcmp(leftOperand.GetStringData(), rightOperand.GetStringData());

	return result < 0 || result == 0;
}

// >
bool const operator>(const CMyString& leftOperand, const CMyString& rightOperand)
{
	return strcmp(leftOperand.GetStringData(), rightOperand.GetStringData()) > 0;
}

// >=
bool const operator>=(const CMyString& leftOperand, const CMyString& rightOperand)
{
	int result = strcmp(leftOperand.GetStringData(), rightOperand.GetStringData());

	return result > 0 || result == 0;
}

// <<
std::ostream& operator<<(std::ostream& out, const CMyString& str)
{
	out << str.GetStringData();

	return out;
}

// >>
std::istream& operator>>(std::istream& in, CMyString& str)
{
	if (in)
	{
		in.seekg(0, in.end);
		size_t length = in.tellg();
		in.seekg(0, in.beg);
		char* inputStr = new char[length + 1];

		in.read(inputStr, length);
		inputStr[length] = '\0';

		CMyString result = CMyString(inputStr);
		str = result;
	}

	return in;
}