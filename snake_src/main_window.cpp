#include "main_window.h"
#include <QWidget>       // For QWidget
#include <QVBoxLayout>   // For QVBoxLayout
#include <QHBoxLayout>   // For QHBoxLayout

namespace s21 {

// Constructor to initialize the main window
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      game_view_(new GameView(this)),
      control_panel_(new ControlPanel(this)),
      score_board_(new ScoreBoard(this)) {

    // Set up the layout for the main window
    SetupLayout();

    // Connect signals and slots between components
    ConnectSignals();
}

// Private method to set up the layout
void MainWindow::SetupLayout() {
    // Central widget for the main window
    QWidget *central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    // Layouts for arranging the widgets
    QVBoxLayout *main_layout = new QVBoxLayout(central_widget);
    QHBoxLayout *top_layout = new QHBoxLayout();

    // Add the score board and control panel to the top layout
    top_layout->addWidget(score_board_);
    top_layout->addWidget(control_panel_);

    // Add the top layout and game view to the main layout
    main_layout->addLayout(top_layout);
    main_layout->addWidget(game_view_);
}

// Private method to connect signals and slots
void MainWindow::ConnectSignals() {
    // Connect the control panel buttons to game view slots
    connect(control_panel_, &ControlPanel::StartClicked, game_view_, &GameView::StartGame);
    connect(game_view_, &GameView::ScoreUpdated, score_board_, &ScoreBoard::UpdateScore);
    connect(game_view_, &GameView::HighScoreUpdated, score_board_, &ScoreBoard::UpdateHighScore);

    connect(control_panel_, &ControlPanel::PauseClicked, game_view_, &GameView::PauseGame);
    connect(control_panel_, &ControlPanel::ResetClicked, game_view_, &GameView::ResetGame);

    // You can also connect signals to update the score on the scoreboard
    // Example:
    // connect(game_view_, &GameView::ScoreUpdated, score_board_, &ScoreBoard::UpdateScore);
}

}  // namespace s21
