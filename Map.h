#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <unordered_map>
#include "blackboard.hpp"
#include <utility>
#include <ncurses.h>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

class Map {
public:
    Map(int width, int height, Blackboard* blackboard);
    int getAstronautX() const;
    int getAstronautY() const;
    void initializeGrid();
    void display(WINDOW* win) const;
    bool moveAstronaut(const std::string& direction, WINDOW* infoWin);
    void placeCharacter(int x, int y, const std::string& symbol);
    void addVillain(int x, int y, const std::string& symbol);
    void moveVillains();
    bool checkCollision(int x, int y) const;

private:
    int width_;
    int height_;
    int astronautX_;
    int astronautY_;
    Blackboard* blackboard_;
    std::vector<std::vector<std::string>> grid_;
    std::vector<std::pair<int, int>> villainPositions_;
    std::unordered_map<std::pair<int, int>, std::string, pair_hash> villainSymbols_;

    bool isWithinBounds(int x, int y) const;
    void clearOldPosition(int x, int y);
    void clearGrid();
};

#endif // MAP_H
