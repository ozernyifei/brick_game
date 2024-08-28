#ifndef S21_SCORE_BOARD_H_
#define S21_SCORE_BOARD_H_

#include <QWidget>        // For QWidget base class
#include <QLabel>         // For QLabel to display the score
#include <QVBoxLayout>    // For QVBoxLayout to arrange labels

namespace s21 {

class ScoreBoard : public QWidget {
    Q_OBJECT

public:
    // Constructor and Destructor
    ScoreBoard(QWidget *parent = nullptr);
    ~ScoreBoard() = default;

    // Methods to update the score and high score
    void UpdateScore(int score);
    void UpdateHighScore(int high_score);

private:
    // Data members
    QLabel *score_label_;      // Label to display the current score
    QLabel *high_score_label_; // Label to display the high score

    // Private methods
    void SetupLayout(); // Sets up the layout for the labels
};

}  // namespace s21

#endif  // S21_SCORE_BOARD_H_
