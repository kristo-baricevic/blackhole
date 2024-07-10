#include <iostream>
#include <vector>
#include <ncurses.h>

// Custom headers
#include "AStar.h"
#include "UCS.h"
#include "GeneticAlgorithm.h"
#include "Graphics.h"
#include "blackboard.hpp"
#include "Map.h"
#include "NcursesUtils.h"
#include "BehaviorTree.h"

// Constants
const int DASHBOARD_HEIGHT = 10;
const int SCREEN_WIDTH = 80; // Fixed width for the screen
const int SCREEN_HEIGHT = 24; // Fixed height for the screen

void updateGame(Map& gameMap, WINDOW* mapWin, int winWidth, int winHeight) {
    gameMap.moveVillains();    // Update positions of villains
    gameMap.initializeGrid();  // Reinitialize the grid with updated positions
    gameMap.display(mapWin, winWidth, winHeight);   // Now display the updated map
}

int main() {
    initializeNcurses();

    // Create windows for the screen (TV) and dashboard
    WINDOW* screenWin = newwin(SCREEN_HEIGHT - DASHBOARD_HEIGHT, SCREEN_WIDTH, 0, 0);
    WINDOW* dashboardWin = newwin(DASHBOARD_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - DASHBOARD_HEIGHT, 0);

    // Add borders to the windows
    box(screenWin, 0, 0);
    box(dashboardWin, 0, 0);
    wrefresh(screenWin);
    wrefresh(dashboardWin);

    // Display the logo in the screen window
    displayLogo(screenWin);
    getch();  // Wait for user input to proceed
    clearAndRedrawWindow(screenWin);
    wrefresh(dashboardWin);

    Blackboard blackboard;
    blackboard.setInEnvironment("health", 100);
    blackboard.setInEnvironment("enemy_health", 100);
    blackboard.setInEnvironment("attack_power", 20);
    blackboard.setInEnvironment("heal_amount", 20);

    Map gameMap(120, 120, &blackboard);  // Create a 120x120 map
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

    updateGame(gameMap, screenWin, SCREEN_WIDTH, SCREEN_HEIGHT - DASHBOARD_HEIGHT);

    while (gameRunning) {
    //     // Display the menu in the dashboard window
        clearAndRedrawWindow(dashboardWin);
    //     mvwprintw(dashboardWin, 1, 1, "1. Explore the black hole");
    //     mvwprintw(dashboardWin, 2, 1, "2. Gather resources");
    //     mvwprintw(dashboardWin, 3, 1, "3. Engage an enemy");
    //     mvwprintw(dashboardWin, 4, 1, "4. Flee from an enemy");
    //     mvwprintw(dashboardWin, 5, 1, "5. Exit");
    //     mvwprintw(dashboardWin, 6, 1, "Enter your choice: ");
    //     wrefresh(dashboardWin);

    //     // Get user input via ncurses
    //     echo();  // Temporarily enable echo for user input
    //     char choiceStr[2];
    //     mvwgetnstr(dashboardWin, 6, 19, choiceStr, 1);
    //     choice = choiceStr[0] - '0';
    //     noecho();  // Disable echo again

    //     switch (choice) {
    //         case 1:
    //             behaviorTree.exploreBlackHole(screenWin, dashboardWin);
    //             break;
    //         case 2:
    //             clearAndRedrawWindow(screenWin);
    //             mvwprintw(dashboardWin, 1, 1, "Gathering resources...");
    //             wrefresh(dashboardWin);
    //             behaviorTree.update();
    //             getch();  // Wait for user input to proceed
    //             clearAndRedrawWindow(dashboardWin);  // Clear dashboard after displaying message
    //             break;
    //         case 3:
    //             clearAndRedrawWindow(screenWin);
    //             mvwprintw(dashboardWin, 1, 1, "Engaging an enemy...");
    //             wrefresh(dashboardWin);
    //             behaviorTree.engageEnemy(screenWin);  // Engage an enemy
    //             getch();  // Wait for user input to proceed
    //             clearAndRedrawWindow(dashboardWin);  // Clear dashboard after displaying message
    //             break;
    //         case 4:
    //             clearAndRedrawWindow(screenWin);
    //             mvwprintw(dashboardWin, 1, 1, "Fleeing from an enemy...");
    //             wrefresh(dashboardWin);
    //             behaviorTree.update();
    //             getch();  // Wait for user input to proceed
    //             clearAndRedrawWindow(dashboardWin);  // Clear dashboard after displaying message
    //             break;
    //         case 5:
    //             clearAndRedrawWindow(screenWin);
    //             mvwprintw(dashboardWin, 1, 1, "Exiting the game...");
    //             wrefresh(dashboardWin);
    //             gameRunning = false;
    //             getch();  // Wait for user input to proceed
    //             clearAndRedrawWindow(dashboardWin);  // Clear dashboard after displaying message
    //             break;
    //         default:
    //             clearAndRedrawWindow(screenWin);
    //             mvwprintw(dashboardWin, 1, 1, "Invalid choice. Please try again.");
    //             wrefresh(dashboardWin);
    //             getch();  // Wait for user input to proceed
    //             clearAndRedrawWindow(dashboardWin);  // Clear dashboard after displaying message
    //             break;
    //     }

    //     if (gameRunning) {
    //         std::vector<Node> path = aStar.findPath(player, enemy);
    //         ucs.allocateResources(100, 50);
    //         geneticAlgorithm.evolve();
            
    //         updateGame(gameMap, screenWin, SCREEN_WIDTH, SCREEN_HEIGHT - DASHBOARD_HEIGHT);
    //     }
    }

    delwin(screenWin);
    delwin(dashboardWin);

    endNcurses();  // End ncurses mode

    return 0;
}
