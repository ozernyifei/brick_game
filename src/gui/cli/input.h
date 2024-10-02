#ifndef INPUT_H_
#define INPUT_H_

#include "specification.h"

/**
 * @brief Initializes the input system.
 */
void initInput();

/**
 * @brief Gets the user input and maps it to a UserAction_t.
 *
 * @return The UserAction_t corresponding to the user's input.
 */
UserAction_t getUserInput();

/**
 * @brief Cleans up the input system.
 */

#endif  // INPUT_H_
