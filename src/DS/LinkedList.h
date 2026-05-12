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

    Node* head;
    Node* tail;
    size_t m_size;

public:
    LinkedList()
        : head(nullptr), tail(nullptr), m_size(0) {
    }

    ~LinkedList()
    {
        clear();
    }

    LinkedList(const LinkedList& other)
        : head(nullptr), tail(nullptr), m_size(0)
    {
        Node* current = other.head;
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

        Node* current = other.head;
        while (current)
        {
            push_back(current->value);
            current = current->next;
        }

        return *this;
    }

    LinkedList(LinkedList&& other) noexcept
        : head(other.head), tail(other.tail), m_size(other.m_size)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.m_size = 0;
    }

    LinkedList& operator=(LinkedList&& other) noexcept
    {
        if (this == &other)
            return *this;

        clear();

        head = other.head;
        tail = other.tail;
        m_size = other.m_size;

        other.head = nullptr;
        other.tail = nullptr;
        other.m_size = 0;

        return *this;
    }

    T& front()
    {
        if (empty()) throw std::runtime_error("List is empty");
        return head->value;
    }

    const T& front() const
    {
        if (empty()) throw std::runtime_error("List is empty");
        return head->value;
    }

    T& back()
    {
        if (empty()) throw std::runtime_error("List is empty");
        return tail->value;
    }

    const T& back() const
    {
        if (empty()) throw std::runtime_error("List is empty");
        return tail->value;
    }

    // ---------------- Iterators ----------------
    Node* begin() { return head; }
    const Node* begin() const { return head; }

    Node* end() { return nullptr; }             // tail->next = null
    const Node* end() const { return nullptr; } // tail->next = null

    // ---------------- Insert ----------------
    void push_front(const T& value)
    {
        Node* node = new Node(value);

        if (empty())
        {
            head = tail = node;
        }
        else
        {
            node->next = head;
            head->prev = node;
            head = node;
        }

        ++m_size;
    }

    void push_back(const T& value)
    {
        Node* node = new Node(value);

        if (empty())
        {
            head = tail = node;
        }
        else
        {
            tail->next = node;
            node->prev = tail;
            tail = node;
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

        Node* current = head;

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

        Node* temp = head;
        head = head->next;

        if (head)
            head->prev = nullptr;
        else
            tail = nullptr;

        delete temp;
        --m_size;
    }

    void pop_back()
    {
        if (empty()) throw std::runtime_error("List is empty");

        Node* temp = tail;
        tail = tail->prev;

        if (tail)
            tail->next = nullptr;
        else
            head = nullptr;

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

        Node* curr = head;
        for (size_t i = 0; i < index; i++)
            curr = curr->next;

        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        delete curr;
        --m_size;
    }

    void clear()
    {
        while (head)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }

        tail = nullptr;
        m_size = 0;
    }

    void reverse()
    {
        Node* current = head;
        Node* temp = nullptr;

        while (current)
        {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;

            current = current->prev;
        }

        temp = head;
        head = tail;
        tail = temp;
    }

    // ---------------- get element (O(n)) ----------------
    T& getElement(size_t index)
    {
        Node* curr = head;
        for (size_t i = 0; i < index; i++)
            curr = curr->next;

        return curr->value;
    }

    const T& getElement(size_t index) const
    {
        Node* curr = head;
        for (size_t i = 0; i < index; i++)
            curr = curr->next;

        return curr->value;
    }

    size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }
};