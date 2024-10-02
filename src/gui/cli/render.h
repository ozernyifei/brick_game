#ifndef RENDER_H_
#define RENDER_H_
#include "../../brick_game/tetris/game_logic.h"
#include "specification.h"

/**
 * @brief Initializes the rendering system.
 */
void initRender();

/**
 * @brief Renders the game state to the screen.
 *
 * @param gameInfo Pointer to the current game state information.
 */
void renderGame(GameInfo_t* gameInfo);

/**
 * @brief Cleans up the rendering system.
 */
void cleanupRender();

#endif  // RENDER_H_
