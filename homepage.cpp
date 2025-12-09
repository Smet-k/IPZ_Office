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
#include "paginationnavigator.h"
void HomePage::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    service->fetchNewsletters();
}

HomePage::HomePage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);


    welcomeText = new QLabel("Welcome! Username");
    QFont font("Noto Sans", 32);
    welcomeText->setFont(font);
    welcomeText->setStyleSheet("margin-left:12px");

    PaginationNavigator *nav = new PaginationNavigator();

    QWidget *contentBox = new QWidget();
    QHBoxLayout *contentLayout = new QHBoxLayout(contentBox);
    contentLayout->setContentsMargins(0,0,0,0);

    QFrame *newsletterFrame = new QFrame();
    QVBoxLayout *newsFrameLayout = new QVBoxLayout(newsletterFrame);
    newsletterFrame->setObjectName("News");
    newsletterFrame->setFrameShape(QFrame::NoFrame); //tmp
    newsletterFrame->setStyleSheet("#News {margin:0px 5px 20px 5px;}");

    QWidget *scrollWidget = new QWidget();
    scrollWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setContentsMargins(0,0,0,0);
    scrollLayout->setSpacing(15);

    service = new NewsService(this);

    connect(service, &NewsService::newslettersReady, this,
            [=](const QList<Newsletter> &list, const int totalCount)
            {
                clearLayout(scrollLayout);
                for (const Newsletter &news : list) {
                    scrollLayout->addWidget(createNewsRow(news));
                }

                nav->setTotalEntities(totalCount);
            });

    service->fetchNewsletters();

    connect(nav, &PaginationNavigator::pageChanged, this, [=](const int page){
        newsPage = page;
        service->fetchNewsletters(page, PAGESIZE);
    });


    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setFrameShape(QFrame::NoFrame);

    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    newsFrameLayout->addWidget(scrollArea);
    newsletterFrame->setLayout(newsFrameLayout);

    contentLayout->addWidget(newsletterFrame);

    QHBoxLayout *navLayout = new QHBoxLayout();

    navLayout->addStretch();
    navLayout->addWidget(nav);
    navLayout->addStretch();

    mainLayout->addWidget(welcomeText, 2);
    mainLayout->addWidget(contentBox, 9);
    mainLayout->addLayout(navLayout, 1);
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
