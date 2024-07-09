#ifndef NCURSES_UTILS_H
#define NCURSES_UTILS_H

#include <locale.h>
#include <ncurses.h>

void initializeNcurses() {
    setlocale(LC_ALL, "");  // Set locale to default environment setting
    initscr();              // Start ncurses mode
    cbreak();               // Line buffering disabled
    keypad(stdscr, TRUE);   // Enable function keys and arrow keys
    noecho();               // Don't echo while we do getch
    curs_set(0);            // Hide the cursor
}

void endNcurses() {
    endwin(); // End ncurses mode
}

#endif // NCURSES_UTILS_H
