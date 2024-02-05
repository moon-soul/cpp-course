#pragma once

struct Node
{
    int data;
    Node* next;

    Node(int nodeData)
    {
        data = nodeData;
        next = nullptr;
    }
};

bool hasCycle(Node* head);
