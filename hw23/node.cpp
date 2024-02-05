#include "node.hpp"

#include <unordered_set>

bool hasCycle(Node* head)
{
    std::unordered_set<Node*> visited;
    Node* current = head;
    while (current != nullptr)
    {
        const auto [iter, inserted] = visited.insert(current);
        if (not inserted)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}
