#pragma once
#include "Graph.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "Queue.h"
#include <stdexcept>

template <class T>
class AdjacencyListGraph : public Graph<T>
{
public:
    AdjacencyListGraph(Graph<T>::GraphDirectionType type)
        : Graph<T>(type) {}

    AdjacencyListGraph(const DynamicArray<T>& vertices,
        Graph<T>::GraphDirectionType type)
        : Graph<T>(type), m_Vertices(vertices)
    {
        m_Graph = DynamicArray<LinkedList<size_t>>(m_Vertices.size());
    }

    // ---------------- Add Vertex ----------------
    void AddVertex(const T& value) override
    {
        if (ContainsVertex(value))
            throw std::runtime_error("Vertex already exists");

        m_Vertices.push_back(value);
        m_Graph.push_back(LinkedList<size_t>());

        this->m_VertexCount++;
    }

    // ---------------- Add Edge ----------------
    void AddEdge(const T& source, const T& destination) override
    {
        if (!ContainsVertex(source) || !ContainsVertex(destination))
            throw std::runtime_error("Invalid vertices");

        size_t src = m_Vertices.find(source);
        size_t dst = m_Vertices.find(destination);

        if (m_Graph[src].contains(dst))
            throw std::runtime_error("Edge already exists");

        m_Graph[src].push_back(dst);
        this->m_EdgeCount++;

        if (this->m_GraphDirectionType == Graph<T>::GraphDirectionType::eUnDirected)
            m_Graph[dst].push_back(src);
    }

    // ---------------- Remove Edge ----------------
    void RemoveEdge(const T& source, const T& destination) override
    {
        if (!ContainsVertex(source) || !ContainsVertex(destination))
            throw std::runtime_error("Invalid vertices");

        size_t src = m_Vertices.find(source);
        size_t dst = m_Vertices.find(destination);

        auto it = m_Graph[src].find(dst);

        if (it == m_Graph[src].end())
            throw std::runtime_error("Edge does not exist");

        m_Graph[src].erase(it);
        this->m_EdgeCount--;

        if (this->m_GraphDirectionType == Graph<T>::GraphDirectionType::eUnDirected)
        {
            auto it2 = m_Graph[dst].find(src);
            if (it2 != m_Graph[dst].end())
                m_Graph[dst].erase(it2);
        }
    }

    // ---------------- Remove Vertex ----------------
    void RemoveVertex(const T& value) override
    {
        if (!ContainsVertex(value))
            throw std::runtime_error("Vertex does not exist");

        size_t idx = m_Vertices.find(value);

        // remove all incoming edges
        for (size_t i = 0; i < m_Graph.size(); i++)
        {
            auto it = m_Graph[i].find(idx);
            if (it != m_Graph[i].end())
            {
                m_Graph[i].erase(it);
                this->m_EdgeCount--;
            }
        }

        // remove adjacency list
        m_Graph.erase(idx);
        m_Vertices.erase(idx);

        this->m_VertexCount--;

        // fix shifted indices
        for (size_t i = 0; i < m_Graph.size(); i++)
        {
            for (auto it = m_Graph[i].begin(); it != m_Graph[i].end(); ++it)
            {
                if (*it > idx)
                    (*it)--;
            }
        }
    }

    // ---------------- Queries ----------------
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

        return m_Graph[src].contains(dst);
    }

    // ---------------- Get Neighbors ----------------
    DynamicArray<T> GetNeighbors(const T& vertex)
    {
        if (!ContainsVertex(vertex))
            throw std::runtime_error("Vertex not found");

        size_t idx = m_Vertices.find(vertex);
        DynamicArray<T> result;

        for (auto it = m_Graph[idx].begin(); it != m_Graph[idx].end(); ++it)
            result.push_back(m_Vertices[*it]);

        return result;
    }

    // ---------------- Clear ----------------
    void clear() override
    {
        m_Graph.clear();
        m_Vertices.clear();

        this->m_VertexCount = 0;
        this->m_EdgeCount = 0;
    }

    // ---------------- BFS Iterator ----------------
    class BFSIterator
    {
    public:
        BFSIterator() = default;

        BFSIterator(const AdjacencyListGraph<T>* graph, size_t start, bool end = false)
            : m_Graph(graph), m_End(end)
        {
            if (end) return;

            size_t n = graph->m_Vertices.size();
            m_visited = DynamicArray<bool>(n);

            for (size_t i = 0; i < n; i++)
                m_visited.push_back(false);

            m_queue.push(start);
            m_visited[start] = true;
            m_current = start;
        }

        T operator*() const
        {
            return m_Graph->m_Vertices[m_current];
        }

        BFSIterator& operator++()
        {
            if (m_queue.empty())
            {
                m_End = true;
                return *this;
            }

            size_t node = m_queue.front();
            m_queue.pop();

            for (auto it = m_Graph->m_Graph[node].begin();
                it != m_Graph->m_Graph[node].end(); ++it)
            {
                size_t neigh = *it;

                if (!m_visited[neigh])
                {
                    m_visited[neigh] = true;
                    m_queue.push(neigh);
                }
            }

            if (!m_queue.empty())
                m_current = m_queue.front();
            else
                m_End = true;

            return *this;
        }

        bool operator!=(const BFSIterator& other) const
        {
            return m_End != other.m_End;
        }

    private:
        const AdjacencyListGraph<T>* m_Graph = nullptr;
        Queue<size_t> m_queue;
        DynamicArray<bool> m_visited;
        size_t m_current = 0;
        bool m_End = false;
    };

    BFSIterator beginBFS(const T& start)
    {
        return BFSIterator(this, m_Vertices.find(start));
    }

    BFSIterator endBFS()
    {
        return BFSIterator(this, 0, true);
    }

private:
    DynamicArray<T> m_Vertices;
    DynamicArray<LinkedList<size_t>> m_Graph;
};