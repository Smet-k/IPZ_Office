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
#include <QScrollArea>
#include "layouthelper.h"

void HomePage::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    service->fetchNewsletters();
}

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

    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setContentsMargins(0,0,0,0);
    scrollLayout->setSpacing(15);

    service = new NewsService(this);

    connect(service, &NewsService::newslettersReady, this,
            [=](const QList<Newsletter> &list)
            {
                clearLayout(scrollLayout);
                for (const Newsletter &news : list) {
                    scrollLayout->addWidget(createNewsRow(news));
                }
            });

    service->fetchNewsletters();

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setFrameShape(QFrame::NoFrame);

    newsFrameLayout->addWidget(scrollArea);
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
    // create a separate API function to fetch this data
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

ClickableWidget* HomePage::createNewsRow(Newsletter news){
    ClickableWidget* newsRow = new ClickableWidget();
    QVBoxLayout* newsLayout = new QVBoxLayout(newsRow);
    newsRow->setObjectName("newsRow");
    newsRow->setCursor(Qt::PointingHandCursor);
    newsRow->setStyleSheet(R"(
        #newsRow {
            background-color: #1c1c1c;
            border-radius: 8px;
        }
        #newsRow:hover {
            background-color: #2a2a2a;
        }
    )");

    QFont font = QFont("Noto Sans", 14);
    QFont subtextFont = QFont("Noto Sans", 8);
    QLabel* newsTitle = new QLabel(news.title());
    newsTitle->setFont(font);
    newsTitle->setStyleSheet("background: transparent;");

    QLabel* subtext = new QLabel(QString("Published at %1").arg(news.date().toString("MM.dd.yy")));
    subtext->setFont(subtextFont);
    subtext->setStyleSheet("background: transparent;");


    newsLayout->addWidget(newsTitle);
    newsLayout->addWidget(subtext);

    connect(newsRow, &ClickableWidget::clicked, this, [this, news]() {
        emit goToNewspage(news);
    });


    return newsRow;
}
