#ifndef BEHAVIOR_TREE_H
#define BEHAVIOR_TREE_H

#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include "blackboard.hpp"

class BehaviorTree {
public:
    BehaviorTree(Blackboard* blackboard);
    void update();
    void exploreBlackHole();

private:
    std::vector<std::string> behaviors;
    std::stack<std::string> movementHistory;
    std::unordered_map<std::string, int> directions;
    Blackboard* blackboard_;

    bool checkPattern();
    void handleEncounter(char encounter);
    void simulateBattle();
};

#endif
