#pragma once

#include "../blackboard.hpp"

class HealthCondition {
public:
    HealthCondition(Blackboard* blackboard, const std::string& key) 
        : blackboard_(blackboard), key_(key) {}

    bool isHealthAboveZero() const {
        int health = blackboard_->getInEnvironment<int>(key_, 0);
        return health > 0;
    }

private:
    Blackboard* blackboard_;
    std::string key_;
};
