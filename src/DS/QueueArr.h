#pragma once
#include "IQueue.h"
#include "DynamicArray.h"

template<class T>
class QueueArr : public IQueue
{
protected:
    DynamicArray<T> m_DArray;

public:
    void push(const T& value)
    {
        m_DArray.push_back(value);
    }

    void pop()
    {
        if (empty())
            throw std::out_of_range("Queue is empty");

        m_DArray.erase(0);
    }

    T& front()
    {
        return m_DArray[0];
    }

    const T& front() const
    {
        return m_DArray[0];
    }

    T& back()
    {
        return m_DArray[m_DArray.size() - 1];
    }

    const T& back() const
    {
        return m_DArray[m_DArray.size() - 1];
    }

    T& operator[](size_t index)
    {
        return m_DArray[index];
    }

    const T& operator[](size_t index) const
    {
        return m_DArray[index];
    }

    void clear()
    {
        m_DArray.clear();
    }

    void reverse()
    {
        m_DArray.reverse();
    }

    size_t size() const { return m_DArray.size(); }
    bool empty() const { return m_DArray.empty(); }
};