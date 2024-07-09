#include "BehaviorTree.h"
#include <cstdlib>
#include <ctime>
#include "Graphics.h"
#include "Map.h"
#include "tasks/BattleTask.hpp"
#include "tasks/ExploreTask.hpp"
#include "conditions/HealthCondition.hpp"
#include <ncurses.h>

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
    clear();
    mvprintw(0, 0, "Use the arrow keys to navigate (press 'q' to quit): ");
    refresh();

    int ch;
    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_UP:
                map_->moveAstronaut("N");
                break;
            case KEY_DOWN:
                map_->moveAstronaut("S");
                break;
            case KEY_LEFT:
                map_->moveAstronaut("W");
                break;
            case KEY_RIGHT:
                map_->moveAstronaut("E");
                break;
            default:
                continue; // Ignore other keys
        }

        // Clear the screen and redisplay the map
        clear();
        mvprintw(0, 0, "Use the arrow keys to navigate (press 'q' to quit): ");
        map_->display();
        refresh();

        // Check if the astronaut encounters a villain
        if (map_->checkCollision(map_->getAstronautX(), map_->getAstronautY())) {
            engageEnemy();
            break;
        }
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
            displayCharacter();
            mvprintw(0, 0, "You encounter Character A! Answer this geometry question to proceed.");
            mvprintw(1, 0, "What is the sum of the interior angles of a triangle?");
            refresh();
            int answer;
            scanw("%d", &answer);
            if (answer == 180) {
                mvprintw(2, 0, "Correct! You may proceed.");
            } else {
                mvprintw(2, 0, "Incorrect. Try again next time.");
            }
            refresh();
            break;
        case 'B':
            displayVillain();
            mvprintw(0, 0, "You encounter Character B! Prepare for battle!");
            refresh();
            simulateBattle();  // Trigger the battle sequence
            break;
        case 'C':
            mvprintw(0, 0, "The black hole abstracts away into metaphysical madness...");
            mvprintw(1, 0, "Solve the following puzzle to proceed.");
            // Placeholder for puzzle logic
            refresh();
            break;
    }

    // Clear movement history to reset the encounter
    while (!movementHistory.empty()) {
        movementHistory.pop();
    }
}

void BehaviorTree::simulateBattle() {
    mvprintw(0, 0, "Battle begins!");
    refresh();

    BattleTask battleTask(blackboard_);
    HealthCondition playerHealthCond(blackboard_, "health");
    HealthCondition enemyHealthCond(blackboard_, "enemy_health");

    bool playerDefeated = false;
    bool enemyDefeated = false;

    while (!playerDefeated && !enemyDefeated) {
        battleTask.playerTurn();
        if (!enemyHealthCond.isHealthAboveZero()) {
            enemyDefeated = true;
            mvprintw(1, 0, "You defeated the enemy!");
            refresh();
            break;
        }

        battleTask.enemyTurn();
        if (!playerHealthCond.isHealthAboveZero()) {
            playerDefeated = true;
            mvprintw(1, 0, "You were defeated by the enemy.");
            refresh();
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
    displayVillain();
    mvprintw(0, 0, "Engaging an enemy! Prepare for battle!");
    refresh();
    simulateBattle();
}
