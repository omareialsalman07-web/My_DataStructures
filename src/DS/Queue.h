#pragma once
#include "LinkedList.h"

template<class T>
class Queue
{
protected:
	LinkedList<T> m_List;
public:
	size_t size() const { return m_List.size(); }
	
	virtual void push(const T& value)
	{
		m_List.InsertLast(value);
	}

	virtual void pop()
	{
		m_List.DeleteFirst();
	}

	void InsertAtFront(const T& value)
	{
		m_List.InsertFirst(value);
	}

	void InsertAtBack(const T& value)
	{
		m_List.InsertLast(value);
	}

	void InsertAtPosition(const T& value, size_t position)
	{
		m_List.InsertAtPosition(value, position);
	}


	T front() const { return m_List[0]; }
	T back() const { return m_List[size() - 1]; }

	T& operator[](size_t index)
	{
		return m_List[index];
	}
	const T& operator[](size_t index) const
	{
		return m_List[index];
	}

	void Reverse()
	{
		m_List.Reverse();
	}
	
	void clear()
	{
		m_List.clean();
	}
};