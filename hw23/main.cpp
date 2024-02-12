#include <cassert>
#include <iostream>
#include <string>

#include "line_manip.hpp"
#include "node.hpp"

int main()
{
    /* Task 1 */
    const std::string str = "Hello Hey Hello Bye Hey";
    assert(uniqueWordsCount(str) == 3);

    /* Task 2 */
    std::cout << "Most occurred word: " << mostOccurredWord(str) << '\n';

    /* Task 3 */
    const std::string balanced = "{ [()][ ] }()";
    assert(isBalanced(balanced) == true);

    const std::string unbalanced1 = "[{]}";
    assert(isBalanced(unbalanced1) == false);

    const std::string unbalanced2 = "[{ [()][ ] }()";
    assert(isBalanced(unbalanced2) == false);

    /* Task 4 */
    Node* node1 = new Node(10);
    Node* node2 = new Node(10);
    Node* node3 = new Node(10);

    node1->next = node2;
    node2->next = node3;
    node3->next = node1;
    assert(hasCycle(node1) == true);

    node3->next = nullptr;
    assert(hasCycle(node1) == false);

    delete node1;
    delete node2;
    delete node3;

    return 0;
}
