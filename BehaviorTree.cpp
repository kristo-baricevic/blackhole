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

void BehaviorTree::exploreBlackHole(WINDOW* mapWin, WINDOW* infoWin) {
    wclear(infoWin);
    mvwprintw(infoWin, 0, 0, "Use the arrow keys to navigate (press 'q' to quit): ");
    wrefresh(infoWin);

    int ch;
    while ((ch = wgetch(mapWin)) != 'q') {
        switch (ch) {
            case KEY_UP:
                map_->moveAstronaut("N", infoWin);
                break;
            case KEY_DOWN:
                map_->moveAstronaut("S", infoWin);
                break;
            case KEY_LEFT:
                map_->moveAstronaut("W", infoWin);
                break;
            case KEY_RIGHT:
                map_->moveAstronaut("E", infoWin);
                break;
            default:
                continue; // Ignore other keys
        }

        // Clear the map window and redisplay the map
        wclear(mapWin);
        map_->display(mapWin);
        wrefresh(mapWin);

        // Check if the astronaut encounters a villain
        if (map_->checkCollision(map_->getAstronautX(), map_->getAstronautY())) {
            engageEnemy(infoWin);
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
        handleEncounter('A', nullptr);  // Pass nullptr or a valid WINDOW*
        return true;
    }

    if ((lastMove == "W" && secondLastMove == "W")) {
        handleEncounter('B', nullptr);  // Pass nullptr or a valid WINDOW*
        return true;
    }

    if (((lastMove == "N" || lastMove == "S") && 
         (secondLastMove == "E" || secondLastMove == "W")) ||
        ((lastMove == "E" || lastMove == "W") && 
         (secondLastMove == "N" || secondLastMove == "S"))) {
        handleEncounter('C', nullptr);  // Pass nullptr or a valid WINDOW*
        return true;
    }

    return false;
}

void BehaviorTree::handleEncounter(char encounter, WINDOW* win) {
    switch (encounter) {
        case 'A':
            displayCharacter(win);
            mvwprintw(win, 0, 0, "You encounter Character A! Answer this geometry question to proceed.");
            mvwprintw(win, 1, 0, "What is the sum of the interior angles of a triangle?");
            wrefresh(win);
            int answer;
            mvwscanw(win, 2, 0, "%d", &answer);  // Use mvwscanw
            if (answer == 180) {
                mvwprintw(win, 3, 0, "Correct! You may proceed.");
            } else {
                mvwprintw(win, 3, 0, "Incorrect. Try again next time.");
            }
            wrefresh(win);
            break;
        case 'B':
            displayVillain(win);  // Pass WINDOW* argument
            mvwprintw(win, 0, 0, "You encounter Character B! Prepare for battle!");
            wrefresh(win);
            simulateBattle(win);  // Trigger the battle sequence
            break;
        case 'C':
            mvwprintw(win, 0, 0, "The black hole abstracts away into metaphysical madness...");
            mvwprintw(win, 1, 0, "Solve the following puzzle to proceed.");
            // Placeholder for puzzle logic
            wrefresh(win);
            break;
    }

    // Clear movement history to reset the encounter
    while (!movementHistory.empty()) {
        movementHistory.pop();
    }
}

void BehaviorTree::simulateBattle(WINDOW* win) {
    mvwprintw(win, 0, 0, "Battle begins!");
    wrefresh(win);

    BattleTask battleTask(blackboard_);
    HealthCondition playerHealthCond(blackboard_, "health");
    HealthCondition enemyHealthCond(blackboard_, "enemy_health");

    bool playerDefeated = false;
    bool enemyDefeated = false;

    while (!playerDefeated && !enemyDefeated) {
        battleTask.playerTurn();
        if (!enemyHealthCond.isHealthAboveZero()) {
            enemyDefeated = true;
            mvwprintw(win, 1, 0, "You defeated the enemy!");
            wrefresh(win);
            break;
        }

        battleTask.enemyTurn();
        if (!playerHealthCond.isHealthAboveZero()) {
            playerDefeated = true;
            mvwprintw(win, 1, 0, "You were defeated by the enemy.");
            wrefresh(win);
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

void BehaviorTree::engageEnemy(WINDOW* infoWin) {
    displayVillain(infoWin);
    mvwprintw(infoWin, 0, 0, "Engaging an enemy! Prepare for battle!");
    wrefresh(infoWin);
    simulateBattle(infoWin);
}
