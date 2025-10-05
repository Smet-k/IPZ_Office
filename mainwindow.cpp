#include "mainwindow.h"
#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSplitter>
#include <QLabel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("ClockedIn");

    QWidget *central = new QWidget(this);
    central->setStyleSheet("Background-color: #212121;");
    QHBoxLayout *layout = new QHBoxLayout(central);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    stack = new QStackedWidget(this);

    homePage = new HomePage();
    statPage = new StatPage();

    stack->addWidget(homePage);
    stack->addWidget(statPage);

    connect(homePage, &HomePage::goToStatpage, this, &MainWindow::showStatpage);
    connect(statPage, &StatPage::goToHomePage, this, &MainWindow::showHomePage);

    setCentralWidget(central);

    layout->addWidget(createSidemenu());
    layout->addWidget(stack);
}

QWidget* MainWindow::createSidemenu(){
    this->setStyleSheet(
        "QPushButton {"
        "font-family: 'Noto Sans';"
        "font-weight: 400;"
        "height: 25px;"
        "text-align: left;"
        "padding: 5px 10px 5px 10px;"
        "}"
    );

    QWidget *sideMenu = new QWidget();
    sideMenu->setStyleSheet("Background-color: #1c1c1c");
    sideMenu->setFixedWidth(150);

    QVBoxLayout *menuLayout = new QVBoxLayout(sideMenu);
    menuLayout->setContentsMargins(0,0,0,0);
    menuLayout->setSpacing(5);

    QWidget *headerGroup = new QWidget();
    QVBoxLayout *headerLayout = new QVBoxLayout(headerGroup);
    QLabel *headerText = new QLabel("Username");
    QFont font = QFont("Noto Sans", 15, 400);
    headerText->setFont(font);
    headerLayout->addWidget(headerText);

    QWidget *buttonGroup = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(buttonGroup);
    mainLayout->setSpacing(15);
    QPushButton *homeBtn = new QPushButton("Home");

    QPushButton *statsBtn = new QPushButton("Stats");
    QPushButton *clock = new QPushButton("Clock In");
    connect(homeBtn, &QPushButton::clicked, this, &MainWindow::showHomePage);
    connect(statsBtn, &QPushButton::clicked, this, &MainWindow::showStatpage);
    mainLayout->addWidget(homeBtn);
    mainLayout->addWidget(statsBtn);
    mainLayout->addStretch();
    mainLayout->addWidget(clock);


    QWidget *footerGroup = new QWidget();
    QVBoxLayout *footerLayout = new QVBoxLayout(footerGroup);
    QPushButton *logout = new QPushButton("Log out");
    footerLayout->addWidget(logout);

    QFrame *line1 = new QFrame();
    line1->setFrameShape(QFrame::HLine);
    line1->setStyleSheet("color: #383838;");

    QFrame *line2 = new QFrame();
    line2->setFrameShape(QFrame::HLine);
    line2->setStyleSheet("color: #383838;");

    menuLayout->addWidget(headerGroup);
    menuLayout->addWidget(line1);
    menuLayout->addWidget(buttonGroup);
    menuLayout->addWidget(line2);
    menuLayout->addWidget(footerGroup);

    return sideMenu;
}

void MainWindow::showHomePage() {
    stack->setCurrentWidget(homePage);
}

void MainWindow::showStatpage() {
    stack->setCurrentWidget(statPage);
}
