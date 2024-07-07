#ifndef BEHAVIOR_TREE_H
#define BEHAVIOR_TREE_H

#include <vector>
#include <string>
#include <stack>
#include <unordered_map>

enum Action { EXPLORE, GATHER, FIGHT, FLEE, PUZZLE };

class BehaviorTree {
public:
    BehaviorTree();
    Action getAction();
    void update();
    void exploreBlackHole();

private:
    std::vector<std::string> behaviors;
    std::stack<std::string> movementHistory;
    std::unordered_map<std::string, int> directions;
    bool checkPattern();
    void handleEncounter(char encounter);
    void simulateBattle();
};

#endif
