#pragma once

#include <cstddef>
#include <list>
#include <vector>

class Graph
{
public:
    enum class ConnectionType
    {
        Undirected,
        Directed,
        Last
    };

    Graph(size_t vertices, ConnectionType type);

    virtual void addEdge(size_t v, size_t w) = 0;
    virtual size_t numberOfNodesOnLevel(size_t level, size_t startingVertex) const = 0;
    virtual bool isStronglyConnected(size_t startingVertex) const = 0;

protected:
    size_t vertices_;
    ConnectionType type_;
};

class AdjacencyList : public Graph
{
public:
    AdjacencyList(size_t vertices, ConnectionType type = ConnectionType::Undirected);

    void addEdge(size_t v, size_t w) override final;
    size_t numberOfNodesOnLevel(size_t level, size_t startingVertex = 0) const override final;
    bool isStronglyConnected(size_t startingVertex = 0) const override final;

private:
    std::vector<bool> visitedBFS(const std::vector<std::list<size_t>>& list, size_t startingVertex) const;
    bool allVisited(const std::vector<bool>& visited) const;
    std::vector<std::list<size_t>> reversedList() const;

    std::vector<std::list<size_t>> list_;
};
