#pragma once
#include "QueueArr.h"

template<class T>
class StackArr : public QueueArr<T>
{
public:
	void push(const T& item) override
	{
		QueueArr <T>::m_DArray.InsertFirst(item);
	}

	T top()
	{
		return QueueArr <T>::front();
	}

	T bottom()
	{
		return QueueArr <T>::back();
	}
};