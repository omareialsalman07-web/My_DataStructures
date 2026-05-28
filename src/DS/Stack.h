#pragma once
#include "LinkedList.h"
#include "IStack.h"
#include <stdexcept>

template<class T>
class Stack : public IStack<T>
{
private:
    LinkedList<T> m_List;

public:
    void push(const T& item)
    {
        m_List.push_back(item);
    }

    void pop()
    {
        if (empty())
            throw std::runtime_error("Stack is empty");

        m_List.erase(m_List.size() - 1);
    }

    T& top()
    {
        if (empty())
            throw std::runtime_error("Stack is empty");

        return m_List.front();
    }

    const T& top() const
    {
        if (empty())
            throw std::runtime_error("Stack is empty");

        return m_List.front();
    }

    T& getElement(size_t index)
    {
        return m_List.getElement(index);
    }

    const T& getElement(size_t index) const
    {
        return m_List.getElement(index);
    }

    void clear()
    {
        m_List.clear();
    }

    size_t size() const { return m_List.size(); }
    bool empty() const { return m_List.size() == 0; }

};