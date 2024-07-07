#include "BehaviorTree.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Graphics.h"
#include "tasks/AttackTask.hpp"
#include "tasks/ExploreTask.hpp"
#include "tasks/HealTask.hpp"
#include "tasks/FleeTask.hpp"
#include "conditions/LowHealthCondition.hpp"

BehaviorTree::BehaviorTree(Blackboard* blackboard)
    : blackboard_(blackboard) {
    behaviors = { "Explore", "Attack", "Heal", "Flee" };
    directions = { {"N", 0}, {"S", 1}, {"E", 2}, {"W", 3} };
    std::srand(std::time(0));  // Seed for random number generation
}

void BehaviorTree::update() {
    std::string action = behaviors[std::rand() % behaviors.size()];
    if (action == "Explore") {
        ExploreTask exploreTask(blackboard_);
        exploreTask.execute();
    } else if (action == "Attack") {
        AttackTask attackTask(blackboard_);
        attackTask.execute();
    } else if (action == "Heal") {
        HealTask healTask(blackboard_);
        healTask.execute();
    } else if (action == "Flee") {
        FleeTask fleeTask(blackboard_);
        fleeTask.execute();
    }
}

void BehaviorTree::exploreBlackHole() {
    displayBlackhole();
    std::cout << "You see blackness. Choose a direction (N/S/E/W): ";
    std::string direction;
    std::cin >> direction;

    if (directions.find(direction) == directions.end()) {
        std::cout << "Invalid direction. Try again.\n";
        return;
    }

    movementHistory.push(direction);
    if (movementHistory.size() >= 2) {
        if (checkPattern()) {
            return;
        }
    }

    // Randomly choose between displayBlackhole2 and displayBlackhole3
    if (std::rand() % 2 == 0) {
        displayBlackhole2();
    } else {
        displayBlackhole3();
    }

    std::cout << "You see blackness.\n";
}

bool BehaviorTree::checkPattern() {
    if (movementHistory.size() < 2) {
        return false;
    }

    std::string lastMove = movementHistory.top();
    movementHistory.pop();
    std::string secondLastMove = movementHistory.top();
    movementHistory.push(lastMove);

    if (lastMove == secondLastMove) {
        handleEncounter('A');
        return true;
    }

    if ((lastMove == "W" && secondLastMove == "W")) {
        handleEncounter('B');
        return true;
    }

    if (((lastMove == "N" || lastMove == "S") && 
         (secondLastMove == "E" || secondLastMove == "W")) ||
        ((lastMove == "E" || lastMove == "W") && 
         (secondLastMove == "N" || secondLastMove == "S"))) {
        handleEncounter('C');
        return true;
    }

    return false;
}

void BehaviorTree::handleEncounter(char encounter) {
    switch (encounter) {
        case 'A':
            displayCharacterA();
            std::cout << "You encounter Character A! Answer this geometry question to proceed.\n";
            std::cout << "What is the sum of the interior angles of a triangle?\n";
            int answer;
            std::cin >> answer;
            if (answer == 180) {
                std::cout << "Correct! You may proceed.\n";
            } else {
                std::cout << "Incorrect. Try again next time.\n";
            }
            break;
        case 'B':
            std::cout << "You encounter Character B! Prepare for battle!\n";
            update();  // Trigger the battle simulation
            break;
        case 'C':
            std::cout << "The black hole abstracts away into metaphysical madness...\n";
            std::cout << "Solve the following puzzle to proceed.\n";
            // Placeholder for puzzle logic
            break;
    }

    // Clear movement history to reset the encounter
    while (!movementHistory.empty()) {
        movementHistory.pop();
    }
}

void BehaviorTree::simulateBattle() {
    displayCharacterB();

    std::cout << "Simulating battle...\n";

    int playerHealth = blackboard_->getInEnvironment<int>("health");
    int enemyHealth = blackboard_->getInEnvironment<int>("enemy_health");
    int playerAttack = blackboard_->getInEnvironment<int>("attack_power");
    int enemyAttack = 15;  // This can be set via blackboard as well

    while (playerHealth > 0 && enemyHealth > 0) {
        // Player's turn
        enemyHealth -= playerAttack;
        std::cout << "You attack the enemy! Enemy health: " << enemyHealth << "\n";
        blackboard_->setInEnvironment("enemy_health", enemyHealth);

        if (enemyHealth <= 0) {
            std::cout << "You defeated the enemy!\n";
            blackboard_->setInEnvironment("enemy_health", 100); // Reset enemy health
            return;
        }

        // Enemy's turn
        playerHealth -= enemyAttack;
        std::cout << "Enemy attacks you! Your health: " << playerHealth << "\n";
        blackboard_->setInEnvironment("health", playerHealth);

        if (playerHealth <= 0) {
            std::cout << "You were defeated by the enemy.\n";
            blackboard_->setInEnvironment("health", 100); // Reset player health
            return;
        }
    }
}
