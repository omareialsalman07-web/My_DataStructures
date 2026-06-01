#pragma once
#include <iostream>
#include "Queue.h"
#include <stdexcept>

enum class SearchType { PreOrder, InOrder, PostOrder };

template <class T>
class BinarySearchTree
{
private:
    struct Node
    {
        T value;
        Node* left;
        Node* right;

        Node(const T& v)
            : value(v), left(nullptr), right(nullptr) {}
    };

    Node* m_root;
    size_t m_size;

private:
    Node* insert(Node* node, const T& value)
    {
        if (!node)
            return new Node(value);

        if (value < node->value)
            node->left = insert(node->left, value);
        else
            node->right = insert(node->right, value);

        return node;
    }

    Node* search(Node* node, const T& value) const
    {
        if (!node) return nullptr;

        if (node->value == value) return node;

        if (value < node->value)
            return search(node->left, value);

        return search(node->right, value);
    }

    Node* findMin(Node* node) const
    {
        if (!node) return nullptr;

        while (node->left)
            node = node->left;

        return node;
    }

    Node* findMax(Node* node) const
    {
        if (!node) return nullptr;

        while (node->right)
            node = node->right;

        return node;
    }

    Node* remove(Node* node, const T& key, bool& removed)
    {
        if (!node) return nullptr;

        if (key < node->value)
            node->left = remove(node->left, key, removed);
        else if (key > node->value)
            node->right = remove(node->right, key, removed);
        else
        {
            removed = true;

            if (!node->left)
            {
                Node* r = node->right;
                delete node;
                return r;
            }
            else if (!node->right)
            {
                Node* l = node->left;
                delete node;
                return l;
            }

            Node* pred = findMax(node->left);
            node->value = pred->value;

            bool dummy = false;
            node->left = remove(node->left, pred->value, dummy);
        }

        return node;
    }

    void inorder(Node* node) const
    {
        if (!node) return;
        inorder(node->left);
        std::cout << node->value << " ";
        inorder(node->right);
    }

    void preorder(Node* node) const
    {
        if (!node) return;
        std::cout << node->value << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) const
    {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        std::cout << node->value << " ";
    }

    void clear(Node* node)
    {
        if (!node) return;

        clear(node->left);
        clear(node->right);
        delete node;
    }

    Node* clone(Node* node)
    {
        if (!node) return nullptr;

        Node* newNode = new Node(node->value);
        newNode->left = clone(node->left);
        newNode->right = clone(node->right);

        return newNode;
    }

public:
    class Iterator
    {
    private:
        Queue<Node*> q;
        Node* current;

        void push(Node* node)
        {
            if (node) q.push(node);
        }

    public:
        Iterator(Node* root) : current(nullptr)
        {
            push(root);
            ++(*this);
        }

        const T& operator*() const
        {
            return current->value;
        }

        Iterator& operator++()
        {
            if (q.empty())
            {
                current = nullptr;
                return *this;
            }

            current = q.front();
            q.pop();

            push(current->left);
            push(current->right);

            return *this;
        }

        bool operator!=(const Iterator& other) const
        {
            return current != other.current;
        }
    };

public:
    BinarySearchTree()
        : m_root(nullptr), m_size(0) {}

    // Copy constructor
    BinarySearchTree(const BinarySearchTree& other)
    {
        m_root = clone(other.m_root);
        m_size = other.m_size;
    }

    // Copy assignment
    BinarySearchTree& operator=(const BinarySearchTree& other)
    {
        if (this == &other)
            return *this;

        clear(m_root);

        m_root = clone(other.m_root);
        m_size = other.m_size;

        return *this;
    }

    ~BinarySearchTree()
    {
        clear(m_root);
    }

    void insert(const T& value)
    {
        m_root = insert(m_root, value);
        ++m_size;
    }

    bool contains(const T& value) const
    {
        return search(m_root, value) != nullptr;
    }

    const T& min() const
    {
        Node* n = findMin(m_root);
        if (!n) throw std::runtime_error("Tree is empty");
        return n->value;
    }

    const T& max() const
    {
        Node* n = findMax(m_root);
        if (!n) throw std::runtime_error("Tree is empty");
        return n->value;
    }

    bool remove(const T& value)
    {
        bool removed = false;
        m_root = remove(m_root, value, removed);

        if (removed)
            --m_size;

        return removed;
    }

    void clear()
    {
        clear(m_root);
        m_root = nullptr;
        m_size = 0;
    }

    bool empty() const { return m_size == 0; }
    size_t size() const { return m_size; }

    Iterator begin() const { return Iterator(m_root); }
    Iterator end() const { return Iterator(nullptr); }

    void dfs(SearchType type) const
    {
        switch (type)
        {
        case SearchType::PreOrder: preorder(m_root); break;
        case SearchType::InOrder: inorder(m_root); break;
        case SearchType::PostOrder: postorder(m_root); break;
        }

        std::cout << "\n";
    }

    void bfs() const
    {
        if (!m_root) return;

        Queue<Node*> queue;
        queue.push(m_root);

        while (!queue.empty())
        {
            Node* current = queue.front();
            queue.pop();

            std::cout << current->value << " ";

            if (current->left)
                queue.push(current->left);

            if (current->right)
                queue.push(current->right);
        }

        std::cout << "\n";
    }
};