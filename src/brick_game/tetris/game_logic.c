// src/brick_game/tetris/game_logic.c

#include "game_logic.h"
#include "pieces.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>  // For gettimeofday




void initGame(Game_t* game) {
    memset(game->field, 0, sizeof(game->field));
    game->state = STATE_START;
    game->score = 0;
    game->level = 1;
    game->lines_cleared = 0;
    game->speed = 1000;  // Initial speed in milliseconds
    game->pause = 0;  // 0: Running, 1: Paused, 2: Game Over
    game->last_move_time = getCurrentTime();
    srand(time(NULL));
    game->current_piece = createPiece(getRandomNumber(0, NUM_PIECES - 1));
    game->next_piece = createPiece(getRandomNumber(0, NUM_PIECES - 1));
}

void updateGame(Game_t* game) {
    if (game->score == 1000) {
        game->state = STATE_GAME_OVER;
        saveHighScore(game->high_score);
        game->pause = 2;
    }
    if (game->pause != 0 || game->state == STATE_GAME_OVER) {
        return;
    }

    unsigned long current_time = getCurrentTime();
    if (current_time - game->last_move_time >= game->speed) {
        // Time to move the piece down
        if (!moveCurrentPiece(game, 0, 1)) {
            // Piece can't move down; lock it
            lockPiece(game);
            clearLines(game);

            // Check for game over
            if (checkCollision(game, &game->current_piece)) {
                game->state = STATE_GAME_OVER;
                saveHighScore(game->high_score);
                game->pause = 2;  // Indicate game over
            }

            spawnPiece(game);

            
        }
        game->last_move_time = current_time;
    }
}

void handleInput(Game_t* game, UserAction_t action) {
    if (game->state == STATE_GAME_OVER) {
        if (action == Start) {
            initGame(game);
        }
        return;
    }

    if (action == Pause) {
        game->pause = (game->pause == 0) ? 1 : 0;
        return;
    }

    if (game->pause != 0) {
        return;
    }

    switch (action) {
        case Left:
            moveCurrentPiece(game, -1, 0);
            break;
        case Right:
            moveCurrentPiece(game, 1, 0);
            break;
        case Down:
            if (!moveCurrentPiece(game, 0, 1)) {
                // Piece can't move down; lock it
                lockPiece(game);
                clearLines(game);
                spawnPiece(game);

                // Check for game over
                if (checkCollision(game, &game->current_piece) || game->score == 1000) {
                    game->state = STATE_GAME_OVER;
                    saveHighScore(game->high_score);
                    game->pause = 2;  // Indicate game over
                }
            }
            // Reset last move time to prevent immediate automatic move
            game->last_move_time = getCurrentTime();
            break;
        case Action:
            rotateCurrentPiece(game, true);
            break;
        case Start:
            initGame(game);
            break;
        default:
            break;
    }
}

GameInfo_t getGameInfo(Game_t* game) {
    GameInfo_t info;
    
    // Allocate and populate the field matrix
    info.field = malloc(sizeof(int*) * FIELD_HEIGHT);
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        info.field[i] = malloc(sizeof(int) * FIELD_WIDTH);
        memcpy(info.field[i], game->field[i], sizeof(int) * FIELD_WIDTH);
    }

    // Add current piece to the field for rendering
    for (int i = 0; i < PIECE_SIZE; ++i) {
        int x = game->current_piece.blocks[i].x + game->current_piece.x;
        int y = game->current_piece.blocks[i].y + game->current_piece.y;
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
        int x = game->next_piece.blocks[i].x;
        int y = game->next_piece.blocks[i].y;
        if (x >= 0 && x < 4 && y >= 0 && y < 4) {
            info.next[y][x] = 1;
        }
    }

    // Populate other fields
    info.score = game->score;
    info.high_score = game->high_score;
    info.level = game->level;
    info.speed = game->speed;
    info.pause = game->pause;

    return info;
}

void spawnPiece(Game_t* game) {
    game->current_piece = game->next_piece;
    game->current_piece.x = FIELD_WIDTH / 2 - 2;
    game->current_piece.y = 0; // Starting y position within the field

    // Generate a new next piece
    game->next_piece = createPiece(getRandomNumber(0, NUM_PIECES - 1));
}

bool moveCurrentPiece(Game_t* game, int dx, int dy) {
    Piece_t moved_piece = game->current_piece;
    moved_piece.x += dx;
    moved_piece.y += dy;
    if (!checkCollision(game, &moved_piece)) {
        game->current_piece = moved_piece;
        return true;
    }
    return false;
}

bool rotateCurrentPiece(Game_t* game, bool clockwise) {
    Piece_t rotated_piece = game->current_piece;
    rotatePiece(&rotated_piece, clockwise);

    // Try rotation without offset
    if (!checkCollision(game, &rotated_piece)) {
        game->current_piece = rotated_piece;
        return true;
    }

    // Try shifting left
    rotated_piece.x -= 1;
    if (!checkCollision(game, &rotated_piece)) {
        game->current_piece = rotated_piece;
        return true;
    }

    // Try shifting right
    rotated_piece.x += 2; // Since we shifted left before
    if (!checkCollision(game, &rotated_piece)) {
        game->current_piece = rotated_piece;
        return true;
    }

    // Rotation not possible
    return false;
}

void lockPiece(Game_t* game) {
    for (int i = 0; i < PIECE_SIZE; ++i) {
        int x = game->current_piece.blocks[i].x + game->current_piece.x;
        int y = game->current_piece.blocks[i].y + game->current_piece.y;
        if (y >= 0 && y < FIELD_HEIGHT && x >= 0 && x < FIELD_WIDTH) {
            game->field[y][x] = 1;
        }
    }
}

void clearLines(Game_t* game) {
    int lines = 0;
    for (int y = 0; y < FIELD_HEIGHT; ++y) {
        bool full_line = true;
        for (int x = 0; x < FIELD_WIDTH; ++x) {
            if (game->field[y][x] == 0) {
                full_line = false;
                break;
            }
        }
        if (full_line) {
            // Move all lines above down
            for (int ty = y; ty > 0; --ty) {
                memcpy(game->field[ty], game->field[ty - 1], sizeof(game->field[0]));
            }
            memset(game->field[0], 0, sizeof(game->field[0]));
            lines++;
        }
    }

    if (lines > 0) {
        game->lines_cleared += lines;
        switch (lines) {
            case 1:
                game->score += 100;
                break;
            case 2:
                game->score += 300;
                break;
            case 3:
                game->score += 700;
                break;
            case 4:
                game->score += 1500;
                break;
            default:
                break;
        }
        // Update high score
        if (game->score > game->high_score) {
            game->high_score = game->score;
        }
        // Level up every 600 points
        int new_level = game->score / 600 + 1;
        if (new_level > game->level && game->level < 10) {
            game->level = new_level;
            game->speed = game->speed * 9 / 10;  // Increase speed by 10%
        }
    }
}

bool checkCollision(Game_t* game, Piece_t* piece) {
    for (int i = 0; i < PIECE_SIZE; ++i) {
        int x = piece->blocks[i].x + piece->x;
        int y = piece->blocks[i].y + piece->y;
        if (x < 0 || x >= FIELD_WIDTH || y >= FIELD_HEIGHT) {
            return true;
        }
        if (y >= 0 && game->field[y][x]) {
            return true;
        }
    }
    return false;
}
