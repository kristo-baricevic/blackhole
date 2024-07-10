#include "NcursesUtils.h"

void initializeNcurses() {
    initscr();            // Start ncurses mode
    cbreak();             // Line buffering disabled
    keypad(stdscr, TRUE); // Enable function keys and arrow keys
    noecho();             // Don't echo while we do getch
    curs_set(0);          // Hide the cursor
}

void endNcurses() {
    endwin(); // End ncurses mode
}

void clearAndRedrawWindow(WINDOW* win) {
    werase(win);        // Clear the window
    box(win, 0, 0);     // Redraw the border
    wrefresh(win);      // Refresh the window to show changes
}
