// gui/cli/render.c

#include "render.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

static WINDOW* gameWin;
static WINDOW* infoWin;

void initRender() {
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();
    use_default_colors();

    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_YELLOW, -1);
    init_pair(4, COLOR_BLUE, -1);
    init_pair(5, COLOR_MAGENTA, -1);
    init_pair(6, COLOR_CYAN, -1);
    init_pair(7, COLOR_WHITE, -1);

    gameWin = newwin(FIELD_HEIGHT + 2, FIELD_WIDTH * 2 + 2, 0, 0);  
    infoWin = newwin(FIELD_HEIGHT + 2, 20, 0, FIELD_WIDTH * 2 + 3); 

    box(gameWin, 0, 0);
    box(infoWin, 0, 0);

    wrefresh(gameWin);
    wrefresh(infoWin);
}

void renderGame(GameInfo_t* gameInfo) {
    werase(gameWin);
    box(gameWin, 0, 0);

    for (int y = 0; y < FIELD_HEIGHT; ++y) {
        for (int x = 0; x < FIELD_WIDTH; ++x) {
            if (gameInfo->field[y][x]) {
                wattron(gameWin, COLOR_PAIR(1));
                mvwprintw(gameWin, y + 1, x * 2 + 1, "[]");
                wattroff(gameWin, COLOR_PAIR(1));
            }
        }
    }

    for (int y = 2; y < 6; ++y) {
        for (int x = 1; x < 9; ++x) {
            mvwprintw(infoWin, y, x, "  ");
        }
    }

    mvwprintw(infoWin, 1, 1, "Next:");
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (gameInfo->next[y][x]) {
                wattron(infoWin, COLOR_PAIR(2));
                mvwprintw(infoWin, y + 2, x * 2 + 1, "[]");
                wattroff(infoWin, COLOR_PAIR(2));
            }
        }
    }

    mvwprintw(infoWin, 7, 1, "Score: %d", gameInfo->score);
    mvwprintw(infoWin, 8, 1, "High: %d", gameInfo->high_score);
    mvwprintw(infoWin, 9, 1, "Level: %d", gameInfo->level);

    if (gameInfo->pause == 1) {
        wattron(gameWin, A_BOLD);
        mvwprintw(gameWin, FIELD_HEIGHT / 2, (FIELD_WIDTH * 2 + 2) / 2 - 4, "PAUSED");
        wattroff(gameWin, A_BOLD);
    } else if (gameInfo->pause == 2) {
        wattron(gameWin, A_BOLD | COLOR_PAIR(1));
        mvwprintw(gameWin, FIELD_HEIGHT / 2, (FIELD_WIDTH * 2 + 2) / 2 - 5, "GAME OVER");
        wattroff(gameWin, A_BOLD | COLOR_PAIR(1));
    }

    wrefresh(gameWin);
    wrefresh(infoWin);

    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        free(gameInfo->field[i]);
    }
    free(gameInfo->field);

    for (int i = 0; i < 4; ++i) {
        free(gameInfo->next[i]);
    }
    free(gameInfo->next);
}

void cleanupRender() {
    delwin(gameWin);
    delwin(infoWin);
    endwin();
}
