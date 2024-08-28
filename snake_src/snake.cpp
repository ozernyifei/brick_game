#include "snake.h"

namespace s21 {

// Constructor to initialize the snake
Snake::Snake(int initial_length, int field_width, int field_height)
    : direction_(Direction::RIGHT),  // Default direction is right
      field_width_(field_width),
      field_height_(field_height),
      grow_(false) {
    // Initialize the snake's body in the middle of the field
    int start_x = field_width_ / 2;
    int start_y = field_height_ / 2;

    for (int i = 0; i < initial_length; ++i) {
        body_.emplace_back(start_x - i, start_y);
    }
}

// Method to move the snake in the current direction
void Snake::Move() {
    // Determine the new head position
    Segment new_head = body_.front();
    switch (direction_) {
        case Direction::UP:
            new_head.second -= 1;
            break;
        case Direction::DOWN:
            new_head.second += 1;
            break;
        case Direction::LEFT:
            new_head.first -= 1;
            break;
        case Direction::RIGHT:
            new_head.first += 1;
            break;
    }

    // Insert the new head at the front of the body
    body_.insert(body_.begin(), new_head);

    // If not growing, remove the tail segment
    if (!grow_) {
        body_.pop_back();
    } else {
        grow_ = false;
    }
}

// Method to change the direction of the snake
void Snake::ChangeDirection(Direction new_direction) {
    // Prevent the snake from reversing into itself
    if (!IsOppositeDirection(new_direction)) {
        direction_ = new_direction;
    }
}

// Method to check if the snake has collided with itself
bool Snake::CheckCollisionWithSelf() const {
    const Segment& head = body_.front();
    for (std::size_t i = 1; i < body_.size(); ++i) {
        if (body_[i] == head) {
            return true;
        }
    }
    return false;
}

// Method to check if the snake has collided with the walls
bool Snake::CheckCollisionWithWalls() const {
    const Segment& head = body_.front();
    return head.first < 0 || head.first >= field_width_ ||
           head.second < 0 || head.second >= field_height_;
}

// Method to grow the snake by one segment
void Snake::Grow() {
    grow_ = true;
}

// Method to get the snake's body segments
const std::vector<Segment>& Snake::GetBody() const {
    return body_;
}

// Method to get the current direction of the snake
Direction Snake::GetDirection() const {
    return direction_;
}

// Private method to check if the new direction is opposite to the current one
bool Snake::IsOppositeDirection(Direction new_direction) const {
    switch (direction_) {
        case Direction::UP:
            return new_direction == Direction::DOWN;
        case Direction::DOWN:
            return new_direction == Direction::UP;
        case Direction::LEFT:
            return new_direction == Direction::RIGHT;
        case Direction::RIGHT:
            return new_direction == Direction::LEFT;
        default:
            return false;
    }
}

}  // namespace s21
