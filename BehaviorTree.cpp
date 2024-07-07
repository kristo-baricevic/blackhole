#include "BehaviorTree.h"
#include <iostream>
#include <cstdlib>

BehaviorTree::BehaviorTree() {
    behaviors = { "Explore", "Gather", "Fight", "Flee", "Puzzle" };
    directions = { {"N", 0}, {"S", 1}, {"E", 2}, {"W", 3} };
}

Action BehaviorTree::getAction() {
    return static_cast<Action>(rand() % behaviors.size());
}

void BehaviorTree::update() {
    Action action = getAction();
    switch(action) {
        case EXPLORE:
            exploreBlackHole();
            break;
        case GATHER:
            std::cout << "Gathering resources...\n";
            break;
        case FIGHT:
            std::cout << "Engaging an enemy...\n";
            break;
        case FLEE:
            std::cout << "Fleeing from an enemy...\n";
            break;
        case PUZZLE:
            std::cout << "Solving a puzzle...\n";
            break;
    }
}

void BehaviorTree::exploreBlackHole() {
               std::cout << R"(
                                                     ........................................-----------+++---------+##++++####+++###+
                                             ...........................................----------+++--+++++----++++++####+++##++-
                                          ...........---+++++-++++----------..........-----------++#########+--+++++####++-+###+-+
                                      . ........--++#######+++---+----------..----------------+############+-+#+#++####++++++-+++#
                                 . ..........--+#######+----------------------------------++##############++#+##+#####+-++#+-++###
                               . .........--+##--+##+--------------------------------+++#################+##########+--++#+++#####
                             . .........-+++-.-###+-------------------------+++++++################################+--+##++#######
                            . ........--++---##+---------++++++#####++++++++++###################################+--++#+++######+-
                           ..........-+-+--##+------+++########################################################+--+##++#######+--.
                          . .......-+++--+#+-------+##################################+######################+---##########++-....
                         . .......-+++--#+------+###########################################################+--+#########++-......
                         ........-#++-+#+-----+###########################################################++++#########+--........
                       . .......-###+##------+#############--........---+################################+++#########+--..........
                       ........-######+-----+###########-..............----+###########################++++########+--............
                       .......-+#####+-----+##########+-....      .........--########################++++#+######+--..............
                      . ......-######-----+##########-....        .........+#######################++++#+######+--................
                      .......--#####+-----##########.....           .  ...-###+##################++++++######+--..................
               .      .......-+#####-----+#########-...              ...-###+++################++++++######+---...................
                     . ......-+####+-----+#########...             ...+###+-+################++++++#####++---.....................
                      .......-+###++-----+########+...         ....-+##+-++####++##########+++#++#####++---..................... .
                     . ......--###+------++########...        ...-###+++#####+-+#########+++##+#####++---...................... . 
                      ........-+#+--------+########-...     ....+###+######+-+#####################+----..................... .   
                     . ........-+#--------++#######+....  ....-###++#####+-+#####################+----.................... .      
                      .........-++---------++#######-......--####+#####+--++##################++----......................        
                       .........-++--------++########+-----####++#####--++##################+++---...................... . .      
                       .........----------++###########++###+-+#####+-++##################+++---........................ .        
                      . .........---------++###############++#####---+##################++---.......................... . .       
                       ...........-------++####################+--+###################+----............................. .        
                       ...........------++#########################################++----.....---....................... . .      
                        ............-----###++++###########++####################++---......----........................ .        
                      . .............---+#+++###########+--+###################+----.....-----........................ .. . .     
                        .............---+########++###+--+###########++######+---.......----........................... .         
                       . ...........---++++++++++###--++#+#########+++#####+---.......-----............................. . . .  . 
                        ...........------------+#+--+#+++########+++#####+---.......--+--............................. .          
                       .........-.-----------+#+--+#++++#######+++#####+---.......--+--.............................. .           
                        ..........--++-----+#--+#+-+++########+######+---.......--+--.............................. .             
                       ..........-++++---++--+#+--++################---.......--+--.............................. .. .            
                       .........--+++++----++---++################+--.....-------.............................. .                 
                       .........--++----+++----+################+---...----++--.............................. . .                                               
            )" << std::endl;
    std::cout << "You see blackness. Choose a direction (N/S/E/W): ";
    std::string direction;
    std::cin >> direction;

    if (directions.find(direction) == directions.end()) {
        std::cout << "Invalid direction. Try again.\n";
        return;
    }

    movementHistory.push(direction);
    if (movementHistory.size() >= 2) {
        if (checkPattern()) {
            movementHistory.pop(); // Clean up the stack after pattern check
            return;
        }
    }

    std::cout << "You see blackness.\n";
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

    if ((lastMove == "N" && secondLastMove == "S") || 
        (lastMove == "S" && secondLastMove == "N") || 
        (lastMove == "E" && secondLastMove == "W") || 
        (lastMove == "W" && secondLastMove == "E")) {
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
            std::cout << "You encounter Character A! Answer this geometry question to proceed.\n";
            std::cout << R"(
                                                  ░                                                        
                                                   ▒░                                                      
                                            ░     ▒░                                                       
                                            ▓     ▓█▓░                                                     
                                            █▓▒░    ░█▓▒                                                   
                                              ▒█▓▒    ▒▓░                                                  
                                                ░▓▒  ▒▒▓                                                   
                      ░░░▓█▒              ▒▓▓▓▓▒░▓▒▒▒▒▒▒ ▒▒▓▓▒            ░▓▓░                             
                          ▒█▒            ░███▓▓▓▓▓████▓▒▒▒▓▓▓▓▓   ░░░░░░▒▓▓                                
                           ▒██▓▒▒▓▓▓███▓▒▒░███▓▓█▓██████▓█▓██▓░▒▓███▒░░░                                   
                             ▒▓███▓▓▒▒▒▓█████▓▓▓██████████▓▒▒▒▓▓█░                                         
                                           ░██▓████████████▓▓▓▓▓▓░                                         
                                ░▓██▓▒░     ▒█████████▓▓██▓█▓▒▒▒▒▓▒▒▒░                                     
                              ▒▓▒    ░▓██▓▓▓████████████████▓▓▓███████▓▓░                                  
                          ▒▓█▓              ▓▓▓███████████▓███▓▓▓▓░  ░███▓▓░                               
                                          ▒▓███▒▒▓▓▓▓█████▓▓█████▓▓▓▓░  ░▓███▓▓▒░░░░                       
                                        ▒▓███░▓▓▓▓▓██▓█▓▓▒▓▓▓░▓███▓▓▓█      ░▓██████▓▓██▓░                 
                                     ▒▓▓███░ ░██▓█▓██▒▓▓▒ ██▓░ ░█████░                                     
                              ▒▒▓███████▒     ▒█████▒ ▓▓░  ▓█▓▒   ░                                        
                           ▒████▓▓▒░                  ▓▓░    ▓██▒░                                         
                         ▒██▒                         ▓▓░      ░██▓▒                                       
                        ▓█▒                           ▓▓░         ▒█▓░                                     
                       ░█░                            ▓▓            ▓█▒                                    
                       ▒▓                            ░▓▒             ░█▓                                   
                                                    ▒▓▒               ▒▓▒                                  
                                                  ░██                 ░▓▓                                  
                                                  █░                   ▓▓                                  
                                                                       ▓█                                  
            )" << std::endl;
            std::cout << "What is the sum of the interior angles of a triangle?\n";
            int answer;
            std::cin >> answer;
            if (answer == 180) {
                std::cout << "Correct! You may proceed.\n";
            } else {
                std::cout << "Incorrect. Try again next time.\n";
            }
            break;
        case 'B':
            std::cout << "You encounter Character B!\n";
            break;
        case 'C':
            std::cout << "The black hole abstracts away into metaphysical madness...\n";
            std::cout << "Solve the following puzzle to proceed.\n";
            // Placeholder for puzzle logic
            break;
    }
}