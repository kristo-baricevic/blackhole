#include "Map.h"
#include "Graphics.h"
#include <iostream>

Map::Map(int width, int height)
    : width_(width), height_(height), astronautX_(width / 2), astronautY_(height / 2) {
    grid_ = std::vector<std::vector<char>>(height, std::vector<char>(width, ' '));
    grid_[astronautY_][astronautX_] = 'A';  // Initial position of the astronaut
}

void Map::display() const {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < (width_); ++x) {
            if (x == astronautX_ && y == astronautY_) {
                displayAstronaut();
            } else {
                displayOuterSpace();
            }
        }
        std::cout << '\n';
    }
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

    if (newX >= 0 && newX < width_ && newY >= 0 && newY < height_) {
        grid_[astronautY_][astronautX_] = ' ';  // Clear the old position
        astronautX_ = newX;
        astronautY_ = newY;
        grid_[astronautY_][astronautX_] = 'A';  // Set the new position
        return true;
    } else {
        std::cout << "Move out of bounds.\n";
        return false;
    }
}

void Map::placeCharacter(int x, int y, char symbol) {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
        grid_[y][x] = symbol;
    }
}
