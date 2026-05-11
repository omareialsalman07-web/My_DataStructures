#pragma once
#include <iostream>
#include <stdexcept>

template<class T>
class LinkedList
{
    template<class T>
    class Node
    {
    public:
        Node(const T& value)
            : value(value), next(nullptr), prev(nullptr) {
        }

    private:
        T value;
        Node<T>* next;
        Node<T>* prev;

    public:
        T& GetValue() { return value; }
        const T& GetValue() const { return value; }

        Node<T>* GetNext() const { return next; }
        void SetNext(Node<T>* nextNode) { next = nextNode; }

        Node<T>* GetPrev() const { return prev; }
        void SetPrev(Node<T>* prevNode) { prev = prevNode; }
    };

private:
    Node<T>* head;
    Node<T>* tail;
    size_t _size;

public:
    LinkedList()
        : head(nullptr), tail(nullptr), _size(0) {
    }

    ~LinkedList()
    {
        Node<T>* temp = head;
        while (temp != nullptr)
        {
            Node<T>* next = temp->GetNext();
            delete temp;
            temp = next;
        }
        _size = 0;
    }

public:
    void InsertFirst(const T& value)
    {
        if (IsEmpty())
        {
            InsertTheFirstNode(value);
            return;
        }

        Node<T>* newNode = new Node<T>(value);

        newNode->SetNext(head);
        head->SetPrev(newNode);

        head = newNode;

        _size++;
    }

    void InsertLast(const T& value)
    {
        if (IsEmpty())
        {
            InsertTheFirstNode(value);
            return;
        }

        Node<T>* newNode = new Node<T>(value);

        tail->SetNext(newNode);
        newNode->SetPrev(tail);

        tail = newNode;

        _size++;
    }

    void InsertAtPosition(const T& value, size_t position)
    {
        if (position > _size)
            throw std::out_of_range("Position out of range");

        if (position == 0)
        {
            InsertFirst(value);
            return;
        }

        if (position == _size)
        {
            InsertLast(value);
            return;
        }

        Node<T>* temp = GetNode(position - 1);

        Node<T>* newNode = new Node<T>(value);
        Node<T>* nextNode = temp->GetNext();

        newNode->SetNext(nextNode);
        newNode->SetPrev(temp);

        temp->SetNext(newNode);
        nextNode->SetPrev(newNode);

        _size++;
    }

    void DeleteFirst()
    {
        if (IsEmpty())
            throw std::runtime_error("List is empty");

        if (_size == 1)
        {
            delete head;

            head = nullptr;
            tail = nullptr;

            _size--;

            return;
        }

        Node<T>* nodeToDelete = head;

        head = head->GetNext();
        head->SetPrev(nullptr);

        delete nodeToDelete;

        _size--;
    }

    void DeleteLast()
    {
        if (IsEmpty())
            throw std::runtime_error("List is empty");

        if (_size == 1)
        {
            delete head;

            head = nullptr;
            tail = nullptr;

            _size--;

            return;
        }

        Node<T>* nodeToDelete = tail;

        tail = tail->GetPrev();
        tail->SetNext(nullptr);

        delete nodeToDelete;

        _size--;
    }

    void DeleteAtPosition(size_t position)
    {
        if (IsEmpty())
            throw std::runtime_error("List is empty");

        if (position >= _size)
            throw std::out_of_range("Position out of range");

        if (position == 0)
        {
            DeleteFirst();
            return;
        }

        if (position == _size - 1)
        {
            DeleteLast();
            return;
        }

        Node<T>* temp = GetNode(position - 1);

        Node<T>* nodeToDelete = temp->GetNext();
        Node<T>* nextNode = nodeToDelete->GetNext();

        temp->SetNext(nextNode);
        nextNode->SetPrev(temp);

        delete nodeToDelete;

        _size--;
    }

    bool IsEmpty() const
    {
        return _size == 0;
    }

    size_t size() const
    {
        return _size;
    }

    T& operator[](size_t index)
    {
        return GetElement(index);
    }
    const T& operator[](size_t index) const
    {
        return GetElement(index);
    }

    T* begin() { return head; }
    const T* begin() const { return head; }

    T* end() { return tail; }
    const T* end() const { return tail; }

    void Reverse()
    {

    }

    void clean()
    {
        while (_size > 0)
        {
            DeleteFirst();
        }
    }

private:
    void InsertTheFirstNode(const T& value)
    {
        Node<T>* newNode = new Node<T>(value);

        head = newNode;
        tail = newNode;

        _size++;
    }

    T& GetElement(size_t index) const
    {
        Node<T>* node = GetNode(index);

        if (node == nullptr)
            throw std::out_of_range("Index out of range");

        return node->GetValue();
    }

protected:
    Node<T>* GetNode(size_t index) const
    {
        if (index >= _size || index < 0)
            return nullptr;

        Node<T>* temp = head;

        for (size_t i = 0; i < index; i++)
        {
            temp = temp->GetNext();
        }

        return temp;
    }
};