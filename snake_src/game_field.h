#ifndef S21_GAME_FIELD_H_
#define S21_GAME_FIELD_H_

#include "snake.h"  // Include Snake for interaction with the game field

namespace s21 {

// GameField class manages the game area and apple placement
class GameField {
public:
    // Constructor and Destructor
    GameField(int width, int height);
    ~GameField() = default;

    // Apple management
    void PlaceApple(); // Places an apple at a random position on the field
    const Segment& GetApplePosition() const; // Returns the position of the apple

    // Collision check
    bool IsAppleEaten(const Snake& snake) const; // Checks if the snake has eaten the apple

    // Getters
    int GetWidth() const;  // Returns the width of the game field
    int GetHeight() const; // Returns the height of the game field

private:
    // Data members
    int width_;            // Width of the game field
    int height_;           // Height of the game field
    Segment apple_position_; // Position of the current apple

    // Private methods
    bool IsPositionOccupied(const Segment& position, const Snake& snake) const; // Checks if a position is occupied by the snake
};

}  // namespace s21

#endif  // S21_GAME_FIELD_H_
