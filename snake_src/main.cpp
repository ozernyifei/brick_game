#include <QApplication>
#include "main_window.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    s21::MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
