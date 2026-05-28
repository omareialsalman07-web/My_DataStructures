#pragma once
#include <stdexcept>
#include <utility>

template<class T>
class LinkedList
{
private:
    struct Node
    {
        T value;
        Node* next;
        Node* prev;

        // Copy
        Node(const T& v)
            : value(v), next(nullptr), prev(nullptr)
        {}

        // Move
        Node(T&& v)
            : value(std::move(v)), next(nullptr), prev(nullptr)
        {}
    };

public:
    class Iterator
    {
    private:
        Node* current;

    public:
        Iterator(Node* node = nullptr)
            : current(node)
        {}

        T& operator*()
        {
            return current->value;
        }

        const T& operator*() const
        {
            return current->value;
        }

        Iterator& operator++()
        {
            if (current)
                current = current->next;

            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const
        {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const
        {
            return current != other.current;
        }
    };

private:
    Node* m_head;
    Node* m_tail;
    size_t m_size;

public:
    // ---------------- Constructors ----------------

    LinkedList()
        : m_head(nullptr), m_tail(nullptr), m_size(0)
    {}

    ~LinkedList()
    {
        clear();
    }

    // Copy constructor
    LinkedList(const LinkedList& other)
        : m_head(nullptr), m_tail(nullptr), m_size(0)
    {
        Node* current = other.m_head;

        while (current)
        {
            push_back(current->value);
            current = current->next;
        }
    }

    // Move constructor
    LinkedList(LinkedList&& other) noexcept
        : m_head(other.m_head),
        m_tail(other.m_tail),
        m_size(other.m_size)
    {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }

    // Copy assignment
    LinkedList& operator=(const LinkedList& other)
    {
        if (this == &other)
            return *this;

        LinkedList temp(other);
        swap(temp);

        return *this;
    }

    // Move assignment
    LinkedList& operator=(LinkedList&& other) noexcept
    {
        if (this == &other)
            return *this;

        clear();

        m_head = other.m_head;
        m_tail = other.m_tail;
        m_size = other.m_size;

        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;

        return *this;
    }

    // ---------------- Utility ----------------

    void swap(LinkedList& other) noexcept
    {
        std::swap(m_head, other.m_head);
        std::swap(m_tail, other.m_tail);
        std::swap(m_size, other.m_size);
    }

    bool empty() const
    {
        return m_size == 0;
    }

    size_t size() const
    {
        return m_size;
    }

    void clear()
    {
        while (m_head)
        {
            Node* temp = m_head;
            m_head = m_head->next;
            delete temp;
        }

        m_tail = nullptr;
        m_size = 0;
    }

    // ---------------- Front / Back ----------------

    T& front()
    {
        if (empty())
            throw std::runtime_error("List is empty");

        return m_head->value;
    }

    const T& front() const
    {
        if (empty())
            throw std::runtime_error("List is empty");

        return m_head->value;
    }

    T& back()
    {
        if (empty())
            throw std::runtime_error("List is empty");

        return m_tail->value;
    }

    const T& back() const
    {
        if (empty())
            throw std::runtime_error("List is empty");

        return m_tail->value;
    }

    // ---------------- Iterators ----------------

    Iterator begin()
    {
        return Iterator(m_head);
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

    Iterator begin() const
    {
        return Iterator(m_head);
    }

    Iterator end() const
    {
        return Iterator(nullptr);
    }

    // ---------------- Push Back ----------------

    void push_back(const T& value)
    {
        Node* node = new Node(value);

        if (empty())
        {
            m_head = m_tail = node;
        }
        else
        {
            m_tail->next = node;
            node->prev = m_tail;
            m_tail = node;
        }

        ++m_size;
    }

    void push_back(T&& value)
    {
        Node* node = new Node(std::move(value));

        if (empty())
        {
            m_head = m_tail = node;
        }
        else
        {
            m_tail->next = node;
            node->prev = m_tail;
            m_tail = node;
        }

        ++m_size;
    }

    // ---------------- Push Front ----------------

    void push_front(const T& value)
    {
        Node* node = new Node(value);

        if (empty())
        {
            m_head = m_tail = node;
        }
        else
        {
            node->next = m_head;
            m_head->prev = node;
            m_head = node;
        }

        ++m_size;
    }

    void push_front(T&& value)
    {
        Node* node = new Node(std::move(value));

        if (empty())
        {
            m_head = m_tail = node;
        }
        else
        {
            node->next = m_head;
            m_head->prev = node;
            m_head = node;
        }

        ++m_size;
    }

    // ---------------- Pop ----------------

    void pop_front()
    {
        if (empty())
            throw std::runtime_error("List is empty");

        Node* temp = m_head;

        m_head = m_head->next;

        if (m_head)
            m_head->prev = nullptr;
        else
            m_tail = nullptr;

        delete temp;
        --m_size;
    }

    void pop_back()
    {
        if (empty())
            throw std::runtime_error("List is empty");

        Node* temp = m_tail;

        m_tail = m_tail->prev;

        if (m_tail)
            m_tail->next = nullptr;
        else
            m_head = nullptr;

        delete temp;
        --m_size;
    }

    // ---------------- Access ----------------

    T& getElement(size_t index)
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");

        Node* curr;

        if (index < m_size / 2)
        {
            curr = m_head;

            for (size_t i = 0; i < index; ++i)
                curr = curr->next;
        }
        else
        {
            curr = m_tail;

            for (size_t i = m_size - 1; i > index; --i)
                curr = curr->prev;
        }

        return curr->value;
    }

    const T& getElement(size_t index) const
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");

        Node* curr;

        if (index < m_size / 2)
        {
            curr = m_head;

            for (size_t i = 0; i < index; ++i)
                curr = curr->next;
        }
        else
        {
            curr = m_tail;

            for (size_t i = m_size - 1; i > index; --i)
                curr = curr->prev;
        }

        return curr->value;
    }

    // ---------------- Reverse ----------------

    void reverse()
    {
        Node* current = m_head;
        Node* temp = nullptr;

        while (current)
        {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;

            current = current->prev;
        }

        temp = m_head;
        m_head = m_tail;
        m_tail = temp;
    }
};