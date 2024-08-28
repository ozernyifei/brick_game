#ifndef S21_SNAKE_H_
#define S21_SNAKE_H_

#include <vector>  // For storing the snake's body segments
#include <utility> // For std::pair

namespace s21 {

// Enum for the direction of the snake
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// Represents a single segment of the snake's body
using Segment = std::pair<int, int>;

class Snake {
public:
    // Constructor and Destructor
    Snake(int initial_length, int field_width, int field_height);
    ~Snake() = default;

    // Movement and Update
    void Move(); // Moves the snake one step in the current direction
    void ChangeDirection(Direction new_direction); // Changes the direction of the snake

    // Collision Detection
    bool CheckCollisionWithSelf() const; // Checks if the snake has collided with itself
    bool CheckCollisionWithWalls() const; // Checks if the snake has collided with the walls

    // Growth
    void Grow(); // Increases the length of the snake

    // Getters
    const std::vector<Segment>& GetBody() const; // Returns the snake's body segments
    Direction GetDirection() const; // Returns the current direction of the snake

private:
    // Private methods
    bool IsOppositeDirection(Direction new_direction) const; // Checks if the new direction is opposite to current

    // Data members
    std::vector<Segment> body_; // Stores the segments of the snake's body
    Direction direction_;       // Current direction of movement
    int field_width_;           // Width of the game field
    int field_height_;          // Height of the game field
    bool grow_;                 // Indicates whether the snake should grow after the next move
};

}  // namespace s21

#endif  // S21_SNAKE_H_
