#pragma once

template <typename T>
class CMyArray
{
public:
	CMyArray() = default;

	CMyArray(const T* arr, const size_t size)
		: m_myArray(size != 0 ? new T[size * 2] : nullptr)
		, m_size(size)
		, m_capacity(size * 2)
	{
		memcpy(m_myArray, arr, size);
	}

	// Констуктор копирования
	CMyArray(CMyArray const& other)
		: CMyArray(other.GetArray(), other.Count())
	{
	}

	// Конструктор перемещения
	CMyArray(CMyArray&& other) noexcept
		: m_myArray(other.GetArray())
		, m_size(other.Count())
		, m_capacity(m_size * 2)
	{
		other.m_myArray = nullptr;
		other.m_size = 0;
	}

	// Перегруженные операторы
	// =
	CMyArray& operator=(const CMyArray& other)
	{
		if (this == &other)
		{
			return *this;
		}

		T* reserve = new T[other.Count()];
		delete[] m_myArray;
		m_myArray = other.GetArray();
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		if (other.m_size != 0)
		{
			memcpy(m_myArray, other.m_myArray, m_size);
		}

		return *this;
	}

	// && =
	CMyArray& operator=(CMyArray&& other) noexcept
	{
		if (this == &other)
		{
			return *this;
		}

		delete[] m_myArray;
		m_myArray = other.m_myArray;
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		other.m_myArray = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;

		return *this;
	}

	T& operator[](const size_t index) const
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index is more than the array size");
		}

		return m_myArray[index];
	}

	void Insert(const T& el)
	{
		if (m_size == m_capacity)
		{
			if (m_size == 0)
			{
				m_myArray = new T[2];
				m_size = 0;
				m_capacity = 2;
			}
			else
			{
				CMyArray newArray = CMyArray(m_myArray, m_size);
				m_myArray = newArray.GetArray();
				m_capacity = m_size * 2;
			}
		}

		m_myArray[m_size] = el;
		m_size++;
	}

	size_t Count() const
	{
		return m_size;
	}
	//void Resize(const size_t index);
	//void Clear();

	//// Итераторы
	//CMyArrayIterator begin();
	//CMyArrayIterator end();
	//std::reverse_iterator<CMyArrayIterator> rbegin();
	//std::reverse_iterator<CMyArrayIterator> rend();

	T* GetArray() const
	{
		return m_myArray;
	}
private:
	T* m_myArray = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;
};