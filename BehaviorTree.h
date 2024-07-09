#ifndef BEHAVIOR_TREE_H
#define BEHAVIOR_TREE_H

#include <stack>
#include <unordered_map>
#include <vector>
#include <string>
#include "blackboard.hpp"
#include "map.h"
#include <ncurses.h>

class BehaviorTree {
public:
    BehaviorTree(Blackboard* blackboard, Map* map);
    void update();
    void exploreBlackHole(WINDOW* mapWin, WINDOW* infoWin);
    void engageEnemy(WINDOW* win);

private:
    Blackboard* blackboard_;
    Map* map_;
    std::vector<std::string> behaviors;
    std::unordered_map<std::string, int> directions;
    std::stack<std::string> movementHistory;

    bool checkPattern();
    void handleEncounter(char encounter, WINDOW* win);
    void simulateBattle(WINDOW* win);
};

#endif // BEHAVIOR_TREE_H
