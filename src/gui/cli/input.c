#include "input.h"
#include <ncurses.h>
#include <unistd.h>

void initInput() {
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

UserAction_t getUserInput() {
    int ch = getch();

    switch (ch) {
        case 'q':
            return Terminate;
        case 'p':
            return Pause;
        case KEY_LEFT:
            return Left;
        case KEY_RIGHT:
            return Right;
        case KEY_DOWN:
            return Down;
        case KEY_UP:
            return Action;
        case ' ':
            return Action;
        case 's':
            return Start;
        default:
            return -1;  // No action
    }
}

