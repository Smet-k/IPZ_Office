#include "homepage.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QFile>
#include <QPixmap>
HomePage::HomePage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *text = new QLabel("Welcome! Username");
    QFont font("Noto Sans", 32);
    text->setFont(font);
    text->setStyleSheet("margin-left:12px");

    QWidget *contentBox = new QWidget();
    QHBoxLayout *contentLayout = new QHBoxLayout(contentBox);
    contentLayout->setContentsMargins(0,0,0,0);

    QFrame *newsletterFrame = new QFrame();
    QVBoxLayout *newsFrameLayout = new QVBoxLayout(newsletterFrame);
    newsletterFrame->setObjectName("News");
    newsletterFrame->setFrameShape(QFrame::NoFrame); //tmp
    newsletterFrame->setStyleSheet("#News {margin:0px 5px 20px 5px;}");


    for (int i = 1; i < 6; ++i) {
        newsFrameLayout->addWidget(createNewsRow(QString("News Title Number %1").arg(i)));
    }
    newsFrameLayout->addStretch();
    newsletterFrame->setLayout(newsFrameLayout);


    QFrame *attendanceFrame = getAttendance();
    attendanceFrame->setObjectName("Attend");
    attendanceFrame->setStyleSheet("#Attend {margin:0px 5px 20px 5px;}");

    contentLayout->addWidget(newsletterFrame);
    contentLayout->addWidget(attendanceFrame);

    mainLayout->addWidget(text, 1);
    mainLayout->addWidget(contentBox, 5);
}

QFrame* HomePage::getAttendance(){
    int n = 5; // Number of recent users attending (received from database)
    int totalEmployees = 100; // Total amount of employees clocked in
    QFrame* attendanceFrame = new QFrame();
    QVBoxLayout *attFrameLayout = new QVBoxLayout(attendanceFrame);

    attendanceFrame->setFrameShape(QFrame::NoFrame);
    attendanceFrame->setFixedWidth(225);
    attendanceFrame->setLayout(attFrameLayout);

    attFrameLayout->setSpacing(0);


    QFont font = QFont("Noto Sans", 10);
    QFont fontHeader = QFont("Noto Sans", 14);

    QLabel* headerText = new QLabel("Recent clocks");
    headerText->setFont(fontHeader);
    headerText->setAlignment(Qt::AlignLeft);
    QLabel* subtext = new QLabel(QString("%1 users (last 15 minutes)").arg(n));
    subtext->setFont(font);
    subtext->setStyleSheet("Padding-left: 10px;");

    attFrameLayout->addWidget(headerText);
    attFrameLayout->addWidget(subtext);

    for (int i = 0; i < n; ++i) {
        QWidget* employeeInfo = new QWidget();
        QHBoxLayout* employeeRow = new QHBoxLayout(employeeInfo);

        QLabel* employeeName = new QLabel(QString("Employee%1").arg(i));
        employeeName->setFont(font);
        employeeName->setAlignment(Qt::AlignLeft);
        // Maybe add an icon next to authorized user;
        employeeRow->addWidget(employeeName);

        attFrameLayout->addWidget(employeeInfo);
    }

    if(totalEmployees - n> 0){
        QLabel* footerText = new QLabel(QString("Other users(%1)").arg(totalEmployees - n));
        footerText->setStyleSheet("Padding-left: 10px;");
        footerText->setFont(font);
        footerText->setAlignment(Qt::AlignLeft);

        attFrameLayout->addWidget(footerText);
    }
    attFrameLayout->addStretch();

    return attendanceFrame;
}

// Make it into a separate class to make it a functional button
QWidget* HomePage::createNewsRow(QString title){
    QWidget* newsRow = new QWidget();
    QVBoxLayout* newsLayout = new QVBoxLayout(newsRow);
    newsRow->setObjectName("newsRow");
    newsRow->setCursor(Qt::PointingHandCursor);
    newsRow->setStyleSheet(R"(
        QWidget#newsRow {
            background-color: #1c1c1c;
            border-radius: 8px;
        }
        QWidget#newsRow:hover {
            background-color: #2a2a2a;
        }
    )");

    QFont font = QFont("Noto Sans", 14);
    QFont subtextFont = QFont("Noto Sans", 8);
    QLabel* newsTitle = new QLabel(title);
    newsTitle->setFont(font);
    newsTitle->setStyleSheet("background: transparent;");

    QLabel* subtext = new QLabel("Published X days ago");
    subtext->setFont(subtextFont);
    subtext->setStyleSheet("background: transparent;");


    newsLayout->addWidget(newsTitle);
    newsLayout->addWidget(subtext);

    return newsRow;
}
