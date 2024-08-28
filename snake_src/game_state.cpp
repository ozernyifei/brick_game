#include "game_state.h"
#include <iostream>

namespace s21 {

// Constructor to initialize the game state
GameStateManager::GameStateManager(int field_width, int field_height)
    : snake_(4, field_width, field_height), // Initialize snake
      game_field_(field_width, field_height), // Initialize game field
      apple_(field_width, field_height), // Initialize apple
      state_(GameState::RUNNING), // Set initial state
      score_(0), // Initialize score
      level_(1) { // Initialize level
    apple_.PlaceApple(); // Place initial apple
}

// Method to update the game state
void GameStateManager::Update() {
    if (state_ == GameState::RUNNING) {
        snake_.Move(); // Move the snake
        CheckCollisions(); // Check for collisions
        if (game_field_.IsAppleEaten(snake_)) {
            snake_.Grow(); // Grow the snake
            apple_.PlaceApple(); // Place a new apple
            UpdateScore(); // Update the score
            IncreaseLevel(); // Increase the level
        }
    }
}

// Method to process user input
void GameStateManager::ProcessInput(char input) {
    switch (input) {
        case 'w': snake_.ChangeDirection(Direction::UP); break;
        case 's': snake_.ChangeDirection(Direction::DOWN); break;
        case 'a': snake_.ChangeDirection(Direction::LEFT); break;
        case 'd': snake_.ChangeDirection(Direction::RIGHT); break;
        default: break;
    }
}

// Method to reset the game state
void GameStateManager::Reset() {
    snake_ = Snake(4, game_field_.GetWidth(), game_field_.GetHeight()); // Reset snake
    apple_.PlaceApple(); // Place a new apple
    state_ = GameState::RUNNING; // Set state to running
    score_ = 0; // Reset score
    level_ = 1; // Reset level
}

// Method to get the current game state
GameState GameStateManager::GetState() const {
    return state_;
}

// Method to get the snake object
const Snake& GameStateManager::GetSnake() const {
    return snake_;
}

// Method to get the game field object
const GameField& GameStateManager::GetGameField() const {
    return game_field_;
}

// Method to get the apple object
const Apple& GameStateManager::GetApple() const {
    return apple_;
}

// Method to check for collisions
void GameStateManager::CheckCollisions() {
    if (snake_.CheckCollisionWithWalls() || snake_.CheckCollisionWithSelf()) {
        state_ = GameState::GAME_OVER; // Set state to game over
    } else if (score_ >= 200) { // Example winning condition
        state_ = GameState::WIN; // Set state to win
    }
}

// Method to update the score
void GameStateManager::UpdateScore() {
    score_ += 1; // Increment score
}

// Method to increase the level
void GameStateManager::IncreaseLevel() {
    if (score_ / 5 > level_) {
        level_ = score_ / 5; // Update level based on score
        // Adjust snake speed here if needed
    }
}

}  // namespace s21
