#pragma once
#include <iterator>
#include <stdexcept>

template <typename T>
class CMyArray
{
	// TODO: пользователь должен иметь возможность объ€вить итератор самосто€тельно
	class CMyIterator
	{
	public:
		// TODO: заменить forward_iterator_tag
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		CMyIterator()
			: curr(nullptr)
		{
		}
		CMyIterator(T* first)
			: curr(first)
		{
		}

		CMyIterator operator++(int)
		{
			return curr++;
		}
		CMyIterator operator--(int)
		{
			return curr--;
		}
		CMyIterator operator++()
		{
			return ++curr;
		}
		CMyIterator operator--()
		{
			return --curr;
		}

		// TODO: добавить операторы + - += -=

		// TODO: метод должен быть константным
		reference operator*()
		{
			return *curr;
		}
		// TODO: метод должен быть константным
		pointer operator->()
		{
			return curr;
		}

		reference operator[](ptrdiff_t diff)
		{
			return *(curr + diff);
		}
		// TODO: добавить все виды сравнени€

		bool operator!=(const CMyIterator& rightOperand) const
		{
			return curr != rightOperand.curr;
		}
	protected:
		// TODO: m_curr
		pointer curr;
	};

public:
	CMyArray() = default;

	CMyArray(const T* arr, const size_t size)
		: m_myArray(size != 0 ? new T[size * 2] : nullptr)
		, m_size(size)
		, m_capacity(size * 2)
	{
		// TODO: new T[] конструирует, а нужно просто выдел€ть пам€ть
		// TODO: placement new
		// TODO: construct_at
		for (int i = 0; i < size; i++)
		{
			m_myArray[i] = arr[i];
		}
	}

	~CMyArray()
	{
		if (m_myArray != nullptr)
		{
			delete[] m_myArray;
		}
	}

	//  онстуктор копировани€
	CMyArray(CMyArray const& other)
		: CMyArray(other.GetArray(), other.Count())
	{
	}

	//  онструктор перемещени€
	CMyArray(CMyArray&& other) noexcept
		: m_myArray(other.GetArray())
		, m_size(other.Count())
		, m_capacity(m_size * 2)
	{
		other.m_myArray = nullptr;
		other.m_size = 0;
		// TODO: other.m_capacity
	}

	// ѕерегруженные операторы
	// =
	CMyArray& operator=(const CMyArray& other)
	{
		if (this == &other)
		{
			return *this;
		}

		T* reserve = other.m_size != 0 ? new T[other.m_size] : nullptr;
		for (size_t i = 0; i < other.m_size; i++)
		{
			// TODO: = может выбросить исключение, утечка пам€ти
			reserve[i] = other[i];
		}
		delete[] m_myArray;
		m_myArray = reserve;
		m_size = other.m_size;
		m_capacity = other.m_capacity;

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

	template <class AnotherT>
	CMyArray<T>& operator=(const CMyArray<AnotherT>& rightOperand)
	{
		T* reserve = new T[rightOperand.Count() * 2];
		m_myArray = reserve;
		for (size_t i = 0; i < rightOperand.Count(); i++)
		{
			// TODO: = может выбросить исключение, утечка пам€ти
			m_myArray[i] = static_cast<T>(rightOperand[i]);
		}
		m_size = rightOperand.Count();
		m_capacity = m_size * 2;

		return *this;
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
				const T* reserve = m_myArray;
				m_myArray = new T[m_size * 2];
				for (size_t i = 0; i < m_size; i++)
				{
					// TODO: утечка пам€ти
					m_myArray[i] = reserve[i];
				}
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

	void Resize(const size_t size)
	{
		// TODO: освободить ненужные объекты в пам€ти
		const T* reserve = m_myArray;
		const size_t prevSize = m_size;
		m_myArray = new T[size * 2];
		m_size = size;
		m_capacity = size * 2;

		for (size_t i = 0; i < prevSize; i++)
		{
			m_myArray[i] = reserve[i];
		}
		for (size_t i = prevSize; i < size; i++)
		{
			m_myArray[i] = T();
		}
		delete[] reserve;
	}

	void Clear()
	{
		delete[] m_myArray;
		m_myArray = nullptr;
		m_size = 0;
		m_capacity = 0;
		// TODO: m_capacity оставл€ть прежним
	}

	T* GetArray() const
	{
		return m_myArray;
	}

	// »тераторы

	CMyIterator begin()
	{
		return m_myArray;
	}
	CMyIterator end()
	{
		return m_myArray + m_size;
	}
	// TODO: добавить константные итераторы
	std::reverse_iterator<CMyIterator> rbegin()
	{
		return std::make_reverse_iterator(end());
	}
	std::reverse_iterator<CMyIterator> rend()
	{
		return std::make_reverse_iterator(begin());
	}

private:
	T* m_myArray = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;
};
