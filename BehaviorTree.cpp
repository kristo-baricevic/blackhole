#include "BehaviorTree.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Graphics.h"
#include "Map.h"
#include "tasks/BattleTask.hpp"
#include "tasks/ExploreTask.hpp"
#include "conditions/HealthCondition.hpp"

BehaviorTree::BehaviorTree(Blackboard* blackboard, Map* map)
    : blackboard_(blackboard), map_(map) {
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
        // Attack task logic if needed
    } else if (action == "Heal") {
        // Heal task logic if needed
    } else if (action == "Flee") {
        // Flee task logic if needed
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

    if (!map_->moveAstronaut(direction)) {
        std::cout << "Movement failed.\n";
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

    // Check if the astronaut encounters a villain
    if (map_->checkCollision(map_->getAstronautX(), map_->getAstronautY())) {
        engageEnemy();
    }
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
            displayCharacterB();
            std::cout << "You encounter Character B! Prepare for battle!\n";
            simulateBattle();  // Trigger the battle sequence
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
    std::cout << "Battle begins!\n";

    BattleTask battleTask(blackboard_);
    HealthCondition playerHealthCond(blackboard_, "health");
    HealthCondition enemyHealthCond(blackboard_, "enemy_health");

    bool playerDefeated = false;
    bool enemyDefeated = false;

    while (!playerDefeated && !enemyDefeated) {
        battleTask.playerTurn();
        if (!enemyHealthCond.isHealthAboveZero()) {
            enemyDefeated = true;
            std::cout << "You defeated the enemy!\n";
            break;
        }

        battleTask.enemyTurn();
        if (!playerHealthCond.isHealthAboveZero()) {
            playerDefeated = true;
            std::cout << "You were defeated by the enemy.\n";
            break;
        }
    }

    // Reset health after the battle ends
    if (playerDefeated) {
        blackboard_->setInEnvironment("health", 100);
    }

    if (enemyDefeated) {
        blackboard_->setInEnvironment("enemy_health", 100);
    }
}

void BehaviorTree::engageEnemy() {
    displayCharacterB();
    std::cout << "Engaging an enemy! Prepare for battle!\n";
    simulateBattle();
}
