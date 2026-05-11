#pragma once
#include "Queue.h"

template<class T>
class Stack : public Queue<T>
{
public:
	void push(const T& item) override
	{
		Queue <T>::m_List.InsertFirst(item);
	}

	T top()
	{
		return Queue <T>::front();
	}

	T bottom()
	{
		return Queue <T>::back();
	}
};