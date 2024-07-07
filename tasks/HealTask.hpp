#pragma once

#ifndef HEALTASK_HPP
#define HEALTASK_HPP

#include "../blackboard.hpp"
#include <iostream>

class HealTask {
public:
    HealTask(Blackboard* blackboard) : blackboard_(blackboard) {}

    void execute() {
        int health = blackboard_->getInEnvironment<int>("health");
        int healAmount = blackboard_->getInEnvironment<int>("heal_amount");
        health += healAmount;
        blackboard_->setInEnvironment("health", health);
        std::cout << "Healed! Health: " << health << "\n";
    }

private:
    Blackboard* blackboard_;
};

#endif // HEALTASK_HPP
