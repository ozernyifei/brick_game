#include "game_field.h"
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time() to seed the random number generator
#include <algorithm>
namespace s21 {

// Constructor to initialize the game field
GameField::GameField(int width, int height)
    : width_(width), height_(height) {
    std::srand(std::time(nullptr));  // Seed the random number generator
    PlaceApple();  // Place the first apple
}

// Method to place an apple at a random position on the field
void GameField::PlaceApple() {
    int x, y;
    do {
        x = std::rand() % width_;
        y = std::rand() % height_;
        apple_position_ = std::make_pair(x, y);
    } while (IsPositionOccupied(apple_position_, Snake(0, width_, height_)));  // Ensure apple doesn't spawn on the snake
}

// Method to get the position of the apple
const Segment& GameField::GetApplePosition() const {
    return apple_position_;
}

// Method to check if the snake has eaten the apple
bool GameField::IsAppleEaten(const Snake& snake) const {
    return snake.GetBody().front() == apple_position_;
}

// Method to get the width of the game field
int GameField::GetWidth() const {
    return width_;
}

// Method to get the height of the game field
int GameField::GetHeight() const {
    return height_;
}

// Private method to check if a position is occupied by the snake
bool GameField::IsPositionOccupied(const Segment& position, const Snake& snake) const {
    const auto& body = snake.GetBody();
    return std::find(body.begin(), body.end(), position) != body.end();
}

}  // namespace s21
