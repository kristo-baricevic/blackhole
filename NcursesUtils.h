#ifndef NCURSES_UTILS_H
#define NCURSES_UTILS_H

#include <ncurses.h>

void initializeNcurses();
void endNcurses();
void clearAndRedrawWindow(WINDOW* win);

#endif // NCURSES_UTILS_H
