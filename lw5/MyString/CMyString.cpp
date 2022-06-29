#include "CMyString.h"

CMyString::CMyString()
	: m_string(nullptr)
	, m_stringSize(0)
{
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

CMyString::CMyString(const char* pString, const size_t length)
	: m_string(new char[length + 1])
	, m_stringSize(length)
{
	memcpy(m_string, pString, length);
	m_string[m_stringSize] = '\0';
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.GetStringData(), other.GetLength())
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_string(other.m_string)
	, m_stringSize(other.m_stringSize)
{
	// TODO: Подумать, как можно не выделять памят, чтобы не выбрасывать исключения при new
	other.m_string = nullptr;
	other.m_stringSize = 0;
	// TODO: Убрать исключение(std::swap)
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.c_str(), stlString.size())
{
	// TODO: использовать forwarding constructor
}

CMyString::~CMyString()
{
	delete[] m_string;
}

size_t CMyString::GetLength()const
{
	return m_stringSize;
}

const char* CMyString::GetStringData()const
{
	if (m_stringSize == 0)
	{
		return "\0";
	}

	return m_string;
}

CMyString CMyString::SubString(const size_t start, const size_t length)const
{
	if (start > m_stringSize)
	{
		throw std::out_of_range("Start index is greater than length of string");
	}
	if (length > m_stringSize - start)
	{
		throw std::length_error("The substring exceeds the bounds of the string");
	}

	//char* resultArray = new char[length];

	//for (int i = 0; i < length; i++)
	//{
	//	resultArray[i] = m_string[start + i];
	//}

	// TODO: освободить память
	// не выделять память
	/*CMyString result = CMyString(&m_string[start], length);*/
	//delete[] resultArray;

	return CMyString(&m_string[start], length);
}

void CMyString::Clear()
{
	delete[] m_string;
	// TODO: разобраться с исключением при выделении памяти
	m_string = nullptr;
	m_stringSize = 0;
}

// =
CMyString& CMyString::operator=(const CMyString& other)
{
	if (this == &other)
	{
		return *this;
	}

	char* reserve = new char[other.GetLength() + 1];
	delete[] m_string;
	m_string = reserve;
	m_stringSize = other.GetLength();
	if (other.GetLength() != 0)
	{
		memcpy(m_string, other.GetStringData() , m_stringSize);
	}
	m_string[m_stringSize] = '\0';

	return *this;
}

// && =
CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	// TODO: конструктор не должен бросать исключений
	// TODO: использовать оператор swap
	delete[] m_string;
	m_string = other.m_string;
	m_stringSize = other.m_stringSize;
	other.m_string = nullptr;
	other.m_stringSize = 0;

	return *this;
}

// +
CMyString operator+(const CMyString& leftOperand, const CMyString& rightOperand)
{
	char* resultArray = new char[leftOperand.GetLength() + rightOperand.GetLength() + 1];

	// TODO: скопирует до \0
	// TODO: освободить память resultArray
	memcpy(resultArray, leftOperand.GetStringData(), leftOperand.GetLength());
	for (size_t i = leftOperand.GetLength(); i < leftOperand.GetLength() + rightOperand.GetLength(); i++)
	{
		resultArray[i] = rightOperand.GetStringData()[i - leftOperand.GetLength()];
	}

	CMyString resultString = CMyString(resultArray, leftOperand.GetLength() + rightOperand.GetLength());
	delete[] resultArray;

	return resultString;
}

// +=
CMyString& operator+=(CMyString& leftOperand, const CMyString& rightOperand)
{
	// Будет некорректно работать так: (a+=b)+=c;
	leftOperand = leftOperand + rightOperand;
	return leftOperand;
}

// ==
bool operator==(const CMyString& leftOperand, const CMyString& rightOperand)
{
	// TODO: использовать memcmp
	if (leftOperand.GetLength() == rightOperand.GetLength())
	{
		if (leftOperand.GetLength() == 0)
		{
			return true;
		}
		return memcmp(leftOperand.GetStringData(), rightOperand.GetStringData(), rightOperand.GetLength()) == 0;
	}

	return false;
}

// !=
bool operator!=(const CMyString& leftOperand, const CMyString& rightOperand)
{
	return !(leftOperand == rightOperand);
}

// []
char const CMyString::operator[](const size_t index) const
{
	if (index >= m_stringSize)
	{
		throw std::out_of_range("Index is more than string size");
	}

	return m_string[index];
}

char& CMyString::operator[](const size_t index)
{
	if (index >= m_stringSize)
	{
		throw std::out_of_range("Index is more than string size");
	}

	return m_string[index];
}

// <
bool operator<(const CMyString& leftOperand, const CMyString& rightOperand)
{
	// TODO: std lexicographical compare
	return std::lexicographical_compare(leftOperand.GetStringData(), &leftOperand.GetStringData()[leftOperand.GetLength()],
		rightOperand.GetStringData(), &rightOperand.GetStringData()[rightOperand.GetLength()]);

	//if (leftOperand.GetLength() <= rightOperand.GetLength())
	//{
	//	if (memcmp(leftOperand.GetStringData(), rightOperand.GetStringData(), leftOperand.GetLength()) == 0)
	//	{
	//		return leftOperand.GetLength() < rightOperand.GetLength();
	//	}
	//	return memcmp(leftOperand.GetStringData(), rightOperand.GetStringData(), leftOperand.GetLength()) < 0;
	//}

	//if (memcmp(leftOperand.GetStringData(), rightOperand.GetStringData(), rightOperand.GetLength()) == 0)
	//{
	//	return leftOperand.GetLength() < rightOperand.GetLength();
	//}
	//return memcmp(leftOperand.GetStringData(), rightOperand.GetStringData(), rightOperand.GetLength()) < 0;
}

// TODO: убрать const у bool
// <=
bool operator<=(const CMyString& leftOperand, const CMyString& rightOperand)
{
	return leftOperand < rightOperand || leftOperand == rightOperand;
}

// >
bool operator>(const CMyString& leftOperand, const CMyString& rightOperand)
{
	return !(leftOperand <= rightOperand);
}

// >=
bool operator>=(const CMyString& leftOperand, const CMyString& rightOperand)
{
	return !(leftOperand < rightOperand);
}

// <<
std::ostream& operator<<(std::ostream& out, const CMyString& str)
{
	// TODO: исправить вывод строки с нулевым символом в середине
	/*out << str.GetStringData();*/
	for (size_t i = 0; i < str.GetLength(); i++)
	{
		out << str[i];
	}

	return out;
}

// >>
std::istream& operator>>(std::istream& in, CMyString& str)
{
	if (in)
	{
		std::vector<char> inputStr;
		char ch;
		size_t length = 0;
		while (!(std::isspace(in.peek())) && in.get(ch))
			inputStr.push_back(ch);
		inputStr.push_back('\0');

		CMyString result = CMyString(inputStr.data(), inputStr.size());
		str = result;
	}

	return in;
}

// CMyIterator

CMyIterator CMyString::begin() const
{
	return m_string;
}

CMyIterator CMyString::end() const
{
	return m_string + m_stringSize;
}

std::reverse_iterator<CMyIterator> CMyString::rbegin() const
{
	return std::make_reverse_iterator(end());
}

std::reverse_iterator<CMyIterator> CMyString::rend() const
{
	return std::make_reverse_iterator(begin());
}

// CMyConstIterator

CMyConstIterator CMyString::cbegin() const
{
	return m_string;
}
CMyConstIterator CMyString::cend() const
{
	return m_string + m_stringSize;
}

std::reverse_iterator<CMyConstIterator> CMyString::crbegin() const
{
	return std::make_reverse_iterator(cend());
}

std::reverse_iterator<CMyConstIterator> CMyString::crend() const
{
	return std::make_reverse_iterator(cbegin());
}