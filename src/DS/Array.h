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

private:
	T m_data[_size];
};