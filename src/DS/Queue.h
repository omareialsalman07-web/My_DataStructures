#pragma once
#include "LinkedList.h"

template<typename T>
class Queue
{
protected:
	LinkedList<T> m_Queue;
public:
	size_t size() const { return m_Queue.size(); }
	
	void push(const T& value)
	{
		m_Queue.InsertLast(value);
	}

	void pop()
	{
		m_Queue.DeleteFirst();
	}

	void InsertAtFront(const T& value)
	{
		m_Queue.InsertFirst(value);
	}

	void InsertAtBack(const T& value)
	{
		m_Queue.InsertLast(value);
	}

	void InsertAtPosition(const T& value, size_t position)
	{
		m_Queue.InsertAtPosition(value, position);
	}


	T front() const { return m_Queue[0]; }
	T back() const { return m_Queue[size() - 1]; }

	T& operator[](size_t index)
	{
		return m_Queue[index];
	}
	const T& operator[](size_t index) const
	{
		return m_Queue[index];
	}

	void Reverse()
	{
		m_Queue.Reverse();
	}
	
	void clear()
	{
		m_Queue.clean();
	}

	void Print()
	{
		m_Queue.Print();
	}
};