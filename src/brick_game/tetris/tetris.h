#ifndef TETRIS_H_
#define TETRIS_H_

#include <stdbool.h>
#include "specification.h"

/**
 * @brief Initializes the Tetris game library.
 */
void initTetris();

/**
 * @brief Processes user input.
 *
 * @param action The user action to handle.
 * @param hold Whether the button is being held down.
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Updates and retrieves the current game state.
 *
 * @return A GameInfo_t structure with the current game state.
 */
GameInfo_t updateCurrentState();

/**
 * @brief Cleans up resources used by the Tetris game library.
 */

#endif  // TETRIS_H_
