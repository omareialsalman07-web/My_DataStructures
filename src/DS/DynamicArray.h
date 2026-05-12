#pragma once
#include <stdexcept>

template <typename T>
class DynamicArray
{
private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;

    void reallocate(size_t newCapacity)
    {
        T* newData = new T[newCapacity];

        for (size_t i = 0; i < m_size; i++)
        {
            newData[i] = m_data[i];
        }

        delete[] m_data;
        m_data = newData;
        m_capacity = newCapacity;
    }

    void swap(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

public:
    // ---------------- Constructor ----------------
    DynamicArray()
        : m_data(nullptr), m_size(0), m_capacity(0)
    {
    }

    explicit DynamicArray(size_t capacity)
        : m_data(nullptr), m_size(0), m_capacity(capacity)
    {
        if (m_capacity > 0)
            m_data = new T[m_capacity];
    }

    // ---------------- Destructor ----------------
    ~DynamicArray()
    {
        delete[] m_data;
    }

    // ---------------- Copy Constructor ----------------
    DynamicArray(const DynamicArray& other)
        : m_data(nullptr), m_size(other.m_size), m_capacity(other.m_capacity)
    {
        if (m_capacity > 0)
            m_data = new T[m_capacity];

        for (size_t i = 0; i < m_size; i++)
        {
            m_data[i] = other.m_data[i];
        }
    }

    // ---------------- Copy Assignment ----------------
    DynamicArray& operator=(const DynamicArray& other)
    {
        if (this == &other)
            return *this;

        T* newData = nullptr;

        if (other.m_capacity > 0)
        {
            newData = new T[other.m_capacity];

            for (size_t i = 0; i < other.m_size; i++)
            {
                newData[i] = other.m_data[i];
            }
        }

        delete[] m_data;

        m_data = newData;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        return *this;
    }

    // ---------------- Move Constructor ----------------
    DynamicArray(DynamicArray&& other) noexcept
        : m_data(other.m_data),
        m_size(other.m_size),
        m_capacity(other.m_capacity)
    {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    // ---------------- Move Assignment ----------------
    DynamicArray& operator=(DynamicArray&& other) noexcept
    {
        if (this == &other)
            return *this;

        delete[] m_data;

        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;

        return *this;
    }

    // ---------------- Element Access ----------------
    T& operator[](size_t index)
    {
        return m_data[index];
    }

    const T& operator[](size_t index) const
    {
        return m_data[index];
    }

    T& at(size_t index)
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");
        return m_data[index];
    }

    const T& at(size_t index) const
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");
        return m_data[index];
    }

    // ---------------- Capacity ----------------
    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; }
    bool empty() const { return m_size == 0; }

    // ---------------- Iterators ----------------
    T* begin() { return m_data; }
    const T* begin() const { return m_data; }

    T* end() { return m_data + m_size; }
    const T* end() const { return m_data + m_size; }

    T* data() { return m_data; }
    const T* data() const { return m_data; }

    // ---------------- Modifiers ----------------
    void push_back(const T& value)
    {
        if (m_size >= m_capacity)
        {
            size_t newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
            reallocate(newCapacity);
        }

        m_data[m_size++] = value;
    }

    void pop_back()
    {
        if (m_size == 0)
            throw std::out_of_range("Array is empty");

        --m_size;
    }

    void insert(size_t index, const T& value)
    {
        if (index > m_size)
            throw std::out_of_range("Index out of range");

        if (m_size >= m_capacity)
        {
            size_t newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
            reallocate(newCapacity);
        }

        for (size_t i = m_size; i > index; --i)
        {
            m_data[i] = m_data[i - 1];
        }

        m_data[index] = value;
        ++m_size;
    }

    void erase(size_t index)
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");

        for (size_t i = index; i < m_size - 1; ++i)
        {
            m_data[i] = m_data[i + 1];
        }

        --m_size;
    }

    void clear()
    {
        m_size = 0;
        m_capacity = 0;
        delete[] m_data;
        m_data = nullptr;
    }

    void reverse()
    {
        for (size_t i = 0; i < m_size / 2; i++)
        {
            swap(m_data[i], m_data[m_size - 1 - i]);
        }
    }
};