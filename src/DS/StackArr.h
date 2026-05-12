#pragma once
#include "IStack.h"
#include "DynamicArray.h"

template<class T>
class StackArr : public IStack<T>
{
private:
    DynamicArray<T> m_DArray;

public:
    void push(const T& item)
    {
        m_DArray.push_back(item);
    }

    void pop()
    {
        if (empty())
            throw std::out_of_range("Stack is empty");

        m_DArray.erase(m_DArray.size() - 1);
    }

    T& top()
    {
        if (empty())
            throw std::out_of_range("Stack is empty");

        return m_DArray[m_DArray.size() - 1];
    }

    const T& top() const
    {
        if (empty())
            throw std::out_of_range("Stack is empty");

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

    size_t size() const { return m_DArray.size(); }
    bool empty() const { return m_DArray.size() == 0; }
};