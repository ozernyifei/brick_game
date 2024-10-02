#ifndef TETRIS_GAME_LOGIC_H_
#define TETRIS_GAME_LOGIC_H_

#include <stdbool.h>
#include "pieces.h"
#include "specification.h"

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

typedef enum {
    STATE_START,
    STATE_SPAWN,
    STATE_MOVING,
    STATE_MOVE,
    STATE_ATTACHING,
    STATE_GAME_OVER
} GameState_t;

typedef struct {
    int field[FIELD_HEIGHT][FIELD_WIDTH];
    Piece_t current_piece;
    Piece_t next_piece;
    GameState_t state;
    int score;
    int high_score;
    int level;
    int lines_cleared;
    int speed;
    int pause;
    unsigned long last_move_time;
} Game_t;

/**
 * @brief Initializes the game state.
 *
 * @param game Pointer to the Game_t structure.
 */
void initGame(Game_t* game);

/**
 * @brief Updates the game state based on the FSM.
 *
 * @param game Pointer to the Game_t structure.
 */
void updateGame(Game_t* game);

/**
 * @brief Handles user input actions.
 *
 * @param game Pointer to the Game_t structure.
 * @param action The user action to handle.
 */
void handleInput(Game_t* game, UserAction_t action);

/**
 * @brief Gets the current game information for rendering.
 *
 * @param game Pointer to the Game_t structure.
 * @return A GameInfo_t structure with the current game state.
 */
GameInfo_t getGameInfo(Game_t* game);

/**
 * @brief Moves current piece to another position.
 *
 * @param game Pointer to the Game_t structure.
 * @param dx X coordinate of piece.
 * @param dy Y coordinate of piece.
 * @return A bool value that tells if the piece has moved.
 */
bool moveCurrentPiece(Game_t* game, int dx, int dy);

/**
 * @brief Cleans the lines on the field.
 *
 * @param game Pointer to the Game_t structure.
 */
void clearLines(Game_t* game);

/**
 * @brief Spawns a piece on the field.
 *
 * @param game Pointer to the Game_t structure.
 */
void spawnPiece(Game_t* game);

/**
 * @brief Rotates current piece.
 *
 * @param game Pointer to the Game_t structure.
 * @param clockwise A bool value indicating whether the figure is spinning clockwise.
 * @return A bool value that tells if the piece has been rotated.
 */
bool rotateCurrentPiece(Game_t* game, bool clockwise);

/**
 * @brief Locks a piece on the field.
 *
 * @param game Pointer to the Game_t structure.
 */
void lockPiece(Game_t* game);



/**
 * @brief Checks whether the shape collides with walls or other shapes.
 *
 * @param game Pointer to the Game_t structure.
 * @param game Pointer to the Piece_t structure. 
 */
bool checkCollision(Game_t* game, Piece_t* piece);

#endif  // TETRIS_GAME_LOGIC_H_
