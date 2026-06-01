#pragma once
#include "Graph.h"
#include "DynamicArray.h"
#include "Queue.h"
#include <stdexcept>

template <class T>
class AdjacencyMatrixGraph : public Graph<T>
{
public:
    class BFSIterator
    {
    public:
        BFSIterator() = default;

        BFSIterator(const AdjacencyMatrixGraph<T>* graph, size_t start, bool isEnd = false)
            : m_Graph(graph), m_End(isEnd)
        {
            if (isEnd)
                return;

            size_t n = graph->m_Vertices.size();
            m_Visited = DynamicArray<bool>(n);

            for (size_t i = 0; i < n; i++)
                m_Visited.push_back(false);

            m_Queue.push(start);
            m_Visited[start] = true;
            m_Current = start;
        }

        const T& operator*() const
        {
            return m_Graph->m_Vertices[m_Current];
        }

        BFSIterator& operator++()
        {
            if (m_Queue.empty())
            {
                m_End = true;
                return *this;
            }

            size_t node = m_Queue.front();
            m_Queue.pop();

            for (size_t i = 0; i < m_Graph->m_Vertices.size(); i++)
            {
                if (m_Graph->m_Graph[node][i] && !m_Visited[i])
                {
                    m_Visited[i] = true;
                    m_Queue.push(i);
                }
            }

            if (!m_Queue.empty())
                m_Current = m_Queue.front();
            else
                m_End = true;

            return *this;
        }

        bool operator!=(const BFSIterator& other) const
        {
            return m_End != other.m_End;
        }

    private:
        const AdjacencyMatrixGraph<T>* m_Graph = nullptr;
        Queue<size_t> m_Queue;
        DynamicArray<bool> m_Visited;
        size_t m_Current = 0;
        bool m_End = false;
    };

public:
    AdjacencyMatrixGraph(Graph<T>::GraphDirectionType type)
        : Graph<T>(type) {}

    AdjacencyMatrixGraph(const DynamicArray<T>& vertices,
        Graph<T>::GraphDirectionType type)
        : Graph<T>(type), m_Vertices(vertices)
    {
        size_t n = m_Vertices.size();

        m_Graph = DynamicArray<DynamicArray<bool>>(n);

        for (size_t i = 0; i < n; i++)
        {
            DynamicArray<bool> row(n);

            for (size_t j = 0; j < n; j++)
                row.push_back(false);

            m_Graph.push_back(row);
        }

        this->m_VertexCount = n;
        this->m_EdgeCount = 0;
    }

    BFSIterator beginBFS(const T& start)
    {
        size_t idx = m_Vertices.find(start);
        return BFSIterator(this, idx);
    }

    BFSIterator endBFS()
    {
        return BFSIterator(this, 0, true);
    }

public:
    void AddVertex(const T& value) override
    {
        if (ContainsVertex(value))
            throw std::runtime_error("Vertex already exists");

        m_Vertices.push_back(value);

        for (size_t i = 0; i < m_Graph.size(); i++)
            m_Graph.at(i).push_back(false);

        DynamicArray<bool> newRow(m_Vertices.size());

        for (size_t i = 0; i < m_Vertices.size(); i++)
            newRow.push_back(false);

        m_Graph.push_back(newRow);

        this->m_VertexCount++;
    }

    void AddEdge(const T& source, const T& destination) override
    {
        if (!ContainsVertex(source) || !ContainsVertex(destination))
            throw std::runtime_error("Invalid vertices");

        size_t src = m_Vertices.find(source);
        size_t dst = m_Vertices.find(destination);

        if (m_Graph[src][dst])
            throw std::runtime_error("Edge already exists");

        m_Graph[src][dst] = true;
        this->m_EdgeCount++;

        if (this->m_GraphDirectionType == Graph<T>::GraphDirectionType::eUnDirected)
            m_Graph[dst][src] = true;
    }

    void RemoveVertex(const T& value) override
    {
        if (!ContainsVertex(value))
            throw std::runtime_error("Vertex does not exist");

        size_t idx = m_Vertices.find(value);

        for (size_t i = 0; i < m_Graph.size(); i++)
        {
            if (m_Graph[i][idx])
                this->m_EdgeCount--;

            m_Graph[i].erase(idx);
        }

        m_Graph.erase(idx);
        m_Vertices.erase(idx);

        this->m_VertexCount--;

        if (this->m_EdgeCount > this->m_EdgeCount) // for safty
            this->m_EdgeCount = 0;
    }

    void RemoveEdge(const T& source, const T& destination) override
    {
        if (!ContainsVertex(source) || !ContainsVertex(destination))
            throw std::runtime_error("Invalid vertices");

        size_t src = m_Vertices.find(source);
        size_t dst = m_Vertices.find(destination);

        if (!m_Graph[src][dst])
            throw std::runtime_error("Edge does not exist");

        m_Graph[src][dst] = false;
        this->m_EdgeCount--;

        if (this->m_GraphDirectionType == Graph<T>::GraphDirectionType::eUnDirected)
            m_Graph[dst][src] = false;
    }

    DynamicArray<T> GetNeighbors(const T& vertex)
    {
        if (!ContainsVertex(vertex))
            throw std::runtime_error("Vertex does not exist");

        DynamicArray<T> neighbors;

        size_t idx = m_Vertices.find(vertex);

        for (size_t i = 0; i < m_Graph.size(); i++)
        {
            if (m_Graph[idx][i])
                neighbors.push_back(m_Vertices[i]);
        }

        return neighbors;
    }

    bool ContainsVertex(const T& value) const override
    {
        return m_Vertices.contains(value);
    }

    bool ContainsEdge(const T& source, const T& destination) const override
    {
        if (!ContainsVertex(source) || !ContainsVertex(destination))
            return false;

        size_t src = m_Vertices.find(source);
        size_t dst = m_Vertices.find(destination);

        return m_Graph[src][dst];
    }

    void clear() override
    {
        m_Graph.clear();
        m_Vertices.clear();
        this->m_EdgeCount = 0;
        this->m_VertexCount = 0;
    }

private:
    DynamicArray<T> m_Vertices;
    DynamicArray<DynamicArray<bool>> m_Graph;
};