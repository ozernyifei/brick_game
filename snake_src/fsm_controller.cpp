#include "fsm_controller.h"

namespace s21 {

// Constructor to initialize the FSM controller
FSMController::FSMController(Snake *snake, Apple *apple, GameField *field)
    : snake_(snake), apple_(apple), field_(field), current_state_(GameState::IDLE) {}

// Updates the state based on game logic
void FSMController::Update() {
    switch (current_state_) {
        case GameState::IDLE:
            HandleIdleState();
            break;
        case GameState::MOVING:
            HandleMovingState();
            break;
        case GameState::EATING:
            HandleEatingState();
            break;
        case GameState::GAME_OVER:
            HandleGameOverState();
            break;
    }
}

// Manually change the state (if needed)
void FSMController::ChangeState(GameState new_state) {
    current_state_ = new_state;
}

// Returns the current state
GameState FSMController::GetCurrentState() const {
    return current_state_;
}

// Logic for the Idle state
void FSMController::HandleIdleState() {
    // Typically, the Idle state would wait for a start signal or user input
    // For simplicity, let's transition to MOVING directly (or based on input)
    ChangeState(GameState::MOVING);
}

// Logic for the Moving state
void FSMController::HandleMovingState() {
    snake_->Move();

    // Check if the snake has eaten the apple
    if (field_->IsAppleEaten(*snake_)) {
        ChangeState(GameState::EATING);
    }
    // Check for collisions with walls or itself
    else if (snake_->CheckCollisionWithWalls() || snake_->CheckCollisionWithSelf()) {
        ChangeState(GameState::GAME_OVER);
    }
}

// Logic for the Eating state
void FSMController::HandleEatingState() {
    snake_->Grow();       // Grow the snake
    apple_->PlaceApple(); // Place a new apple
    ChangeState(GameState::MOVING); // Transition back to MOVING state
}

// Logic for the Game Over state
void FSMController::HandleGameOverState() {
    // In this state, you might display a game over screen or reset the game
    // For simplicity, let's transition to IDLE after game over
    ChangeState(GameState::IDLE);
}

}  // namespace s21
