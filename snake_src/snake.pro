QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apple.cpp \
    control_panel.cpp \
    fsm_controller.cpp \
    game_field.cpp \
    game_state.cpp \
    game_view.cpp \
    main.cpp \
    main_window.cpp \
    score_board.cpp \
    snake.cpp

HEADERS += \
    apple.h \
    control_panel.h \
    fsm_controller.h \
    game_field.h \
    game_state.h \
    game_view.h \
    main_window.h \
    score_board.h \
    snake.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
