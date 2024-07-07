#include <iostream>
#include "BehaviorTree.h"
#include "AStar.h"
#include "UCS.h"
#include "GeneticAlgorithm.h"

void displayMenu() {
    std::cout << "Choose an action:\n";
    std::cout << "1. Explore the black hole\n";
    std::cout << "2. Gather resources\n";
    std::cout << "3. Engage an enemy\n";
    std::cout << "4. Flee from an enemy\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice: ";
}


void displayLogo() {
    std::cout << "=====================================================================================================\n";
    std::cout << R"(
            ╔══════════════════════════════════════════════════════════════════════════════╗
            ║                                                                              ║
            ║                                                                              ║
            ║   _______  ___      _______  _______  ___   _                                ║
            ║  |  _    ||   |    |   _   ||       ||   | | |                               ║
            ║  | |_|   ||   |    |  |_|  ||       ||   |_| |                               ║
            ║  |       ||   |    |       ||       ||      _|                               ║
            ║  |  _   | |   |___ |       ||      _||     |_                                ║
            ║  | |_|   ||       ||   _   ||     |_ |    _  |                               ║
            ║  |_______||_______||__| |__||_______||___| |_|                               ║
            ║   __   __  _______  ___      _______                                         ║
            ║  |  | |  ||  _    ||   |    |       |                                        ║
            ║  |  |_|  || | |   ||   |    |    ___|                                        ║
            ║  |       || | |   ||   |    |   |___                                         ║
            ║  |       || |_|   ||   |___ |    ___|                                        ║
            ║  |   _   ||       ||       ||   |___                                         ║
            ║  |__| |__||_______||_______||_______|                                        ║
            ║   _______  __   __  _______  ___      _______  ______    _______  ______     ║
            ║  |       ||  |_|  ||       ||   |    |  _    ||    _ |  |       ||    _ |    ║
            ║  |___    ||       ||    _  ||   |    | | |   ||   | ||  |___    ||   | ||    ║
            ║   ___|   ||       ||   |_| ||   |    | | |   ||   |_||_  ___|   ||   |_||_   ║
            ║  |___    | |     | |    ___||   |___ | |_|   ||    __  ||___    ||    __  |  ║
            ║   ___|   ||   _   ||   |    |       ||       ||   |  | | ___|   ||   |  | |  ║
            ║  |_______||__| |__||___|    |_______||_______||___|  |_||_______||___|  |_|  ║
            ║                                                                              ║
            ║                                                                              ║
            ╚══════════════════════════════════════════════════════════════════════════════╝
            )" << std::endl;

    std::cout << "                             ================= By KRiSTO  ==================\n";
    std::cout << "=====================================================================================================\n";
    std::cout << "=====================================================================================================\n";
};

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

