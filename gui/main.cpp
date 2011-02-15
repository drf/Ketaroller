#include <QtGui/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Instantiate first window
    MainWindow w;
    w.show();

    return app.exec();
}
