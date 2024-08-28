#ifndef S21_CONTROL_PANEL_H_
#define S21_CONTROL_PANEL_H_

#include <QWidget>          // For QWidget base class
#include <QPushButton>      // For QPushButton
#include <QVBoxLayout>      // For QVBoxLayout

namespace s21 {

class ControlPanel : public QWidget {
    Q_OBJECT

public:
    // Constructor and Destructor
    ControlPanel(QWidget *parent = nullptr);
    ~ControlPanel() = default;

signals:
    void StartClicked();  // Emitted when the Start button is clicked
    void PauseClicked();  // Emitted when the Pause button is clicked
    void ResetClicked();  // Emitted when the Reset button is clicked

private:
    // Private methods
    void SetupLayout(); // Sets up the layout and adds buttons

    // Data members
    QPushButton *start_button_;  // Button to start the game
    QPushButton *pause_button_;  // Button to pause the game
    QPushButton *reset_button_;  // Button to reset the game
};

}  // namespace s21

#endif  // S21_CONTROL_PANEL_H_
