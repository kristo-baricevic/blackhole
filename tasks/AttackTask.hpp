#pragma once

#ifndef ATTACKTASK_HPP
#define ATTACKTASK_HPP

#include "../blackboard.hpp"
#include <iostream>



class AttackTask {
public:
    AttackTask(Blackboard* blackboard) : blackboard_(blackboard) {}

    void execute() {
        int enemyHealth = blackboard_->getInEnvironment<int>("enemy_health");
        int attackPower = blackboard_->getInEnvironment<int>("attack_power");
        enemyHealth -= attackPower;
        blackboard_->setInEnvironment("enemy_health", enemyHealth);
        std::cout << "Attacked enemy! Enemy health: " << enemyHealth << "\n";
    }

private:
    Blackboard* blackboard_;
};

#endif // ATTACKTASK_HPP
