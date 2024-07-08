#ifndef MAP_H
#define MAP_H

#include <vector>
#include <unordered_map>
#include <string>
#include <utility>
#include "blackboard.hpp"

namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& p) const {
            return std::hash<int>()(p.first) ^ std::hash<int>()(p.second << 1);
        }
    };
}

class Map {
public:
    Map(int width, int height, Blackboard* blackboard);

    void display() const;
    bool moveAstronaut(const std::string& direction);
    void placeCharacter(int x, int y, const std::string& symbol);
    void addVillain(int x, int y, const std::string& symbol);
    void moveVillains();
    bool checkCollision(int x, int y) const;

    int getAstronautX() const;
    int getAstronautY() const;
    void initializeGrid();

private:
    int width_;
    int height_;
    int astronautX_;
    int astronautY_;
    Blackboard* blackboard_;
    std::vector<std::vector<std::string>> grid_;
    std::vector<std::pair<int, int>> villainPositions_;
    std::unordered_map<std::pair<int, int>, std::string> villainSymbols_;

    bool isWithinBounds(int x, int y) const;
    void clearOldPosition(int x, int y);
    void clearGrid();
};

#endif // MAP_H
