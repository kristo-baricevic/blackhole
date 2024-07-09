#include "Graphics.h"
#include <iostream>
#include <ncurses.h>

#include <ncurses.h>
#include <fstream>
#include <string>


void displayFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
      mvprintw(0, 0, ("Failed to open " + filename + " file!").c_str());
      refresh();
      return;
    }

    std::string line;
    int row = 0;
    while (getline(file, line)) {
      mvprintw(row++, 0, "%s", line.c_str());
    }

    file.close();
    refresh();
}


void displayVillain() {
  displayFile("villain.txt");
}

void displayLargeAstronaut() {
  displayFile("astronaut.txt");
}

void displayMenu() {
  clear();
  mvprintw(0, 0, "Choose an action:\n");
  mvprintw(1, 0, "1. Explore the black hole\n");
  mvprintw(2, 0, "2. Gather resources\n");
  mvprintw(3, 0, "3. Engage an enemy\n");
  mvprintw(4, 0, "4. Flee from an enemy\n");
  mvprintw(5, 0, "5. Exit\n");
  mvprintw(6, 0, "Enter your choice: ");
  refresh();
}


void displayCharacter() {
  displayFile("character.txt");
}


void displayBlackhole() {
  displayFile("blackhole1.txt");
}

void displayBlackhole2() {
  displayFile("blackhole2.txt");
}

void displayBlackhole3() {
  displayFile("blackhole3.txt");
}

void displayAstronaut() {
  std::cout << '@';
}

void displayOuterSpace() {
  std::cout << '.';
}
