#include "game_view.h"
#include "qpushbutton.h"
#include <QPainter>    // For drawing the game elements
#include <QKeyEvent>   // For handling key events
#include <QMessageBox> // For displaying game over messages
#include <QDebug>

namespace s21 {

// Constructor to initialize the game view
GameView::GameView(QWidget *parent)
    : QWidget(parent),
      snake_(4, 10, 20),
      apple_(10, 20),
      game_field_(10, 20),
      timer_(new QTimer(this)),
      is_game_over_(false),
      current_score_(0),      // Initialize current score
      high_score_(0),
      current_level_(1),        // Start at level 1
      max_level_(10),           // Set max level to 10
      score_threshold_(5) {     // Score needed to level up{        // Initialize high score
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(10 * kBlockSize, 20 * kBlockSize);

    connect(timer_, &QTimer::timeout, this, &GameView::UpdateGame);
    connect(this, &GameView::LevelUpdated, this, &GameView::UpdateSpeed);

    LoadHighScore();
}

// Start the game
void GameView::StartGame() {
    snake_ = Snake(4, 10, 20);  // Reset the snake to initial state
    apple_.PlaceApple();        // Place a new apple on the field
    is_game_over_ = false;
    current_score_ = 0;
    current_level_ = 1;         // Reset level to 1
    emit ScoreUpdated(current_score_);
    emit HighScoreUpdated(high_score_);
    emit LevelUpdated(current_level_);  // Emit initial level signal
    UpdateSpeed();              // Set initial speed
    update();
    timer_->start(kInitialSpeed);
}


void GameView::PauseGame() {
    if (timer_->isActive()) {
        timer_->stop();  // Pauses the game
    } else {
        timer_->start(kInitialSpeed);  // Resumes the game
    }
}

void GameView::ResetGame() {
    // timer_->stop();   // Stops the game
    StartGame();      // Restart the game by re-initializing everything
}


void GameView::HandleRestart() {
    ResetGame();  // Restart the game
}

void GameView::HandleExit() {
    close();  // Exit the application
}

void GameView::UpdateSpeed() {
    int new_speed = kInitialSpeed - (current_level_ - 1) * 10; // Increase speed with level
    new_speed = std::max(50, new_speed); // Ensure speed doesn't get too fast
    timer_->setInterval(new_speed);  // Update timer with new speed
}

// Paint event to render the game elements
void GameView::paintEvent(QPaintEvent * /* event */) {
    QPainter painter(this);

    // Draw game field borders - adjust so borders are inside the actual playable area
    painter.setPen(QPen(Qt::black, 2));  // Black border with 2 pixels width
    painter.drawRect(0, 0, width() - 1, height() - 1); // Draw the border of the entire widget

    // Draw the snake
    painter.setBrush(Qt::green);
    for (const auto &segment : snake_.GetBody()) {
        painter.drawRect(segment.first * kBlockSize, segment.second * kBlockSize, kBlockSize, kBlockSize);
    }

    // Draw the apple
    painter.setBrush(Qt::red);
    painter.drawRect(apple_.GetPosition().first * kBlockSize, apple_.GetPosition().second * kBlockSize, kBlockSize, kBlockSize);
}



// Key press event to control the snake
void GameView::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Up:
            snake_.ChangeDirection(Direction::UP);
            break;
        case Qt::Key_Down:
            snake_.ChangeDirection(Direction::DOWN);
            break;
        case Qt::Key_Left:
            snake_.ChangeDirection(Direction::LEFT);
            break;
        case Qt::Key_Right:
            snake_.ChangeDirection(Direction::RIGHT);
            break;
    }
}

// Update game state on each timer tick
void GameView::UpdateGame() {
    if (is_game_over_) return;

    snake_.Move();       // Move the snake
    CheckCollisions();   // Check for collisions

    update();  // Trigger a repaint
}


void GameView::SaveHighScore() {
    std::ofstream file(high_score_file_);
    if (file.is_open()) {
        file << high_score_;
        file.close();
    }
    else {
        qDebug() << "Unable to save high score to file.";
    }
}


void GameView::LoadHighScore() {
    std::ifstream file(high_score_file_);
    if (file.is_open()) {
        file >> high_score_;  // Read the high score from the file
        file.close();
    } else {
        high_score_ = 0;  // If the file doesn't exist, set the high score to 0
        qDebug() << "No high score file found. Starting with high score = 0.";
    }
}



// Check for collisions
void GameView::CheckCollisions() {
    // Check collision with the walls or itself
    if (snake_.CheckCollisionWithWalls() || snake_.CheckCollisionWithSelf()) {
        EndGame();
        return;
    }

    // Check if the snake has eaten the apple
    if (apple_.GetPosition() == snake_.GetBody().front()) {
        snake_.Grow();
        apple_.PlaceApple(); // Place a new apple
        current_score_++;  // Increase the current score
        emit ScoreUpdated(current_score_); // Emit score updated signal

        if (current_score_ % score_threshold_ == 0) {
            IncreaseLevel();
        }

        if (current_score_ > high_score_) {
            high_score_ = current_score_;
            emit HighScoreUpdated(high_score_); // Emit high score updated signal
            SaveHighScore();
        }

        if (snake_.GetBody().size() >= 200) {  // Если длина змейки >= 200
            GameWin();  // Вызов метода победы
        }
    }
}


void GameView::IncreaseLevel() {
    if (current_level_ < max_level_) {
        current_level_++;
        emit LevelUpdated(current_level_);  // Notify that level has increased
        UpdateSpeed();  // Adjust the speed when the level increases
    }
}

// End the game
void GameView::EndGame() {
    is_game_over_ = true;
    timer_->stop();  // Stop the game timer

    // Create a custom message box for game over with "Restart" and "Exit" buttons
    QMessageBox msgBox;
    msgBox.setWindowTitle("Game Over");
    msgBox.setText("You lost! What would you like to do?");

    // Add "Restart" button
    QPushButton *restartButton = msgBox.addButton(tr("Restart"), QMessageBox::AcceptRole);
    // Add "Exit" button
    QPushButton *exitButton = msgBox.addButton(tr("Exit"), QMessageBox::RejectRole);

    msgBox.exec();  // Show the message box and wait for user interaction

    connect(restartButton, &QPushButton::clicked, this, &GameView::HandleRestart);
    connect(exitButton, &QPushButton::clicked, this, &GameView::HandleExit);

}

//void GameView::GameWin() {
//    is_game_over_ = true;
//    timer_->stop();

//    // Create a custom message box for game over with "Restart" and "Exit" buttons
//    QMessageBox msgBox;
//    msgBox.setWindowTitle("Congratulations!");
//    msgBox.setText("You won the game! What would you like to do?");

//    // Add "Restart" button
//    QPushButton *restartButton = msgBox.addButton(tr("Restart"), QMessageBox::AcceptRole);
//    // Add "Exit" button
//    QPushButton *exitButton = msgBox.addButton(tr("Exit"), QMessageBox::RejectRole);

//    msgBox.exec();  // Show the message box and wait for user interaction

//    connect(restartButton, &QPushButton::clicked, this, &GameView::HandleRestart);
//    connect(exitButton, &QPushButton::clicked, this, &GameView::HandleExit);

//}

void GameView::GameWin() {
    timer_->stop();  // Остановить игру
    QMessageBox::information(this, "Congratulations!", "You won the game!");  // Сообщение о победе
    ResetGame();  // Перезапуск игры
}


}  // namespace s21
