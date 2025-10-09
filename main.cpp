#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFont font = QFont("Noto Sans", 10);

    app.setFont(font);
    app.setStyleSheet(R"(
    QWidget{ color: white; }

    QPushButton:disabled {
        color: gray;
        background-color: #333333;
        border: 1px solid #444;
        border-radius: 2px;
    }
    )");

    MainWindow window;
    window.setFixedSize(1000,600);

    window.show();

    return app.exec();
}
