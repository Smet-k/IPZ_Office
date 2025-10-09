#include "statpage.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>

#include <QLabel>
#include <QString>
#include <QScrollArea>
#include <QRandomGenerator>
StatPage::StatPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);

    QWidget *userInfo = new QWidget();
    QHBoxLayout *userLayout = new QHBoxLayout(userInfo);

    QWidget *employeeInfo = new QWidget();
    QVBoxLayout *employeeLayout = new QVBoxLayout(employeeInfo);
    QLabel *position = new QLabel("Position: Employee");
    QLabel *hireDate = new QLabel("Hire date: 10/4/2025");

    employeeLayout->addWidget(position);
    employeeLayout->addWidget(hireDate);



    QLabel *text = new QLabel("Username");
    QFont font("Noto Sans", 32);
    text->setFont(font);

    userLayout->addWidget(text);
    userLayout->addStretch();
    userLayout->addWidget(employeeInfo);

    QWidget *attendanceInfo = new QWidget();
    QVBoxLayout *attendanceLayout = new QVBoxLayout(attendanceInfo);
    attendanceLayout->setContentsMargins(0,0,0,0);
    attendanceLayout->setSpacing(0);

    QWidget *statusHeader = new QWidget();
    QHBoxLayout *headerRow = new QHBoxLayout(statusHeader);
    headerRow->setContentsMargins(0,0,0,0);
    headerRow->setSpacing(0);

    QFont headerFont("Noto Sans", 10, 500);

    QLabel *dateHeader = new QLabel("Date");
    dateHeader->setStyleSheet("Padding:8px;");
    QLabel *hoursHeader = new QLabel("Work Time");
    hoursHeader->setStyleSheet("Padding:8px;");
    QLabel *timeHeader = new QLabel("Clock count");
    timeHeader->setStyleSheet("Padding:8px;");

    dateHeader->setFont(headerFont);
    hoursHeader->setFont(headerFont);
    timeHeader->setFont(headerFont);

    dateHeader->setAlignment(Qt::AlignCenter);
    hoursHeader->setAlignment(Qt::AlignCenter);
    timeHeader->setAlignment(Qt::AlignCenter);

    QFrame *line1 = new QFrame();
    line1->setFrameShape(QFrame::VLine);
    line1->setStyleSheet("color: #383838;");

    QFrame *line2 = new QFrame();
    line2->setFrameShape(QFrame::VLine);
    line2->setStyleSheet("color: #383838;");

    headerRow->addWidget(dateHeader);
    headerRow->addWidget(line1);
    headerRow->addWidget(hoursHeader);
    headerRow->addWidget(line2);
    headerRow->addWidget(timeHeader);

    statusHeader->setContentsMargins(0,0,0,0);
    statusHeader->setStyleSheet("background-color:#303030;");

    attendanceLayout->addWidget(statusHeader);

    QWidget *contentWidget = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->setSpacing(0);


    for (int i = 25; i > 0; i--) {
        QTime statTime;
        statTime.setHMS(QRandomGenerator::global()->bounded(6, 12), i, i);
        Stat stat = Stat(QDate(2025, 10, i+1), statTime, i % 3 + 1);
        contentLayout->addWidget(CreateStatus(stat));
    }


    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(contentWidget);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setFrameShape(QFrame::NoFrame);

    attendanceLayout->addWidget(scrollArea);

    attendanceLayout->addStretch();



    layout->addWidget(userInfo);
    layout->addWidget(attendanceInfo);
}

QWidget* StatPage::CreateStatus(Stat stat){
    bool positive = stat.workTime().hour() >= 8;
    QWidget *status = new QWidget();
    QHBoxLayout *statusRow = new QHBoxLayout(status);
    statusRow->setContentsMargins(0,0,0,0);
    statusRow->setSpacing(0);

    QFont font("Noto Sans", 10);

    QLabel *dateText = new QLabel(stat.date().toString("MM.dd.yy"));
    dateText->setStyleSheet("Padding:8px;");
    QLabel *hoursText = new QLabel(stat.workTime().toString());
    hoursText->setStyleSheet("Padding:8px;");
    QLabel *timeText = new QLabel(QString::number(stat.clockCount()));
    timeText->setStyleSheet("Padding:8px;");

    dateText->setFont(font);
    hoursText->setFont(font);
    timeText->setFont(font);

    dateText->setAlignment(Qt::AlignCenter);
    hoursText->setAlignment(Qt::AlignCenter);
    timeText->setAlignment(Qt::AlignCenter);

    QString lineColor = positive ? "Green" : "#b30000";

    QFrame *line1 = new QFrame();
    line1->setFrameShape(QFrame::VLine);
    line1->setStyleSheet(QString("color: %1;").arg(lineColor));

    QFrame *line2 = new QFrame();
    line2->setFrameShape(QFrame::VLine);
    line2->setStyleSheet(QString("color: %1;").arg(lineColor));


    statusRow->addWidget(dateText);
    statusRow->addWidget(line1);
    statusRow->addWidget(hoursText);
    statusRow->addWidget(line2);
    statusRow->addWidget(timeText);

    QString bgColor = positive ? "DarkGreen" : "DarkRed";
    status->setContentsMargins(0,0,0,0);
    status->setStyleSheet(QString("background-color: %1;").arg(bgColor));

    return status;
}
