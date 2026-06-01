#pragma once
#include <stdexcept>

template<class T>
class LinkedList
{
private:
    struct Node
    {
        T value;
        Node* next;
        Node* prev;

        // Copy only
        Node(const T& v)
            : value(v), next(nullptr), prev(nullptr)
        {}
    };

public:
    class Iterator
    {
    private:
        Node* current;

        friend class LinkedList<T>;

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

    // Copy assignment
    LinkedList& operator=(const LinkedList& other)
    {
        if (this == &other)
            return *this;

        clear();  // remove old data

        Node* current = other.m_head;

        while (current)
        {
            push_back(current->value);
            current = current->next;
        }

        return *this;
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

    // Front / Back
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

    // Iterators
    Iterator begin() { return Iterator(m_head); }
    Iterator end() { return Iterator(nullptr); }
    Iterator begin() const { return Iterator(m_head); }
    Iterator end() const { return Iterator(nullptr); }

    // Push Back
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

    // Push Front
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

    // Pop Front
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

    void insert(size_t index, const T& value)
    {
        if (index > m_size)
            throw std::out_of_range("Index out of range");

        // Insert at front
        if (index == 0)
        {
            push_front(value);
            return;
        }

        // Insert at back (after last element)
        if (index == m_size)
        {
            push_back(value);
            return;
        }

        // Middle insertion
        Node* node = new Node(value);
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
            for (size_t i = m_size - 1; i >= index; --i)
                curr = curr->prev;
        }

        Node* prevNode = curr->prev;

        node->next = curr;
        node->prev = prevNode;

        prevNode->next = node;
        curr->prev = node;

        ++m_size;
    }

    // Pop Back
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

    void erase(size_t index)
    {
        if (index >= m_size)
            throw std::out_of_range("Index out of range");

        // Case 1: first element
        if (index == 0)
        {
            pop_front();
            return;
        }

        // Case 2: last element
        if (index == m_size - 1)
        {
            pop_back();
            return;
        }

        // Case 3: middle element
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

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        delete curr;
        --m_size;
    }

    void erase(Iterator it)
    {
        if (it == end())
            return;

        Node* node = it.current;

        if (node == m_head) { pop_front(); return; }
        if (node == m_tail) { pop_back(); return; }

        node->prev->next = node->next;
        node->next->prev = node->prev;

        delete node;
        --m_size;
    }

    // Access
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

    Iterator find(const T& value)
    {
        Node* curr = m_head;
        while (curr)
        {
            if (curr->value == value)
                return Iterator(curr);
            curr = curr->next;
        }
        return end();
    }

    bool contains(const T& value) const
    {
        Node* curr = m_head;
        while (curr)
        {
            if (curr->value == value)
                return true;
            curr = curr->next;
        }
        return false;
    }

    // Reverse
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