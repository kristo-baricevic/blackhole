#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

class Map {
public:
    Map(int width, int height);
    void display() const;
    bool moveAstronaut(const std::string& direction);
    void placeCharacter(int x, int y, char symbol);

    void setAstronautSymbol(char symbol);
    void setOuterSpaceSymbol(char symbol);

private:
    int width_;
    int height_;
    std::vector<std::vector<char>> grid_;
    int astronautX_;
    int astronautY_;
    char astronautSymbol_;
    char outerSpaceSymbol_;
};

#endif // MAP_H
