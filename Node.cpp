#include "Node.h"

Node::Node(int val, Node* par) : value(val), parent(par) {}

Node::~Node() {
    for (Node* child : children) {
        delete child;
    }
}

void Node::addChild(int val) {
    Node* child = new Node(val, this);
    children.push_back(child);
}
