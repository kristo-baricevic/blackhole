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

    WINDOW* screenWin = newwin(SCREEN_HEIGHT - DASHBOARD_HEIGHT, SCREEN_WIDTH, 0, 0);
    WINDOW* dashboardWin = newwin(DASHBOARD_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - DASHBOARD_HEIGHT, 0);
    keypad(screenWin, TRUE);
    nodelay(screenWin, TRUE);
    
    box(screenWin, 0, 0);
    box(dashboardWin, 0, 0);
    wrefresh(screenWin);
    wrefresh(dashboardWin);

    displayLogo(screenWin); // Display the logo at the beginning
    getch();  // Wait for user input to proceed
    clearAndRedrawWindow(screenWin);

    Blackboard blackboard;
    blackboard.setInEnvironment("health", 100);
    blackboard.setInEnvironment("enemy_health", 100);
    blackboard.setInEnvironment("attack_power", 20);
    blackboard.setInEnvironment("heal_amount", 20);

    Map gameMap(40, 10, &blackboard);  // Fixed map size to fit within the screen
    gameMap.addVillain(3, 3, "<^>");
    gameMap.addVillain(7, 7, "<^>");
    gameMap.addVillain(5, 5, "<^>");
    gameMap.addVillain(2, 2, "<^>");
    gameMap.addVillain(6, 6, "<^>");

    gameMap.initializeGrid();

    BehaviorTree behaviorTree(&blackboard, &gameMap);
    
    AStar aStar;
    UCS ucs;
    GeneticAlgorithm geneticAlgorithm;

    Node player(0, 0, 0);
    Node enemy(5, 5, 0);

    bool gameRunning = true;
    int choice = 0;

    while (gameRunning) {
        clearAndRedrawWindow(screenWin);
        clearAndRedrawWindow(dashboardWin);
        mvwprintw(dashboardWin, 1, 1, "1. Explore black hole  2. Gather resources");
        mvwprintw(dashboardWin, 2, 1, "3. Engage enemy  4. Flee  5. Exit");
        mvwprintw(dashboardWin, 3, 1, "Use arrow keys to move. Enter choice (1-5): ");
        wrefresh(dashboardWin);

        int ch = wgetch(screenWin);
        std::string direction = "";

        switch (ch) {
            case KEY_UP: direction = "N"; break;
            case KEY_DOWN: direction = "S"; break;
            case KEY_LEFT: direction = "W"; break;
            case KEY_RIGHT: direction = "E"; break;
            case '1': case '2': case '3': case '4': case '5':
                choice = ch - '0';
                break;
        }

        bool astronautMoved = false;
        if (!direction.empty()) {
            astronautMoved = gameMap.moveAstronaut(direction, dashboardWin);
        } else if (choice != 0) {
            switch (choice) {
                case 1: behaviorTree.exploreBlackHole(screenWin, dashboardWin); break;
                case 2: 
                    mvwprintw(dashboardWin, 4, 1, "Gathering resources...");
                    behaviorTree.update();
                    break;
                case 3:
                    mvwprintw(dashboardWin, 4, 1, "Engaging an enemy...");
                    behaviorTree.engageEnemy(dashboardWin);
                    break;
                case 4:
                    mvwprintw(dashboardWin, 4, 1, "Fleeing from an enemy...");
                    behaviorTree.update();
                    break;
                case 5:
                    mvwprintw(dashboardWin, 4, 1, "Exiting the game...");
                    gameRunning = false;
                    break;
            }
            wrefresh(dashboardWin);
            napms(1000);  // Pause to show message
            choice = 0;
        }

        if (astronautMoved) {
            gameMap.moveVillains(); // Move villains after the astronaut moves
        }

        updateGame(gameMap, screenWin, SCREEN_WIDTH, SCREEN_HEIGHT - DASHBOARD_HEIGHT);

        if (gameRunning) {
            std::vector<Node> path = aStar.findPath(player, enemy);
            ucs.allocateResources(100, 50);
            geneticAlgorithm.evolve();
        }

        napms(50);  // Control game speed
    }

    delwin(screenWin);
    delwin(dashboardWin);
    endNcurses();
    return 0;
}
