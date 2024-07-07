#pragma once

#include "../blackboard.hpp"
#include <iostream>

class ExploreTask {
public:
    ExploreTask(Blackboard* blackboard) : blackboard_(blackboard) {}

    void execute() {
        std::cout << "Exploring...\n";
        // Implement exploration logic using the blackboard
        // For example, set a new state or update some values
        int explorationCount = blackboard_->getInEnvironment<int>("exploration_count", 0);
        blackboard_->setInEnvironment("exploration_count", explorationCount + 1);
        std::cout << "Exploration count: " << explorationCount + 1 << "\n";
    }

private:
    Blackboard* blackboard_;
};
