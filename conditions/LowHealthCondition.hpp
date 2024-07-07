#ifndef LOWHEALTHCONDITION_HPP
#define LOWHEALTHCONDITION_HPP

#pragma once

#include "../blackboard.hpp"

class LowHealthCondition {
public:
    LowHealthCondition(Blackboard* blackboard, int threshold)
        : blackboard_(blackboard), threshold_(threshold) {}

    bool evaluate() {
        int health = blackboard_->getInEnvironment<int>("health");
        return health < threshold_;
    }

private:
    Blackboard* blackboard_;
    int threshold_;
};

#endif // LOWHEALTHCONDITION_HPP
