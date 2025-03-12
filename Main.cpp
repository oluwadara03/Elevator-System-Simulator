#include "SimulatorGUI.h"
#include <QApplication>

// Main function, starts the GUI application
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SimulatorGUI window;
    window.show();
    return app.exec();
}
