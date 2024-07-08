#include <iostream>
#include "BehaviorTree.h"
#include "AStar.h"
#include "UCS.h"
#include "GeneticAlgorithm.h"
#include "Graphics.h"
#include "blackboard.hpp"
#include "Map.h"

void updateGame(Map& gameMap) {
    gameMap.moveVillains();    // Update positions of villains
    gameMap.initializeGrid();  // Reinitialize the grid with updated positions
    gameMap.display();         // Now display the updated map
}

int main() {
    Blackboard blackboard;
    blackboard.setInEnvironment("health", 100);
    blackboard.setInEnvironment("enemy_health", 100);
    blackboard.setInEnvironment("attack_power", 20);
    blackboard.setInEnvironment("heal_amount", 20);

    Map gameMap(120, 10, &blackboard);  // Create a 100x10 map
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
    displayLargeAstronaut();
    updateGame(gameMap);
    while (gameRunning) {
          // Update and display game state
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                behaviorTree.exploreBlackHole();
                break;
            case 2:
                std::cout << "Gathering resources...\n";
                behaviorTree.update();
                break;
            case 3:
                std::cout << "Engaging an enemy...\n";
                behaviorTree.engageEnemy();  // Engage an enemy
                break;
            case 4:
                std::cout << "Fleeing from an enemy...\n";
                behaviorTree.update();
                break;
            case 5:
                std::cout << "Exiting the game...\n";
                gameRunning = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }

        if (gameRunning) {
            std::vector<Node> path = aStar.findPath(player, enemy);
            ucs.allocateResources(100, 50);
            geneticAlgorithm.evolve();
            
            updateGame(gameMap);
        }
    }

    return 0;
}