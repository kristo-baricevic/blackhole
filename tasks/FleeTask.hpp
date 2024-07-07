#pragma once

#include "../blackboard.hpp"
#include <iostream>

class FleeTask {
public:
    FleeTask(Blackboard* blackboard) : blackboard_(blackboard) {}

    void execute() {
        std::cout << "Fleeing...\n";
        // Implement fleeing logic using the blackboard
        // For example, set a new state or update some values
        int fleeCount = blackboard_->getInEnvironment<int>("flee_count", 0);
        blackboard_->setInEnvironment("flee_count", fleeCount + 1);
        std::cout << "Flee count: " << fleeCount + 1 << "\n";
    }

private:
    Blackboard* blackboard_;
};
