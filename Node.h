#ifndef NODE_H
#define NODE_H

#include <vector>

class Node {
public:
    int value;
    Node* parent;
    std::vector<Node*> children;

    Node(int val, Node* par = nullptr);
    ~Node();

    void addChild(int val);
};

#endif // NODE_H
