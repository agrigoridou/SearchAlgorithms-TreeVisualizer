#ifndef SEARCHALGORITHMS_H
#define SEARCHALGORITHMS_H


#include "Node.h"

class SearchAlgorithms {
public:
    static void BFS(Node* root);
    static void DFS(Node* root);
    static void IDS(Node* root, int maxDepth);
    static void UCS(Node* root);
    static void AStar(Node* root);
    static bool Backtracking(Node* root, int goal);


    static int heuristic(Node* node);

private:
    static bool DLS(Node* node, int depth);
};


#endif // SEARCHALGORITHMS_H
