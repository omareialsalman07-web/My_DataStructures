#pragma once
#include "IQueue.h"
#include "LinkedList.h"
#include <stdexcept>

template<class T>
class Queue : public IQueue<T>
{
protected:
    LinkedList<T> m_List;

public:
    void push(const T& value)
    {
        m_List.push_back(value);
    }

    void pop()
    {
        if (empty())
            throw std::runtime_error("Queue is empty");

        m_List.pop_front();
    }

    T& front()
    {
        if (empty())
            throw std::runtime_error("Queue is empty");

        return m_List.front();
    }

    const T& front() const
    {
        if (empty())
            throw std::runtime_error("Queue is empty");

        return m_List.front();
    }

    T& back()
    {
        if (empty())
            throw std::runtime_error("Queue is empty");

        return m_List.back();
    }

    const T& back() const
    {
        if (empty())
            throw std::runtime_error("Queue is empty");

        return m_List.back();
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
    bool empty() const { return m_List.empty(); }
};