#pragma once
#include "LinkedList.h"

template<typename T>
class Queue
{
protected:
	LinkedList<T> m_Queue;
public:
	void push(const T& value)
	{
		m_Queue.InsertLast(value);
	}

	void pop()
	{
		m_Queue.DeleteFirst();
	}

	size_t size() { return m_Queue.size(); }

	T front() { return m_Queue[0]; }
	T back() { return m_Queue[size() - 1]; }

	void Print()
	{
		m_Queue.Print();
	}
};