#ifndef S21_FSM_CONTROLLER_H_
#define S21_FSM_CONTROLLER_H_

#include "snake.h"          // For Snake class
#include "apple.h"          // For Apple class
#include "game_field.h"     // For GameField class

namespace s21 {

// Enum for different states in the game
enum class GameState {
    IDLE,
    MOVING,
    EATING,
    GAME_OVER
};

class FSMController {
public:
    // Constructor and Destructor
    FSMController(Snake *snake, Apple *apple, GameField *field);
    ~FSMController() = default;

    // State management
    void Update();            // Updates the state based on game logic
    void ChangeState(GameState new_state); // Manually change the state (if needed)

    // Getters
    GameState GetCurrentState() const; // Returns the current state

private:
    // Private methods
    void HandleIdleState();    // Logic for the Idle state
    void HandleMovingState();  // Logic for the Moving state
    void HandleEatingState();  // Logic for the Eating state
    void HandleGameOverState();// Logic for the Game Over state

    // Data members
    Snake *snake_;             // Pointer to the Snake object
    Apple *apple_;             // Pointer to the Apple object
    GameField *field_;         // Pointer to the GameField object
    GameState current_state_;  // Current state of the game
};

}  // namespace s21

#endif  // S21_FSM_CONTROLLER_H_
