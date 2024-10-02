#ifndef TETRIS_PIECES_H_
#define TETRIS_PIECES_H_

#include <stdbool.h>

#define NUM_PIECES 7
#define PIECE_SIZE 4

typedef enum {
    I_PIECE,
    J_PIECE,
    L_PIECE,
    O_PIECE,
    S_PIECE,
    T_PIECE,
    Z_PIECE
} PieceType_t;

typedef struct {
    int x;
    int y;
} Point_t;

typedef struct {
    PieceType_t type;
    Point_t blocks[PIECE_SIZE];
    int rotation;
    int x;  // Position on the board
    int y;
} Piece_t;

/**
 * @brief Creates a new piece of the given type.
 *
 * @param type The type of the Tetris piece.
 * @return A new Piece_t object.
 */
Piece_t createPiece(PieceType_t type);

/**
 * @brief Rotates the piece 90 degrees.
 *
 * @param piece The piece to rotate.
 * @param clockwise Direction of rotation.
 */
void rotatePiece(Piece_t* piece, bool clockwise);

/**
 * @brief Moves the piece by dx and dy.
 *
 * @param piece The piece to move.
 * @param dx Change in x-direction.
 * @param dy Change in y-direction.
 */
void movePiece(Piece_t* piece, int dx, int dy);

#endif  // TETRIS_PIECES_H_
