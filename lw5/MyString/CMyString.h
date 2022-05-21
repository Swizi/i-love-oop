#pragma once
#include "common_libs.h"

class CMyString
{
public:
	// конструктор по умолчанию
	CMyString();

	// конструктор, инициализирующий строку данными строки
    // с завершающим нулевым символом
	CMyString(const char* pString);

	// конструктор, инициализирующий строку данными из 
    // символьного массива заданной длины
	CMyString(const char* pString, size_t length);

	// конструктор копирования
	CMyString(CMyString const& other);

	// перемещающий конструктор (для компиляторов, совместимых с C++11)
	//  реализуется совместно с перемещающим оператором присваивания 
	CMyString(CMyString&& other);

	// конструктор, инициализирующий строку данными из 
    // строки стандартной библиотеки C++
	CMyString(std::string const& stlString);

	// деструктор класса - освобождает память, занимаемую символами строки
	~CMyString();

	// возвращает длину строки (без учета завершающего нулевого символа)
	size_t GetLength()const;

	// возвращает указатель на массив символов строки.
	// В конце массива обязательно должен быть завершающий нулевой символ
	// даже если строка пустая 
	const char* GetStringData()const;

	// возвращает подстроку с заданной позиции длиной не больше length символов
	CMyString SubString(const size_t start, const size_t length = SIZE_MAX)const;

	// очистка строки (строка становится снова нулевой длины)
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

