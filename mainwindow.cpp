#include "mainwindow.h"
#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSplitter>
#include <QLabel>
#include <QResizeEvent>

#include "loginmodal.h"
#include "logoutmodal.h"
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

    initializeOverlays();
    setPageInteractable(false);
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
    sideMenu->setObjectName("sideMenu");
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
    homeBtn->setEnabled(false);
    statsBtn->setEnabled(false);

    QPushButton *clock = new QPushButton("Clock In");
    clock->setEnabled(false);


    connect(homeBtn, &QPushButton::clicked, this, &MainWindow::showHomePage);
    connect(statsBtn, &QPushButton::clicked, this, &MainWindow::showStatpage);
    mainLayout->addWidget(homeBtn);
    mainLayout->addWidget(statsBtn);
    mainLayout->addStretch();
    mainLayout->addWidget(clock);


    QWidget *footerGroup = new QWidget();
    QVBoxLayout *footerLayout = new QVBoxLayout(footerGroup);
    QPushButton *loginBtn = new QPushButton("Log in");

    connect(loginBtn, &QPushButton::clicked, this, &MainWindow::onLoginButtonClicked);

    footerLayout->addWidget(loginBtn);

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

    connect(clock, &QPushButton::clicked, this, [this]() {
        setClockIn(!clockIn);
    });

    connect(this, &MainWindow::clockStateChanged, this, [this, clock, homeBtn, statsBtn](bool state){
        clock->setText(state ? "Clock Out" : "Clock In");
        homeBtn->setEnabled(state);
        statsBtn->setEnabled(state);
    });


    connect(this, &MainWindow::authorizationStateChanged, this, [this, clock, loginBtn](bool state){
        clock->setEnabled(state);
        loginBtn->setText(state ? "Log Out" : "Log In");
    });

    return sideMenu;
}

void MainWindow::showHomePage() {
    stack->setCurrentWidget(homePage);
    setPageInteractable(clockIn);
}

void MainWindow::showStatpage() {
    stack->setCurrentWidget(statPage);
    setPageInteractable(clockIn);
}

void MainWindow::setClockIn(bool state) {
    if (clockIn == state) return;
    clockIn = state;
    setPageInteractable(clockIn);
    emit clockStateChanged(clockIn);
}

void MainWindow::initializeOverlays()
{
    for (int i = 0; i < stack->count(); ++i) {
        QWidget *page = stack->widget(i);

        QWidget *overlay = new QWidget(page);
        overlay->setObjectName("overlay");
        overlay->setStyleSheet("background-color: rgba(0, 0, 0, 120);");
        overlay->hide();

        overlay->setGeometry(page->rect());
        overlay->raise();

        page->installEventFilter(this);
    }
}

void MainWindow::setPageInteractable(bool enabled)
{
    QWidget *page = stack->currentWidget();
    if (QWidget *overlay = page->findChild<QWidget*>("overlay"))
        overlay->setVisible(!enabled);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Resize) {
        QWidget *page = qobject_cast<QWidget*>(obj);
        if (page) {
            if (QWidget *overlay = page->findChild<QWidget*>("overlay"))
                overlay->setGeometry(page->rect());
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::onLoginButtonClicked() {
    if(!userAuthorized){
        LoginModal login(this);
        if (login.exec() == QDialog::Accepted) {
            userAuthorized = true;
            emit authorizationStateChanged(userAuthorized);
            // successful login logic
        }
    } else{
        LogoutModal logout(this);
        if (logout.exec() == QDialog::Accepted) {
            userAuthorized = false;
            setClockIn(userAuthorized);
            emit authorizationStateChanged(userAuthorized);
            // successful logout logic
        }
    }
}
