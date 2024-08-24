#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "Node.h"
#include <string>

class Visualizer {
public:
    static void visualize(Node* root, const std::string& filename);
};

#endif // VISUALIZER_H
