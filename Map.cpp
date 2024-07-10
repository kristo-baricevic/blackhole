#include "Map.h"
#include "Graphics.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include "NcursesUtils.h"  // Include the utility functions

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

    // Place stars in every available space
    for (int y = 0; y < grid_.size(); ++y) {
        for (int x = 0; x < grid_[y].size(); ++x) {
            if (grid_[y][x] == " ") {
                grid_[y][x] = "*";
            }
        }
    }
}

void Map::display(WINDOW* win, int winWidth, int winHeight) const {
    clearAndRedrawWindow(win);  // Clear and redraw the window with borders

    // Calculate the scaling factor for the grid to fit within the window
    double scaleX = static_cast<double>(winWidth - 2) / width_; // Adjust for border
    double scaleY = static_cast<double>(winHeight - 2) / height_; // Adjust for border

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            int screenX = static_cast<int>(x * scaleX) + 1;  // Adjust coordinates for border
            int screenY = static_cast<int>(y * scaleY) + 1;  // Adjust coordinates for border

            if (x == astronautX_ && y == astronautY_) {
                mvwaddch(win, screenY, screenX, '@');  // Draw astronaut
            } else {
                bool isVillain = false;
                for (const auto& villain : villainPositions_) {
                    if (x == villain.first && y == villain.second) {
                        mvwaddch(win, screenY, screenX, villainSymbols_.at(villain)[0]);  // Draw villain
                        isVillain = true;
                        break;
                    }
                }
                if (!isVillain) {
                    mvwaddch(win, screenY, screenX, grid_[y][x][0]);  // Draw grid element
                }
            }
        }
    }
    wrefresh(win);
}

bool Map::moveAstronaut(const std::string& direction, WINDOW* infoWin) {
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
        mvwprintw(infoWin, 1, 1, "Invalid direction. Use N, S, E, or W.");
        wrefresh(infoWin);
        return false;
    }

    if (isWithinBounds(newX, newY)) {
        clearOldPosition(astronautX_, astronautY_);
        astronautX_ = newX;
        astronautY_ = newY;
        grid_[astronautY_][astronautX_] = "@";  // Set the new position

        // Check for collision with villains
        if (checkCollision(astronautX_, astronautY_)) {
            displayVillain(infoWin);
            return true;  // Indicate that a battle should occur
        }

        moveVillains();  // Move villains when astronaut moves
        return true;
    } else {
        mvwprintw(infoWin, 1, 1, "Move out of bounds.");
        wrefresh(infoWin);
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
    std::unordered_map<std::pair<int, int>, std::string, pair_hash> newVillainSymbols;

    for (const auto& villain : villainPositions_) {
        int oldX = villain.first;
        int oldY = villain.second;
        
        // Generate a new random position within the grid
        int newX = oldX + (std::rand() % 3 - 1);
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
