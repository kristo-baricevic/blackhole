#pragma once

#include "../blackboard.hpp"
#include <iostream>
#include <string>

class BattleTask {
public:
    BattleTask(Blackboard* blackboard) : blackboard_(blackboard) {}

    void playerTurn() {
        int enemyHealth = blackboard_->getInEnvironment<int>("enemy_health");
        int playerAttack = blackboard_->getInEnvironment<int>("attack_power");

        std::cout << "Choose your action: [1] Attack [2] Heal: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            enemyHealth -= playerAttack;
            std::cout << "You attack the enemy! Enemy health: " << enemyHealth << "\n";
        } else if (choice == 2) {
            int healAmount = blackboard_->getInEnvironment<int>("heal_amount");
            int playerHealth = blackboard_->getInEnvironment<int>("health");
            playerHealth += healAmount;
            std::cout << "You heal yourself! Your health: " << playerHealth << "\n";
            blackboard_->setInEnvironment("health", playerHealth);
        } else {
            std::cout << "Invalid action. You lose your turn.\n";
        }

        blackboard_->setInEnvironment("enemy_health", enemyHealth);
    }

    void enemyTurn() {
        int playerHealth = blackboard_->getInEnvironment<int>("health");
        int enemyAttack = 15;

        playerHealth -= enemyAttack;
        std::cout << "Enemy attacks you! Your health: " << playerHealth << "\n";
        blackboard_->setInEnvironment("health", playerHealth);
    }

private:
    Blackboard* blackboard_;
};
