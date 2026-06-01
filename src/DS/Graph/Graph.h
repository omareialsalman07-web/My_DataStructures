#pragma once

template <class T>
class Graph
{
public:
    enum class GraphDirectionType
    {
        eDirected,
        eUnDirected
    };

public:
    explicit Graph(GraphDirectionType graphDirectionType)
        : m_VertexCount(0),
        m_EdgeCount(0),
        m_GraphDirectionType(graphDirectionType)
    {}

    virtual ~Graph() = default;

public:
    virtual void AddVertex(const T& value) = 0;
    virtual void RemoveVertex(const T& value) = 0;

    virtual void AddEdge(const T& source, const T& destination) = 0;
    virtual void RemoveEdge(const T& source, const T& destination) = 0;

    virtual bool ContainsVertex(const T& value) const = 0;
    virtual bool ContainsEdge(const T& source, const T& destination) const = 0;

    virtual void clear() = 0;

public:
    size_t VertexCount() const
    {
        return m_VertexCount;
    }

    size_t EdgeCount() const
    {
        return m_EdgeCount;
    }

    bool isEmpty() const
    {
        return m_VertexCount == 0;
    }

protected:
    GraphDirectionType m_GraphDirectionType;
    size_t m_VertexCount;
    size_t m_EdgeCount;
};