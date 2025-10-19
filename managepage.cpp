#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>

#include "managepage.h"

ManagePage::ManagePage() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* sectionsLayout = new QHBoxLayout();

    QPushButton* employeeBtn = new QPushButton("Employees");
    QPushButton* newsBtn = new QPushButton("News");

    connect(employeeBtn, &QPushButton::clicked, this, &ManagePage::showEmployeeSection);
    connect(newsBtn, &QPushButton::clicked, this, &ManagePage::showNewsSection);

    sectionsLayout->addWidget(employeeBtn);
    sectionsLayout->addWidget(newsBtn);

    mainLayout->addLayout(sectionsLayout);

    stack = new QStackedWidget();

    // News
    QWidget *newsScrollWidget = new QWidget();
    QVBoxLayout *newsScrollLayout = new QVBoxLayout(newsScrollWidget);
    newsScrollLayout->setContentsMargins(0,0,0,0);
    newsScrollLayout->setSpacing(15);

    for (int i = 10; i > 0; i--) {
        Newsletter news = Newsletter(
            QString("News Title Number %1").arg(i),
            QString("News body %1").arg(i),
            QDate(2025, 10, i));
        newsScrollLayout->addWidget(createNewsRow(news));
    }

    QScrollArea *newsScrollArea = new QScrollArea();
    newsScrollArea->setWidgetResizable(true);
    newsScrollArea->setWidget(newsScrollWidget);
    newsScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    newsScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    newsScrollArea->setFrameShape(QFrame::NoFrame);

    newsSection = new QWidget();
    QVBoxLayout *newsSectionLayout = new QVBoxLayout(newsSection);

    newsSectionLayout->addWidget(newsScrollArea);

    QHBoxLayout *newsButtonsSection = new QHBoxLayout();

    QPushButton *addNewsButton = new QPushButton("+");

    connect(addNewsButton, &QPushButton::clicked, this, [this]() {
        emit goToNewsAdd();
    });

    newsButtonsSection->addStretch();
    newsButtonsSection->addWidget(addNewsButton);

    newsSectionLayout->addLayout(newsButtonsSection);

    // Employees
    QWidget *employeeScrollWidget = new QWidget();
    QVBoxLayout *employeeScrollLayout = new QVBoxLayout(employeeScrollWidget);
    employeeScrollLayout->setContentsMargins(0,0,0,0);
    employeeScrollLayout->setSpacing(15);

    for (int i = 10; i > 0; i--) {
        Employee employee = Employee(
            QString("John"),
            QString("Doe %1").arg(i),
            QString("Employee"),
            QDate(2025, 10, i));
        employeeScrollLayout->addWidget(createEmployeeRow(employee));
    }

    QScrollArea *employeeScrollArea = new QScrollArea();
    employeeScrollArea->setWidgetResizable(true);
    employeeScrollArea->setWidget(employeeScrollWidget);
    employeeScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    employeeScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    employeeScrollArea->setFrameShape(QFrame::NoFrame);

    employeeSection = new QWidget();
    QVBoxLayout *employeeSectionLayout = new QVBoxLayout(employeeSection);


    employeeSectionLayout->addWidget(employeeScrollArea);

    QHBoxLayout *employeeButtonsSection = new QHBoxLayout();

    QPushButton *addEmployeeButton = new QPushButton("+");

    connect(addEmployeeButton, &QPushButton::clicked, this, [this]() {
        emit goToEmployeeAdd();
    });

    employeeButtonsSection->addStretch();
    employeeButtonsSection->addWidget(addEmployeeButton);

    employeeSectionLayout->addLayout(employeeButtonsSection);


    stack->addWidget(employeeSection);
    stack->addWidget(newsSection);

    mainLayout->addWidget(stack);



}

ClickableWidget* ManagePage::createNewsRow(Newsletter news){
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
        emit goToNewsEdit(news);
    });

    return newsRow;
}

ClickableWidget* ManagePage::createEmployeeRow(Employee employee){
    ClickableWidget* employeeRow = new ClickableWidget();
    QVBoxLayout* employeeLayout = new QVBoxLayout(employeeRow);
    employeeRow->setObjectName("employeeRow");
    employeeRow->setCursor(Qt::PointingHandCursor);
    employeeRow->setStyleSheet(R"(
        #employeeRow {
            background-color: #1c1c1c;
            border-radius: 8px;
        }
        #employeeRow:hover {
            background-color: #2a2a2a;
        }
    )");

    QFont font = QFont("Noto Sans", 14);
    QFont subtextFont = QFont("Noto Sans", 8);
    QLabel* employeeTitle = new QLabel(QString("%1 %2").arg(employee.name(), employee.surname()));
    employeeTitle->setFont(font);
    employeeTitle->setStyleSheet("background: transparent;");

    QLabel* subtextPosition = new QLabel(QString("Position: %1").arg(employee.position()));
    subtextPosition->setFont(subtextFont);
    subtextPosition->setStyleSheet("background: transparent;");

    QLabel* subtextEmployment = new QLabel(QString("Employed at %1").arg(employee.employmentDate().toString("MM.dd.yy")));
    subtextEmployment->setFont(subtextFont);
    subtextEmployment->setStyleSheet("background: transparent;");

    employeeLayout->addWidget(employeeTitle);
    employeeLayout->addWidget(subtextPosition);
    employeeLayout->addWidget(subtextEmployment);

    connect(employeeRow, &ClickableWidget::clicked, this, [this, employee]() {
        emit goToEmployeeEdit(employee);
    });


    return employeeRow;
}

void ManagePage::showEmployeeSection(){ stack->setCurrentWidget(employeeSection); }
void ManagePage::showNewsSection() { stack->setCurrentWidget(newsSection); }
