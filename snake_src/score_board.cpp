#include "score_board.h"

namespace s21 {

// Constructor to initialize the scoreboard
ScoreBoard::ScoreBoard(QWidget *parent)
    : QWidget(parent),
      score_label_(new QLabel("Score: 0", this)),
      high_score_label_(new QLabel("High Score: 0", this)) {

    // Set up the layout for the scoreboard
    SetupLayout();
}

// Method to update the current score
void ScoreBoard::UpdateScore(int score) {
    score_label_->setText("Score: " + QString::number(score));
}

// Method to update the high score
void ScoreBoard::UpdateHighScore(int high_score) {
    high_score_label_->setText("High Score: " + QString::number(high_score));
}

// Private method to set up the layout
void ScoreBoard::SetupLayout() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(score_label_);
    layout->addWidget(high_score_label_);

    setLayout(layout);
}

}  // namespace s21
