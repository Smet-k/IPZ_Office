#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include "newsletter.h"
#include "clickablewidget.h"
#include "QShowEvent"
#include "newsservice.h"

#define PAGESIZE 10

class HomePage : public QWidget
{
    Q_OBJECT
public:
    HomePage(QWidget *parent = nullptr);

    void setText(QString text){
        if(welcomeText)
            welcomeText->setText(text);
    }

protected:
    void showEvent(QShowEvent *event) override;
private:
    int newsPage;
    QLabel *welcomeText;
    NewsService *service;
    QFrame* getAttendance();
    ClickableWidget* createNewsRow(Newsletter news);
signals:
    void goToStatpage();
    void goToNewspage(Newsletter news);
};

#endif // HOMEPAGE_H
