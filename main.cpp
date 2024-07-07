#include <iostream>
#include "BehaviorTree.h"
#include "AStar.h"
#include "UCS.h"
#include "GeneticAlgorithm.h"
#include "Graphics.h"

int main() {
    BehaviorTree behaviorTree;
    AStar aStar;
    UCS ucs;
    GeneticAlgorithm geneticAlgorithm;

    Node player(0, 0, 0);
    Node enemy(5, 5, 0);

    bool gameRunning = true;
    int choice;
        displayLogo();

    while (gameRunning) {
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
                behaviorTree.update();
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

