#include "control_panel.h"

namespace s21 {

// Constructor to initialize the control panel
ControlPanel::ControlPanel(QWidget *parent)
    : QWidget(parent),
      start_button_(new QPushButton("Start", this)),
      pause_button_(new QPushButton("Pause", this)),
      reset_button_(new QPushButton("Reset", this)) {

    // Set up the layout of the control panel
    SetupLayout();

    // Connect buttons to signals
    connect(start_button_, &QPushButton::clicked, this, &ControlPanel::StartClicked);
    connect(pause_button_, &QPushButton::clicked, this, &ControlPanel::PauseClicked);
    connect(reset_button_, &QPushButton::clicked, this, &ControlPanel::ResetClicked);
}

// Private method to set up the layout
void ControlPanel::SetupLayout() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(start_button_);
    layout->addWidget(pause_button_);
    layout->addWidget(reset_button_);

    setLayout(layout);
}

}  // namespace s21
