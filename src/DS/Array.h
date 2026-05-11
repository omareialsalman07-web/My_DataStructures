#pragma once
#include <iostream>

template <typename T, size_t _size>
class Array 
{
public:

	T& operator[](size_t index) 
	{ 
		return *(m_data + index); 
	}
	const T& operator[](size_t index) const 
	{
		return *(m_data + index); 
	}

	constexpr size_t size() const { return _size; }

	T* Data() { return m_data; }
	const T* Data() const { return m_data; }

	T* begin() { return m_data; }
	const T* begin() const { return m_data; }

	T* end() { return m_data + _size; }
	const T* end() const { return m_data + _size; }

	Array<T, _size> clone()
	{
		Array<T, _size> clonedArray;

		for (int i = 0; i < _size; i++)
		{
			clonedArray[i] = m_data[i];
		}

		return clonedArray;
	}

private:
	T m_data[_size];
};