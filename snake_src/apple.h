#ifndef S21_APPLE_H_
#define S21_APPLE_H_

#include <utility> // For std::pair

namespace s21 {

// Represents a single apple in the game
class Apple {
public:
    // Constructor and Destructor
    Apple(int field_width, int field_height);
    ~Apple() = default;

    // Apple management
    void PlaceApple(); // Places an apple at a random position on the field
    const std::pair<int, int>& GetPosition() const; // Returns the position of the apple

    // Apple position check
    bool IsPositionOccupied(const std::pair<int, int>& position) const; // Checks if the apple position is occupied

private:
    // Data members
    int field_width_;          // Width of the game field
    int field_height_;         // Height of the game field
    std::pair<int, int> position_; // Position of the apple

    // Private methods
    void GenerateRandomPosition(); // Generates a random position for the apple
};

}  // namespace s21

#endif  // S21_APPLE_H_
