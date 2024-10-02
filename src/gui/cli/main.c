// gui/cli/main.c

#include "render.h"
#include "input.h"
#include "tetris.h"
#include <ncurses.h>
#include <unistd.h>  
#include <stdlib.h>  

#define FRAME_DELAY 50 

int main() {
    initTetris();
    initRender();
    initInput();

    bool running = true;
    while (running) {

        UserAction_t action = getUserInput();
        if (action == Terminate) {
            running = false;
        } else if ((int)action != -1) {  
            userInput(action, false);
        }

        GameInfo_t gameInfo = updateCurrentState();

        renderGame(&gameInfo);

        usleep(FRAME_DELAY * 1000);
    }

    cleanupRender();

    return 0;
}
