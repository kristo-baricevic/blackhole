#ifndef ASTAR_H
#define ASTAR_H

#include <vector>

struct Node {
    int x, y;
    float cost;
    Node* parent;
    Node(int x, int y, float cost) : x(x), y(y), cost(cost), parent(nullptr) {}
};

class AStar {
public:
    std::vector<Node> findPath(Node start, Node goal);
};

#endif
