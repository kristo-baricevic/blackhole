#include "BehaviorTree.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Graphics.h"
BehaviorTree::BehaviorTree() {
    behaviors = { "Explore", "Gather", "Fight", "Flee", "Puzzle" };
    directions = { {"N", 0}, {"S", 1}, {"E", 2}, {"W", 3} };
    std::srand(std::time(0));  // Seed for random number generation
}

Action BehaviorTree::getAction() {
    return static_cast<Action>(std::rand() % behaviors.size());
}

void BehaviorTree::update() {
    Action action = getAction();
    switch(action) {
        case EXPLORE:
            exploreBlackHole();
            break;
        case GATHER:
            std::cout << "Gathering resources...\n";
            break;
        case FIGHT:
            simulateBattle();
            break;
        case FLEE:
            std::cout << "Fleeing from an enemy...\n";
            break;
        case PUZZLE:
            std::cout << "Solving a puzzle...\n";
            break;
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
    std::cout << "You have encountered a wild black hole jelly...\n";

    int playerHealth = 100;
    int enemyHealth = 100;
    int playerAttack = 20;
    int enemyAttack = 15;

    while (playerHealth > 0 && enemyHealth > 0) {
        // Player's turn
        enemyHealth -= playerAttack;
        std::cout << "You attack the enemy! Enemy health: " << enemyHealth << "\n";

        if (enemyHealth <= 0) {
            std::cout << "You defeated the enemy!\n";
            return;
        }

        // Enemy's turn
        playerHealth -= enemyAttack;
        std::cout << "Enemy attacks you! Your health: " << playerHealth << "\n";

        if (playerHealth <= 0) {
            std::cout << "You were defeated by the enemy.\n";
            return;
        }
    }
}
