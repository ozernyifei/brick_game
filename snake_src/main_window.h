#ifndef S21_MAIN_WINDOW_H_
#define S21_MAIN_WINDOW_H_

#include <QMainWindow>      // For QMainWindow base class
#include "game_view.h"      // For GameView class
#include "control_panel.h"  // For ControlPanel class
#include "score_board.h"    // For ScoreBoard class

namespace s21 {

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    // Constructor and Destructor
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private:
    // Private methods
    void SetupLayout();  // Sets up the layout for the main window
    void ConnectSignals(); // Connects signals and slots between components

    // Data members
    GameView *game_view_;         // Widget to display the game
    ControlPanel *control_panel_; // Panel with control buttons
    ScoreBoard *score_board_;     // Widget to display scores
};

}  // namespace s21

#endif  // S21_MAIN_WINDOW_H_
