#include "Visualizer.hpp"
#include <fstream>
#include <functional>

void Visualizer::visualize(Node* root, const std::string& filename) {
    std::ofstream file(filename);
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
}
