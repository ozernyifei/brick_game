#include "apple.h"
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time() to seed the random number generator

namespace s21 {

// Constructor to initialize the apple with a field size
Apple::Apple(int field_width, int field_height)
    : field_width_(field_width), field_height_(field_height) {
    std::srand(std::time(nullptr));  // Seed the random number generator
    GenerateRandomPosition();  // Place the apple initially
}

// Method to place an apple at a random position on the field
void Apple::PlaceApple() {
    GenerateRandomPosition();
}

// Method to get the position of the apple
const std::pair<int, int>& Apple::GetPosition() const {
    return position_;
}

// Method to check if a given position is occupied by the apple
bool Apple::IsPositionOccupied(const std::pair<int, int>& position) const {
    return position == position_;
}

// Private method to generate a random position for the apple
void Apple::GenerateRandomPosition() {
    int x = std::rand() % field_width_;
    int y = std::rand() % field_height_;
    position_ = std::make_pair(x, y);
}

}  // namespace s21
