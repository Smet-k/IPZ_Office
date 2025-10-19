#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QString>
#include "newsletterpage.h"
#include <QScrollArea>
NewsletterPage::NewsletterPage() {

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *titleLayout = new QHBoxLayout();

    title = new QLabel();
    date = new QLabel();

    QFont font("Noto Sans", 18);
    QFont subtextFont("Noto Sans", 8);
    title->setFont(font);
    title->setAlignment(Qt::AlignLeft);
    title->setTextInteractionFlags(Qt::TextSelectableByMouse);
    title->setCursor(Qt::IBeamCursor);
    title->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    title->adjustSize();

    date->setFont(subtextFont);
    date->setAlignment(Qt::AlignRight);
    date->setTextInteractionFlags(Qt::TextSelectableByMouse);
    date->setCursor(Qt::IBeamCursor);
    date->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    date->adjustSize();

    titleLayout->addWidget(title);
    titleLayout->addStretch();
    titleLayout->addWidget(date);

    mainLayout->addLayout(titleLayout, 1);

    body = new QLabel();
    body->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    body->setWordWrap(true);
    body->setTextInteractionFlags(Qt::TextSelectableByMouse);
    body->setCursor(Qt::IBeamCursor);
    body->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); // let layout manage width

    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setStyleSheet("border: none");
    scrollArea->setWidget(body);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);


    mainLayout->addWidget(scrollArea, 10);
}

void NewsletterPage::updatePage(){
    title->setText(news().title());
    date->setText(QString(news().date().toString("MM.dd.yy")));
    body->setText(news().body());
}
