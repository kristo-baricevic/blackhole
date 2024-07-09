#include "Map.h"
#include "Graphics.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>

Map::Map(int width, int height, Blackboard* blackboard)
    : width_(width), height_(height), astronautX_(width / 2), astronautY_(height / 2), blackboard_(blackboard) {
    grid_ = std::vector<std::vector<std::string>>(height, std::vector<std::string>(width, " "));
    grid_[astronautY_][astronautX_] = "@"; 
    std::srand(std::time(0));  

    blackboard_->setInEnvironment("villainPositions", villainPositions_);
}

int Map::getAstronautX() const {
    return astronautX_;
}

int Map::getAstronautY() const {
    return astronautY_;
}

void Map::initializeGrid() {
    // Clear the entire grid
    for (auto& row : grid_) {
        std::fill(row.begin(), row.end(), " ");
    }

    // Redraw the astronaut
    grid_[astronautY_][astronautX_] = "@";

    // Redraw all villains
    for (const auto& villain : villainPositions_) {
        if (isWithinBounds(villain.first, villain.second)) {
            grid_[villain.second][villain.first] = villainSymbols_.at(villain);
        }
    }
}

void Map::display() const {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            if (x == astronautX_ && y == astronautY_) {
                mvprintw(y + 1, x, "@"); // Adjust the position to account for the instruction line
            } else {
                bool isVillain = false;
                for (const auto& villain : villainPositions_) {
                    if (x == villain.first && y == villain.second) {
                        mvprintw(y + 1, x, villainSymbols_.at(villain).c_str());
                        isVillain = true;
                        break;
                    }
                }
                if (!isVillain) {
                    mvprintw(y + 1, x, " "); // Display space
                }
            }
        }
    }
    refresh(); // Refresh the screen to show changes
}


bool Map::moveAstronaut(const std::string& direction) {
    int newX = astronautX_;
    int newY = astronautY_;

   

    if (direction == "N") {
        newY--;
    } else if (direction == "S") {
        newY++;
    } else if (direction == "E") {
        newX++;
    } else if (direction == "W") {
        newX--;
    } else {
        std::cout << "Invalid direction. Use N, S, E, or W.\n";
        return false;
    }

    if (isWithinBounds(newX, newY)) {
        clearOldPosition(astronautX_, astronautY_);
        astronautX_ = newX;
        astronautY_ = newY;
        grid_[astronautY_][astronautX_] = "@";  // Set the new position

        // Check for collision with villains
        if (checkCollision(astronautX_, astronautY_)) {
            displayVillain();
            // std::cout << "You encountered a villain! Prepare for battle!\n";
            return true;  // Indicate that a battle should occur
        }

        moveVillains();  // Move villains when astronaut moves
        return true;
    } else {
        std::cout << "Move out of bounds.\n";
        return false;
    }
}

void Map::placeCharacter(int x, int y, const std::string& symbol) {
    if (isWithinBounds(x, y)) {
        grid_[y][x] = symbol;
    }
}

void Map::addVillain(int x, int y, const std::string& symbol) {
    if (isWithinBounds(x, y)) {
        villainPositions_.emplace_back(x, y);
        villainSymbols_[{x, y}] = symbol;

        // Update villain positions in the blackboard
        blackboard_->setInEnvironment("villainPositions", villainPositions_);
    }
}
void Map::moveVillains() {
    std::vector<std::pair<int, int>> newVillainPositions;
    std::unordered_map<std::pair<int, int>, std::string> newVillainSymbols;

    for (const auto& villain : villainPositions_) {
        int oldX = villain.first;
        int oldY = villain.second;
        
        int newX = oldX + (std::rand() % 3 - 1);  // Move -1, 0, or 1 step
        int newY = oldY + (std::rand() % 3 - 1);

        if (isWithinBounds(newX, newY) && !checkCollision(newX, newY)) {
            newVillainPositions.emplace_back(newX, newY);
            newVillainSymbols[{newX, newY}] = villainSymbols_.at({oldX, oldY});
            
            // Clear old position in grid
            grid_[oldY][oldX] = " ";
        } else {
            newVillainPositions.push_back(villain);
            newVillainSymbols[villain] = villainSymbols_.at(villain);
        }
    }

    // Update class members
    villainPositions_ = newVillainPositions;
    villainSymbols_ = newVillainSymbols;

    // Update grid with new positions
    for (const auto& villain : villainPositions_) {
        grid_[villain.second][villain.first] = villainSymbols_.at(villain);
    }

    // Update villain positions in the blackboard
    blackboard_->setInEnvironment("villainPositions", villainPositions_);
}

bool Map::checkCollision(int x, int y) const {
    for (const auto& villain : villainPositions_) {
        if (x == villain.first && y == villain.second) {
            return true;
        }
    }
    return false;
}

bool Map::isWithinBounds(int x, int y) const {
    return x >= 0 && x < width_ && y >= 0 && y < height_;
}

void Map::clearOldPosition(int x, int y) {
    if (isWithinBounds(x, y)) {
        grid_[y][x] = " ";
    }
}

void Map::clearGrid() {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            grid_[y][x] = " ";
        }
    }
}