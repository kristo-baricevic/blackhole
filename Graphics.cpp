#include "Graphics.h"
#include <ncurses.h>
#include <fstream>
#include <string>

void displayFile(WINDOW* win, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        mvwprintw(win, 1, 1, ("Failed to open " + filename + " file!").c_str());
        wrefresh(win);
        return;
    }

    std::string line;
    int row = 1;  // Start displaying from row 1 to avoid border
    int maxRows, maxCols;
    getmaxyx(win, maxRows, maxCols);

    while (getline(file, line)) {
        if (row >= maxRows - 1) {  // Ensure we do not write over the border
            break;
        }
        mvwprintw(win, row++, 1, "%.*s", maxCols - 2, line.c_str());  // Ensure we do not write over the border
    }

    file.close();
    wrefresh(win);
}



void displayLogo(WINDOW* win) {
    displayFile(win, "logo.txt");
}

void displayVillain(WINDOW* win) {
    displayFile(win, "villian.txt");
}

void displayMenu(WINDOW* win) {
    mvwprintw(win, 0, 0, "1. Explore the black hole");
    mvwprintw(win, 1, 0, "2. Gather resources");
    mvwprintw(win, 2, 0, "3. Engage an enemy");
    mvwprintw(win, 3, 0, "4. Flee from an enemy");
    mvwprintw(win, 4, 0, "5. Exit");
    mvwprintw(win, 5, 0, "Enter your choice: ");
    wrefresh(win);
}

void displayBlackhole(WINDOW* win) {
    displayFile(win, "blackhole.txt");
}

void displayBlackhole2(WINDOW* win) {
    displayFile(win, "blackhole2.txt");
}

void displayBlackhole3(WINDOW* win) {
    displayFile(win, "blackhole3.txt");
}

void displayCharacter(WINDOW* win) {
    displayFile(win, "character.txt");
}

void displayLargeAstronaut(WINDOW* win) {
    displayFile(win, "large_astronaut.txt");
}

void displayAstronaut() {
    // Implementation for displaying the astronaut in ncurses
}

void displayOuterSpace() {
    // Implementation for displaying outer space in ncurses
}
