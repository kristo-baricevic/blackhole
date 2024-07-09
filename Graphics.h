#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <ncurses.h>

void displayFile(WINDOW* win, const std::string& filename);
void displayLogo(WINDOW* win);
void displayVillain(WINDOW* win);
void displayMenu(WINDOW* win);

void displayBlackhole(WINDOW* win);
void displayBlackhole2(WINDOW* win);
void displayBlackhole3(WINDOW* win);

void displayCharacter(WINDOW* win);

void displayLargeAstronaut(WINDOW* win);

void displayAstronaut();
void displayOuterSpace();

#endif // GRAPHICS_H
