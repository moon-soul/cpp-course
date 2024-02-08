#include <cassert>
#include <iostream>

#include "graph.hpp"

int main()
{
    /* Task 1 */
    AdjacencyList graph1(10);
    graph1.addEdge(0, 1);
    graph1.addEdge(0, 2);
    graph1.addEdge(0, 3);
    graph1.addEdge(1, 4);
    graph1.addEdge(2, 5);
    graph1.addEdge(2, 6);
    graph1.addEdge(3, 7);
    graph1.addEdge(4, 8);
    graph1.addEdge(5, 9);

    constexpr size_t level = 2; // 3rd level
    std::cout << "Number of nodes on level [" << level << "]: (" << graph1.numberOfNodesOnLevel(level) << ")\n";
    assert(graph1.numberOfNodesOnLevel(0) == 1);
    assert(graph1.numberOfNodesOnLevel(1) == 3);
    assert(graph1.numberOfNodesOnLevel(2) == 4);
    assert(graph1.numberOfNodesOnLevel(3) == 2);
    assert(graph1.numberOfNodesOnLevel(4) == 0);

    /* Task 2 */
    AdjacencyList graph2(5, Graph::ConnectionType::Directed);
    graph2.addEdge(0, 1);
    graph2.addEdge(1, 3);
    graph2.addEdge(3, 2);
    graph2.addEdge(2, 4);
    graph2.addEdge(2, 0);
    assert(graph2.isStronglyConnected() == false);

    graph2.addEdge(4, 2);
    assert(graph2.isStronglyConnected() == true);

    return 0;
}
