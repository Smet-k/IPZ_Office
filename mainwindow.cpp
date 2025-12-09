#include "mainwindow.h"
#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSplitter>
#include <QLabel>
#include <QResizeEvent>
#include <stdio.h>
#include "loginmodal.h"
#include "logoutmodal.h"
#include <QTime>
#include <QMessageBox>

void MainWindow::clockInCheck(){
    // UPDATE CLOCKS HERE
    if(clockIn){
        latestClock.setTime(QTime::currentTime());
    } else{
        int diffSec = latestClock.time().secsTo(QTime::currentTime());
        currentStat.setWorkTime(currentStat.workTime().addSecs(diffSec));
        currentStat.setClockCount(currentStat.clockCount() + 1);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply =
        QMessageBox::question(this, "Exit", "Are you sure you want to quit?",
                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if(!clockIn){
            clockInCheck();
            StatService *localService = new StatService(this);

            connect(localService, &StatService::statEdited, this, [=](const int status){
                if (status > 0){
                    delete localService;
                    event->accept();
                }
                event->ignore();
            });

            localService->editStat(currentStat,authorizedEmployee.id());
        }
        else
            event->accept();
    } else {
        event->ignore();
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("ClockedIn");

    QWidget *central = new QWidget(this);
    central->setStyleSheet("Background-color: #212121;");
    QHBoxLayout *layout = new QHBoxLayout(central);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    statService = new StatService(this);

    stack = new QStackedWidget(this);

    homePage = new HomePage();
    statPage = new StatPage();
    newsPage = new NewsletterPage();
    managePage = new ManagePage();
    editEmployeePage = new EditEmployeePage();
    editNewsPage = new EditNewsPage();

    stack->addWidget(homePage);
    stack->addWidget(managePage);
    stack->addWidget(statPage);
    stack->addWidget(newsPage);
    stack->addWidget(editEmployeePage);
    stack->addWidget(editNewsPage);

    connect(managePage, &ManagePage::goToEmployeeEdit, this, &MainWindow::showEditEmployeePage);
    connect(managePage, &ManagePage::goToEmployeeAdd, this, &MainWindow::showAddEmployeePage);
    connect(managePage, &ManagePage::goToNewsEdit, this, &MainWindow::showEditNewsPage);
    connect(managePage, &ManagePage::goToNewsAdd, this, &MainWindow::showAddNewsPage);

    connect(editNewsPage, &EditNewsPage::formClosed, this, &MainWindow::showManagePage);
    connect(editEmployeePage, &EditEmployeePage::formClosed, this, &MainWindow::showManagePage);


    connect(homePage, &HomePage::goToNewspage, this, &MainWindow::showNewsPage);
    connect(homePage, &HomePage::goToStatpage, this, &MainWindow::showStatpage);
    connect(statPage, &StatPage::goToHomePage, this, &MainWindow::showHomePage);

    setCentralWidget(central);

    layout->addWidget(createSidemenu());
    layout->addWidget(stack);

    connect(statService, &StatService::onEmployeeStatsReply, this,
            [=](const QList<Stat> &list)
            {
                Stat latestStat = list.first();
                if (latestStat.date().year() == QDate::currentDate().year() &&
                    latestStat.date().month() == QDate::currentDate().month() &&
                    latestStat.date().day() == QDate::currentDate().day()){
                    latestClock = QDateTime(latestStat.date(), QTime::currentTime());
                    currentStat = latestStat;

                }
                else {
                    latestClock = QDateTime::currentDateTime();
                    currentStat.setId(0);
                    currentStat.setWorkTime(QTime::fromMSecsSinceStartOfDay(0));
                    currentStat.setDate(QDate::currentDate());
                    currentStat.setClockCount(0);
                    currentStat.setEmployeeId(authorizedEmployee.id());
                }
            });



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
    manageBtn = new QPushButton("Manage");

    homeBtn->setEnabled(false);
    statsBtn->setEnabled(false);
    manageBtn->setEnabled(false);
    manageBtn->setVisible(false);

    QPushButton *clock = new QPushButton("Clock In");
    clock->setEnabled(false);


    connect(homeBtn, &QPushButton::clicked, this, &MainWindow::showHomePage);
    connect(statsBtn, &QPushButton::clicked, this, &MainWindow::showStatpage);
    connect(manageBtn, &QPushButton::clicked, this, &MainWindow::showManagePage);

    mainLayout->addWidget(homeBtn);
    mainLayout->addWidget(statsBtn);
    mainLayout->addWidget(manageBtn);
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
        clockInCheck();
        if(clockIn){
            statService->fetchEmployeeStats(authorizedEmployee.id());
        } else {
            statService->editStat(currentStat, authorizedEmployee.id());
        }
    });

    connect(this, &MainWindow::clockStateChanged, this, [this, clock, homeBtn, statsBtn](bool state){
        clock->setText(state ? "Clock Out" : "Clock In");
        homeBtn->setEnabled(state);
        statsBtn->setEnabled(state);
        manageBtn->setEnabled(state);
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

void MainWindow::showNewsPage(Newsletter news) {
    newsPage->setNews(news);
    newsPage->updatePage();
    stack->setCurrentWidget(newsPage);
    setPageInteractable(clockIn);
}

void MainWindow::showEditEmployeePage(Employee employee){
    editEmployeePage->setEmployee(employee);
    editEmployeePage->updatePage();
    stack->setCurrentWidget(editEmployeePage);
    setPageInteractable(clockIn);
}

void MainWindow::showAddEmployeePage(){
    editEmployeePage->clearPage();
    stack->setCurrentWidget(editEmployeePage);
    setPageInteractable(clockIn);
}

void MainWindow::showEditNewsPage(Newsletter news){
    editNewsPage->setNews(news);
    editNewsPage->updatePage();
    stack->setCurrentWidget(editNewsPage);
    setPageInteractable(clockIn);
}

void MainWindow::showAddNewsPage(){
    editNewsPage->clearPage();
    stack->setCurrentWidget(editNewsPage);
    setPageInteractable(clockIn);
}


void MainWindow::showManagePage(){
    stack->setCurrentWidget(managePage);
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

        connect(&login, &LoginModal::authorizationSuccessful,
                this, [=](const Employee &employee){

            setAuthorizedEmployee(employee);
            statPage->setAuthorizedEmployee(employee);
            statService->fetchEmployeeStats(employee.id());

            if(employee.role() == 2 || employee.role() == 3){
                manageBtn->setVisible(true);
                manageBtn->setEnabled(clockIn);
            } else{
                manageBtn->setVisible(false);
            }

        });



        if (login.exec() == QDialog::Accepted) {
            userAuthorized = true;
            emit authorizationStateChanged(userAuthorized);
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
