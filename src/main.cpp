#include <iostream>
#include "Node.hpp"
#include "SearchAlgorithms.hpp"
#include "Visualizer.hpp"

int main() {
    Node* root = new Node(1);
    root->addChild(2);
    root->addChild(3);
    root->children[0]->addChild(4);
    root->children[0]->addChild(5);
    root->children[1]->addChild(6);

    std::cout << "BFS:" << std::endl;
    SearchAlgorithms::BFS(root);

    std::cout << "DFS:" << std::endl;
    SearchAlgorithms::DFS(root);

    std::cout << "IDS:" << std::endl;
    SearchAlgorithms::IDS(root, 3);

    std::cout << "UCS:" << std::endl;
    SearchAlgorithms::UCS(root);

    std::cout << "A*:" << std::endl;
    SearchAlgorithms::AStar(root);

    std::cout << "Backtracking:" << std::endl;
    SearchAlgorithms::Backtracking(root, 5);

    Visualizer::visualize(root, "tree.dot");

    delete root;
    return 0;
}
