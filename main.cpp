#include <iostream>
#include "BehaviorTree.h"
#include "AStar.h"
#include "UCS.h"
#include "GeneticAlgorithm.h"
#include "Graphics.h"
#include "blackboard.hpp"
#include "Map.h"

int main() {
    Blackboard blackboard;
    blackboard.setInEnvironment("health", 100);
    blackboard.setInEnvironment("enemy_health", 100);
    blackboard.setInEnvironment("attack_power", 20);
    blackboard.setInEnvironment("heal_amount", 20);

    Map gameMap(100, 10);  
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

    while (gameRunning) {
        gameMap.display();  // Display the map
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
        }
    }

    return 0;
}
