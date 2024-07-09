#include <iostream>
#include "BehaviorTree.h"
#include "AStar.h"
#include "UCS.h"
#include "GeneticAlgorithm.h"
#include "Graphics.h"
#include "blackboard.hpp"
#include "Map.h"
#include "NcursesUtils.h" // Include the ncurses utility header

void updateGame(Map& gameMap) {
    gameMap.moveVillains();    // Update positions of villains
    gameMap.initializeGrid();  // Reinitialize the grid with updated positions
    gameMap.display();         // Now display the updated map
}

void displayLogo() {
    displayFile("logo.txt");
}


int main() {
    initializeNcurses();  // Initialize ncurses

    Blackboard blackboard;
    blackboard.setInEnvironment("health", 100);
    blackboard.setInEnvironment("enemy_health", 100);
    blackboard.setInEnvironment("attack_power", 20);
    blackboard.setInEnvironment("heal_amount", 20);

    Map gameMap(120, 10, &blackboard);  // Create a 120x10 map
    gameMap.addVillain(13, 3, "<^>"); 
    gameMap.addVillain(37, 7, "<^>");  
    gameMap.addVillain(53, 5, "<^>");  
    gameMap.addVillain(78, 2, "<^>");  
    gameMap.addVillain(98, 6, "<^>"); 

    gameMap.initializeGrid();  // Initialize the grid before starting the game loop

    BehaviorTree behaviorTree(&blackboard, &gameMap);
    
    AStar aStar;
    UCS ucs;
    GeneticAlgorithm geneticAlgorithm;

    Node player(0, 0, 0);
    Node enemy(5, 5, 0);

    bool gameRunning = true;
    int choice;

    // Display the logo once at the beginning
    displayLogo();
    getch();  // Wait for user input to proceed
    clear();  // Clear the screen after displaying the logo

    // displayLargeAstronaut();
    updateGame(gameMap);
    while (gameRunning) {
        displayMenu();

        // Get user input via ncurses
        echo();  // Temporarily enable echo for user input
        char choiceStr[2];
        mvgetnstr(6, 18, choiceStr, 1);
        choice = choiceStr[0] - '0';
        noecho();  // Disable echo again

        switch (choice) {
            case 1:
                behaviorTree.exploreBlackHole();
                break;
            case 2:
                clear();
                mvprintw(0, 0, "Gathering resources...\n");
                refresh();
                behaviorTree.update();
                break;
            case 3:
                clear();
                mvprintw(0, 0, "Engaging an enemy...\n");
                refresh();
                behaviorTree.engageEnemy();  // Engage an enemy
                break;
            case 4:
                clear();
                mvprintw(0, 0, "Fleeing from an enemy...\n");
                refresh();
                behaviorTree.update();
                break;
            case 5:
                clear();
                mvprintw(0, 0, "Exiting the game...\n");
                refresh();
                gameRunning = false;
                break;
            default:
                clear();
                mvprintw(0, 0, "Invalid choice. Please try again.\n");
                refresh();
                break;
        }

        if (gameRunning) {
            std::vector<Node> path = aStar.findPath(player, enemy);
            ucs.allocateResources(100, 50);
            geneticAlgorithm.evolve();
            
            updateGame(gameMap);
        }
    }

    endNcurses();  // End ncurses mode

    return 0;
}
