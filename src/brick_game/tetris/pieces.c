#include "pieces.h"
#include <string.h>

// Definitions of the block positions for each piece type and rotation.
// Each piece has four possible rotations (0 to 3).

// The block definitions are arrays of 4 blocks for each rotation.

static const Point_t I_PIECE_SHAPES[4][PIECE_SIZE] = {
    // Rotation 0
    {{0, 1}, {1, 1}, {2, 1}, {3, 1}},
    // Rotation 1
    {{2, 0}, {2, 1}, {2, 2}, {2, 3}},
    // Rotation 2
    {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
    // Rotation 3
    {{1, 0}, {1, 1}, {1, 2}, {1, 3}}
};

// J_PIECE shapes
static const Point_t J_PIECE_SHAPES[4][PIECE_SIZE] = {
    // Rotation 0
    {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
    // Rotation 1
    {{1, 0}, {2, 0}, {1, 1}, {1, 2}},
    // Rotation 2
    {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
    // Rotation 3
    {{1, 0}, {1, 1}, {1, 2}, {0, 2}}
};

// L_PIECE shapes
static const Point_t L_PIECE_SHAPES[4][PIECE_SIZE] = {
    // Rotation 0
    {{2, 0}, {0, 1}, {1, 1}, {2, 1}},
    // Rotation 1
    {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
    // Rotation 2
    {{0, 1}, {1, 1}, {2, 1}, {0, 2}},
    // Rotation 3
    {{0, 0}, {1, 0}, {1, 1}, {1, 2}}
};

// O_PIECE shapes (only one rotation needed)
static const Point_t O_PIECE_SHAPES[1][PIECE_SIZE] = {
    {{1, 0}, {2, 0}, {1, 1}, {2, 1}}
};

// S_PIECE shapes
static const Point_t S_PIECE_SHAPES[2][PIECE_SIZE] = {
    // Rotation 0
    {{1, 1}, {2, 1}, {0, 2}, {1, 2}},
    // Rotation 1
    {{1, 0}, {1, 1}, {2, 1}, {2, 2}}
};

// T_PIECE shapes
static const Point_t T_PIECE_SHAPES[4][PIECE_SIZE] = {
    // Rotation 0
    {{1, 0}, {0, 1}, {1, 1}, {2, 1}},
    // Rotation 1
    {{1, 0}, {1, 1}, {2, 1}, {1, 2}},
    // Rotation 2
    {{0, 1}, {1, 1}, {2, 1}, {1, 2}},
    // Rotation 3
    {{1, 0}, {0, 1}, {1, 1}, {1, 2}}
};

// Z_PIECE shapes
static const Point_t Z_PIECE_SHAPES[2][PIECE_SIZE] = {
    // Rotation 0
    {{0, 1}, {1, 1}, {1, 2}, {2, 2}},
    // Rotation 1
    {{2, 0}, {1, 1}, {2, 1}, {1, 2}}
};


// Similar definitions for other pieces...

static const Point_t* PIECE_SHAPES[NUM_PIECES][4] = {
    // I_PIECE
    {
        I_PIECE_SHAPES[0],
        I_PIECE_SHAPES[1],
        I_PIECE_SHAPES[2],
        I_PIECE_SHAPES[3]
    },
    // J_PIECE
    {
        J_PIECE_SHAPES[0],
        J_PIECE_SHAPES[1],
        J_PIECE_SHAPES[2],
        J_PIECE_SHAPES[3]
    },
    // L_PIECE
    {
        L_PIECE_SHAPES[0],
        L_PIECE_SHAPES[1],
        L_PIECE_SHAPES[2],
        L_PIECE_SHAPES[3]
    },
    // O_PIECE
    {
        O_PIECE_SHAPES[0],
        O_PIECE_SHAPES[0],  // Duplicate because O_PIECE has only one rotation
        O_PIECE_SHAPES[0],
        O_PIECE_SHAPES[0]
    },
    // S_PIECE
    {
        S_PIECE_SHAPES[0],
        S_PIECE_SHAPES[1],
        S_PIECE_SHAPES[0],  // Duplicate rotations
        S_PIECE_SHAPES[1]
    },
    // T_PIECE
    {
        T_PIECE_SHAPES[0],
        T_PIECE_SHAPES[1],
        T_PIECE_SHAPES[2],
        T_PIECE_SHAPES[3]
    },
    // Z_PIECE
    {
        Z_PIECE_SHAPES[0],
        Z_PIECE_SHAPES[1],
        Z_PIECE_SHAPES[0],  // Duplicate rotations
        Z_PIECE_SHAPES[1]
    }
};


Piece_t createPiece(PieceType_t type) {
    Piece_t piece;
    piece.type = type;
    piece.rotation = 0;
    piece.x = 3;  // Starting x position
    piece.y = 0; // Starting y position (off the top of the board)
    memcpy(piece.blocks, PIECE_SHAPES[type][0], sizeof(Point_t) * PIECE_SIZE);
    return piece;
}

void rotatePiece(Piece_t* piece, bool clockwise) {
    piece->rotation = (piece->rotation + (clockwise ? 1 : 3)) % 4;
    memcpy(piece->blocks, PIECE_SHAPES[piece->type][piece->rotation], sizeof(Point_t) * PIECE_SIZE);
}

void movePiece(Piece_t* piece, int dx, int dy) {
    piece->x += dx;
    piece->y += dy;
}
