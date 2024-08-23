#include "SearchAlgorithms.hpp"
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_set>
#include <algorithm>

void SearchAlgorithms::BFS(Node* root) {
    if (!root) return;
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        std::cout << "Visited: " << current->value << std::endl;
        for (Node* child : current->children) {
            q.push(child);
        }
    }
}

void SearchAlgorithms::DFS(Node* root) {
    if (!root) return;
    std::stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        Node* current = s.top();
        s.pop();
        std::cout << "Visited: " << current->value << std::endl;
        for (Node* child : current->children) {
            s.push(child);
        }
    }
}

bool SearchAlgorithms::DLS(Node* node, int depth) {
    if (depth == 0) {
        std::cout << "Visited: " << node->value << std::endl;
        return true;
    }
    for (Node* child : node->children) {
        if (DLS(child, depth - 1)) {
            return true;
        }
    }
    return false;
}

void SearchAlgorithms::IDS(Node* root, int maxDepth) {
    for (int depth = 0; depth <= maxDepth; ++depth) {
        if (DLS(root, depth)) {
            break;
        }
    }
}

struct CompareCost {
    bool operator()(Node* a, Node* b) {
        return a->value > b->value;  // assuming the value represents the cost
    }
};

void SearchAlgorithms::UCS(Node* root) {
    if (!root) return;
    std::priority_queue<Node*, std::vector<Node*>, CompareCost> pq;
    pq.push(root);
    while (!pq.empty()) {
        Node* current = pq.top();
        pq.pop();
        std::cout << "Visited: " << current->value << std::endl;
        for (Node* child : current->children) {
            pq.push(child);
        }
    }
}

int SearchAlgorithms::heuristic(Node* node) {
    return std::abs(node->value - 10);  // Example heuristic
}

struct AStarCompare {
    bool operator()(Node* a, Node* b) {
        return (a->value + SearchAlgorithms::heuristic(a)) > (b->value + SearchAlgorithms::heuristic(b));
    }
};

void SearchAlgorithms::AStar(Node* root) {
    if (!root) return;
    std::priority_queue<Node*, std::vector<Node*>, AStarCompare> pq;
    pq.push(root);
    while (!pq.empty()) {
        Node* current = pq.top();
        pq.pop();
        std::cout << "Visited: " << current->value << std::endl;
        for (Node* child : current->children) {
            pq.push(child);
        }
    }
}

bool SearchAlgorithms::Backtracking(Node* node, int goal) {
    std::cout << "Visited: " << node->value << std::endl;
    if (node->value == goal) {
        return true;
    }
    for (Node* child : node->children) {
        if (Backtracking(child, goal)) {
            return true;
        }
    }
    return false;
}
