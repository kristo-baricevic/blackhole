#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include "blackboard.hpp"

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

class Map {
public:
    Map(int width, int height, Blackboard* blackboard);
    int getAstronautX() const;
    int getAstronautY() const;
    void initializeGrid();
    void display(WINDOW* win, int winWidth, int winHeight) const; // Added winWidth and winHeight
    bool moveAstronaut(const std::string& direction, WINDOW* infoWin);
    void placeCharacter(int x, int y, const std::string& symbol);
    void addVillain(int x, int y, const std::string& symbol);
    void moveVillains();
    bool checkCollision(int x, int y) const;
    bool isWithinBounds(int x, int y) const;
    void clearOldPosition(int x, int y);
    void clearGrid();

private:
    int width_;
    int height_;
    int astronautX_;
    int astronautY_;
    std::vector<std::vector<std::string>> grid_;
    std::vector<std::pair<int, int>> villainPositions_;
    std::unordered_map<std::pair<int, int>, std::string, pair_hash> villainSymbols_;
    Blackboard* blackboard_;
};

#endif // MAP_H
