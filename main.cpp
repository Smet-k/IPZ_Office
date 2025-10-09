#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setStyleSheet("QWidget{color: white;}");

    MainWindow window;
    window.setFixedSize(1000,600);

    window.show();

    return app.exec();
}
