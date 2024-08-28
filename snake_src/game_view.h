#ifndef S21_GAME_VIEW_H_
#define S21_GAME_VIEW_H_

#include <QWidget>
#include <QTimer>
#include <fstream>
#include <string>
#include "snake.h"
#include "apple.h"
#include "game_field.h"


namespace s21 {

class GameView : public QWidget {
    Q_OBJECT

public:
    GameView(QWidget *parent = nullptr);
    ~GameView() = default;

    void StartGame();

signals:
    void ScoreUpdated(int score);
    void HighScoreUpdated(int high_score);
    void LevelUpdated(int level);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void PauseGame();
    void ResetGame();
    void HandleRestart();
    void HandleExit();

private:
    void UpdateGame();
    void CheckCollisions();
    void EndGame();
    void GameWin();
    void IncreaseLevel();      // Function to handle level increase
    void UpdateSpeed();        // Function to update speed based on level

    void SaveHighScore();          // Save high score to file
    void LoadHighScore();          // Load high score from file

    Snake snake_;
    Apple apple_;
    GameField game_field_;
    QTimer *timer_;
    bool is_game_over_;
    int current_score_;  // Holds the current score
    int high_score_;     // Holds the high score
    int current_level_;        // Track the current level
    int max_level_;            // Maximum level allowed
    int score_threshold_;      // Points needed to level up

    static constexpr int kInitialSpeed = 150;
    static constexpr int kBlockSize = 20;
    const std::string high_score_file_="high_score.txt";
};

}  // namespace s21

#endif  // S21_GAME_VIEW_H_
