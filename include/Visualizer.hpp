#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include "Node.hpp"
#include <string>

class Visualizer {
public:
    static void visualize(Node* root, const std::string& filename);
};

#endif
