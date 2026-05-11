#pragma once
#include "DynamicArray.h"

template<class T>
class QueueArr
{
protected:
	DynamicArray<T> m_DArray;
public:
	size_t size() const { return m_DArray.size(); }

	virtual void push(const T& value)
	{
		m_DArray.InsertLast(value);
	}

	virtual void pop()
	{
		m_DArray.DeleteFirst();
	}

	void InsertAtFront(const T& value)
	{
		m_DArray.InsertFirst(value);
	}

	void InsertAtBack(const T& value)
	{
		m_DArray.InsertLast(value);
	}

	void InsertAtPosition(const T& value, size_t position)
	{
		m_DArray.InsertAtPosition(value, position);
	}


	T front() const { return m_DArray[0]; }
	T back() const { return m_DArray[size() - 1]; }

	T& operator[](size_t index)
	{
		return m_DArray[index];
	}
	const T& operator[](size_t index) const
	{
		return m_DArray[index];
	}

	void Reverse()
	{
		m_DArray.Reverse();
	}

	void clear()
	{
		m_DArray.clear();
	}
};