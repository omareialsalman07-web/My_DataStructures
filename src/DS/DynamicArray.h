#pragma once

#include "Array.h"
#include <stdexcept>

template<class T>
class DynamicArray
{
private:
	T* _tempArray;
	T* m_Array;
	size_t _size;
public:
	DynamicArray(size_t size = 0)
	{
		if (size < 0)
			size = 0;

		_size = size;
		m_Array = new T[size]; // allocate object on the heap
	}

	~DynamicArray()
	{
		delete[] m_Array;
	}

	T& operator[](size_t index)
	{
		return GetElement(index);
	}
	const T& operator[](size_t index) const
	{
		GetElement(index);
	}

	T* Data() { return m_Array; }
	const T* Data() const { return m_Array; }

	T* begin() { return m_Array; }
	const T* begin() const { return m_Array; }

	T* end() { return m_Array + _size; }
	const T* end() const { return m_Array + _size; }

	size_t size()
	{
		return _size;
	}

	bool isEmpty()
	{
		return (_size <= 0);
	}

	void Resize(unsigned int newSize)
	{
		if (newSize < 0)
			newSize = 0;

		if (newSize == _size) // no need to resize
			return;

		_tempArray = new T[_size];

		int minSize = Min(_size, newSize);
		// Copy all the data form the original array
		for (int i = 0; i < minSize; i++)
		{
			_tempArray[i] = m_Array[i];
		}

		delete[] m_Array;
		m_Array = _tempArray;
		_size = newSize;
	}

	void InsertAtPosition(size_t index, const T& value)
	{
		if (index < 0 || index > _size)
			throw std::out_of_range("index is out of range!");

		++_size;
		_tempArray = new T[_size];

		//Copy befor index
		for (int i = 0; i < index; i++)
		{
			_tempArray[i] = m_Array[i];
		}
		_tempArray[index] = value;
		//Copy after index
		for (int i = index; i < _size - 1; i++)
		{
			_tempArray[i + 1] = m_Array[i];
		}

		delete[] m_Array;
		m_Array = _tempArray;
	}

	void InsertFirst(const T& value)
	{
		InsertAtPosition(0, value);
	}
	void InsertLast(const T& value)
	{
		InsertAtPosition(_size, value);
	}

	void DeleteLast()
	{
		DeleteAtPosition(_size - 1);
	}

	void DeleteFirst()
	{
		DeleteAtPosition(0);
	}

	void DeleteAtPosition(size_t index)
	{
		if (index < 0 || index >= _size)
			throw std::out_of_range("Invailed position");

		// delete in the middle
		_size--;
		_tempArray = new T[_size];

		// Copy before index
		for (int i = 0; i < index; i++)
		{
			_tempArray[i] = m_Array[i];
		}
		// Copy after index
		for (int i = index + 1; i < _size + 1; i++)
		{
			_tempArray[i - 1] = m_Array[i];
		}

		delete[] m_Array;
		m_Array = _tempArray;
	}

	void DeleteItem(const T& value)
	{
		int index = Find(value);

		if (index < 0)
		{
			return;
		}
		DeleteAtPosition();
	}

	size_t Find(const T& value)
	{
		for (int i = 0; i < size(); i++)
		{
			if (m_Array[i] == value)
				return i;
		}

		return -1;
	}



	void Reverse()
	{
		T* _arr = new T[size()];

		for (int i = 0; i < size(); i++)
		{
			_arr[i] = m_Array[size() - 1 - i];
		}
		
		delete m_Array;
		m_Array = _arr;
	}

	void clear()
	{
		_size = 0;
		delete[] m_Array;
		_tempArray = new T[0];
		m_Array = _tempArray;
	}

	DynamicArray<T> clone()
	{
		DynamicArray<T> clonedArray(_size);

		for (int i = 0; i < _size; i++)
		{
			clonedArray[i] = m_Array[i];
		}

		return clonedArray;
	}

private:
	size_t Min(size_t a, size_t b)
	{
		return (a > b) ? b : a;
	}

	T& GetElement(size_t index) const
	{
		if (index >= _size || index < 0)
			throw std::out_of_range("Position out of range");

		return *(m_Array + index);
	}
};