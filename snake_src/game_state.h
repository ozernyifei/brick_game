#ifndef S21_GAME_STATE_H_
#define S21_GAME_STATE_H_

#include "snake.h"
#include "game_field.h"
#include "apple.h"

namespace s21 {

// Enum for the state of the game
enum class GameState {
    RUNNING,
    GAME_OVER,
    WIN
};

// Manages the state of the game
class GameStateManager {
public:
    // Constructor and Destructor
    GameStateManager(int field_width, int field_height);
    ~GameStateManager() = default;

    // Game management
    void Update(); // Updates the game state
    void ProcessInput(char input); // Processes user input
    void Reset(); // Resets the game to the initial state

    // Getters
    GameState GetState() const; // Returns the current game state
    const Snake& GetSnake() const; // Returns the snake object
    const GameField& GetGameField() const; // Returns the game field object
    const Apple& GetApple() const; // Returns the apple object

private:
    // Data members
    Snake snake_; // Snake object
    GameField game_field_; // Game field object
    Apple apple_; // Apple object
    GameState state_; // Current game state
    int score_; // Current score
    int level_; // Current level

    // Private methods
    void CheckCollisions(); // Checks for collisions
    void UpdateScore(); // Updates the score
    void IncreaseLevel(); // Increases the level
};

}  // namespace s21

#endif  // S21_GAME_STATE_H_
