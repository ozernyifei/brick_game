// src/brick_game/tetris/tetris.c

#include "tetris.h"
#include "game_logic.h"
#include <stdlib.h>
#include <string.h>

// Initialize the game instance
static Game_t game;

void initTetris() {
    initGame(&game);
}

void userInput(UserAction_t action, bool hold) {
    (void)hold;  
    handleInput(&game, action);
}

GameInfo_t updateCurrentState() {
    updateGame(&game);

    GameInfo_t info;
    
    // Allocate and populate the field matrix
    info.field = malloc(sizeof(int*) * FIELD_HEIGHT);
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        info.field[i] = malloc(sizeof(int) * FIELD_WIDTH);
        memcpy(info.field[i], game.field[i], sizeof(int) * FIELD_WIDTH);
    }

    // Add current piece to the field for rendering
    for (int i = 0; i < PIECE_SIZE; ++i) {
        int x = game.current_piece.blocks[i].x + game.current_piece.x;
        int y = game.current_piece.blocks[i].y + game.current_piece.y;
        if (x >= 0 && x < FIELD_WIDTH && y >= 0 && y < FIELD_HEIGHT) {
            info.field[y][x] = 1;
        }
    }

    // Populate the next piece matrix
    info.next = malloc(sizeof(int*) * 4);
    for (int i = 0; i < 4; ++i) {
        info.next[i] = calloc(4, sizeof(int));
    }
    for (int i = 0; i < PIECE_SIZE; ++i) {
        int x = game.next_piece.blocks[i].x;
        int y = game.next_piece.blocks[i].y;
        if (x >= 0 && x < 4 && y >= 0 && y < 4) {
            info.next[y][x] = 1;
        }
    }

    // Populate other fields
    info.score = game.score;
    info.high_score = game.high_score;
    info.level = game.level;
    info.speed = game.speed;
    info.pause = game.pause;

    return info;  // Ensure 'info' is returned
}