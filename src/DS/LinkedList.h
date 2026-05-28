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

        Node(const T& v)
            : value(v), next(nullptr), prev(nullptr) {
        }
    };

    class Iterator
    {
    private:
        Node* current;

    public:
        Iterator(Node* node) : current(node) {}

        // READ access (const-safe)
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

        bool operator!=(const Iterator& other) const
        {
            return current != other.current;
        }
    };



    Node* m_head;
    Node* m_tail;
    size_t m_size;

public:
    LinkedList()
        : m_head(nullptr), m_tail(nullptr), m_size(0) {
    }

    ~LinkedList()
    {
        clear();
    }

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

    LinkedList& operator=(const LinkedList& other)
    {
        if (this == &other)
            return *this;

        clear();

        Node* current = other.m_head;
        while (current)
        {
            push_back(current->value);
            current = current->next;
        }

        return *this;
    }

    LinkedList(LinkedList&& other) noexcept
        : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size)
    {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }

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

    T& front()
    {
        if (empty()) throw std::runtime_error("List is empty");
        return m_head->value;
    }

    const T& front() const
    {
        if (empty()) throw std::runtime_error("List is empty");
        return m_head->value;
    }

    T& back()
    {
        if (empty()) throw std::runtime_error("List is empty");
        return m_tail->value;
    }

    const T& back() const
    {
        if (empty()) throw std::runtime_error("List is empty");
        return m_tail->value;
    }

    // ---------------- Iterators ----------------
    Iterator begin() const { return Iterator(m_head); }

    Iterator end() const { return Iterator(nullptr); }

    // ---------------- Insert ----------------
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

    void insert(size_t position, const T& value)
    {
        if (position > m_size)
            throw std::out_of_range("Position out of range");

        if (position == 0)
        {
            push_front(value);
            return;
        }

        if (position == m_size)
        {
            push_back(value);
            return;
        }

        Node* current = m_head;

        for (size_t i = 0; i < position; i++)
        {
            current = current->next;
        }

        Node* newNode = new Node(value);

        Node* prevNode = current->prev;

        // connect new node
        newNode->next = current;
        newNode->prev = prevNode;

        prevNode->next = newNode;
        current->prev = newNode;

        ++m_size;
    }

    // ---------------- Delete ----------------
    void pop_front()
    {
        if (empty()) throw std::runtime_error("List is empty");

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
        if (empty()) throw std::runtime_error("List is empty");

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

        if (index == 0)
        {
            pop_front();
            return;
        }

        if (index == m_size - 1)
        {
            pop_back();
            return;
        }

        Node* curr = m_head;
        for (size_t i = 0; i < index; i++)
            curr = curr->next;

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        delete curr;
        --m_size;
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

    // ---------------- get element (O(n)) ----------------
    T& getElement(size_t index)
    {
        Node* curr = m_head;
        for (size_t i = 0; i < index; i++)
            curr = curr->next;

        return curr->value;
    }

    const T& getElement(size_t index) const
    {
        Node* curr = m_head;
        for (size_t i = 0; i < index; i++)
            curr = curr->next;

        return curr->value;
    }

    size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }
};