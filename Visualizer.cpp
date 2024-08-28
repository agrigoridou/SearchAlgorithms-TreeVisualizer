#include "Visualizer.h"
#include <fstream>
#include <iostream>
#include <functional>

void Visualizer::visualize(Node* root, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file for visualization: " << filename << std::endl;
        return;
    }

    file << "digraph G {\n";
    std::function<void(Node*)> traverse = [&](Node* node) {
        for (Node* child : node->children) {
            file << "  " << node->value << " -> " << child->value << ";\n";
            traverse(child);
        }
    };
    traverse(root);
    file << "}\n";
    file.close();

    if (system("dot -Tpng current_graph.dot -o current_graph.png") != 0) {
        std::cerr << "Failed to create PNG from DOT file." << std::endl;
    }
}
