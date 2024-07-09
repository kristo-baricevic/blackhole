#include <iostream>
#include "AStar.h"
#include "UCS.h"
#include "GeneticAlgorithm.h"
#include "Graphics.h"
#include "blackboard.hpp"
#include "Map.h"
#include "NcursesUtils.h"
#include "BehaviorTree.h"

void updateGame(Map& gameMap, WINDOW* mapWin) {
    gameMap.moveVillains();    // Update positions of villains
    gameMap.initializeGrid();  // Reinitialize the grid with updated positions
    gameMap.display(mapWin);   // Now display the updated map
}

int main() {
    initializeNcurses();  // Initialize ncurses

    int height, width;
    getmaxyx(stdscr, height, width);

    // Create windows for the map and information display
    WINDOW* mapWin = newwin(height - 10, width, 0, 0);
    keypad(mapWin, TRUE); // Enable arrow keys for mapWin
    WINDOW* infoWin = newwin(10, width, height - 10, 0);

    // Display the logo in the info window
    displayLogo(infoWin);
    getch();  // Wait for user input to proceed
    werase(infoWin);
    wrefresh(infoWin);

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

    // Example to display the villain image
    displayVillain(infoWin);
    getch();  // Wait for user input to proceed
    werase(infoWin);
    wrefresh(infoWin);

    updateGame(gameMap, mapWin);
    while (gameRunning) {
        // Display the menu in the info window
        mvwprintw(infoWin, 0, 0, "1. Explore the black hole");
        mvwprintw(infoWin, 1, 0, "2. Gather resources");
        mvwprintw(infoWin, 2, 0, "3. Engage an enemy");
        mvwprintw(infoWin, 3, 0, "4. Flee from an enemy");
        mvwprintw(infoWin, 4, 0, "5. Exit");
        mvwprintw(infoWin, 5, 0, "Enter your choice: ");
        wrefresh(infoWin);

        // Get user input via ncurses
        echo();  // Temporarily enable echo for user input
        char choiceStr[2];
        mvwgetnstr(infoWin, 5, 18, choiceStr, 1);
        choice = choiceStr[0] - '0';
        noecho();  // Disable echo again

        switch (choice) {
            case 1:
                behaviorTree.exploreBlackHole(mapWin, infoWin);
                break;
            case 2:
                werase(infoWin);
                mvwprintw(infoWin, 0, 0, "Gathering resources...");
                wrefresh(infoWin);
                behaviorTree.update();
                break;
            case 3:
                werase(infoWin);
                mvwprintw(infoWin, 0, 0, "Engaging an enemy...");
                wrefresh(infoWin);
                behaviorTree.engageEnemy(infoWin);  // Engage an enemy
                break;
            case 4:
                werase(infoWin);
                mvwprintw(infoWin, 0, 0, "Fleeing from an enemy...");
                wrefresh(infoWin);
                behaviorTree.update();
                break;
            case 5:
                werase(infoWin);
                mvwprintw(infoWin, 0, 0, "Exiting the game...");
                wrefresh(infoWin);
                gameRunning = false;
                break;
            default:
                werase(infoWin);
                mvwprintw(infoWin, 0, 0, "Invalid choice. Please try again.");
                wrefresh(infoWin);
                break;
        }

        if (gameRunning) {
            std::vector<Node> path = aStar.findPath(player, enemy);
            ucs.allocateResources(100, 50);
            geneticAlgorithm.evolve();
            
            updateGame(gameMap, mapWin);
        }
    }

    delwin(mapWin);
    delwin(infoWin);

    endNcurses();  // End ncurses mode

    return 0;
}
