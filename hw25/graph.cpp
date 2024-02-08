#include "graph.hpp"

#include <cassert>
#include <limits>
#include <queue>

Graph::Graph(size_t vertices, ConnectionType type)
    : vertices_(vertices), type_(type)
{
}

AdjacencyList::AdjacencyList(size_t vertices, ConnectionType type)
    : Graph(vertices, type)
{
    list_.resize(vertices_);
}

void AdjacencyList::addEdge(size_t v, size_t w)
{
    list_[v].push_back(w);
    if (type_ == ConnectionType::Undirected)
    {
        list_[w].push_back(v);
    }
}

/* Level count starts from 0 */
size_t AdjacencyList::numberOfNodesOnLevel(size_t level, size_t startingVertex) const
{
    assert(level < vertices_);
    assert(startingVertex < vertices_);

    /* Number of levels is always less or equal to number of nodes */
    std::vector<size_t> levels;
    levels.resize(vertices_); // Max number of levels

    /* Respective level of each node */
    std::vector<size_t> levelTracker;
    levelTracker.resize(vertices_, std::numeric_limits<size_t>::max()); // Initialize with max to indicate unvisited/unassigned
    levelTracker[startingVertex] = 0;

    std::queue<size_t> queue;
    queue.push(startingVertex);

    while (not queue.empty())
    {
        const size_t currentVertex = queue.front();
        const size_t currentLevel = levelTracker[currentVertex];
        ++levels[currentLevel];

        for (size_t adjacent : list_[currentVertex])
        {
            if (levelTracker[adjacent] == std::numeric_limits<size_t>::max()) // Equivalent to checking if not visited
            {
                levelTracker[adjacent] = levelTracker[currentVertex] + 1;
                queue.push(adjacent);
            }
        }
        queue.pop();
    }
    return levels[level];
}

bool AdjacencyList::isStronglyConnected(size_t startingVertex) const
{
    assert(startingVertex < vertices_);

    auto visited = visitedBFS(list_, startingVertex);
    if (not allVisited(visited))
    {
        return false;
    }
    visited = visitedBFS(reversedList(), startingVertex);
    return allVisited(visited);
}

std::vector<bool> AdjacencyList::visitedBFS(const std::vector<std::list<size_t>>& list, size_t startingVertex) const
{
    std::vector<bool> visited;
    visited.resize(vertices_);
    visited[startingVertex] = true;

    std::queue<size_t> queue;
    queue.push(startingVertex);

    while (not queue.empty())
    {
        for (size_t adjacent : list[queue.front()])
        {
            if (not visited[adjacent])
            {
                visited[adjacent] = true;
                queue.push(adjacent);
            }
        }
        queue.pop();
    }
    return visited;
}

bool AdjacencyList::allVisited(const std::vector<bool>& visited) const
{
    for (bool isVisited : visited)
    {
        if (not isVisited)
        {
            return false;
        }
    }
    return true;
}

std::vector<std::list<size_t>> AdjacencyList::reversedList() const
{
    std::vector<std::list<size_t>> reversed;
    reversed.resize(vertices_);
    const size_t listSize = list_.size();
    for (size_t v = 0; v < listSize; ++v)
    {
        for (size_t w : list_[v])
        {
            reversed[w].push_back(v);
        }
    }
    return reversed;
}
