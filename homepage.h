#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QFrame>
#include "newsletter.h"
#include "clickablewidget.h"
#include "QShowEvent"
#include "newsservice.h"

class HomePage : public QWidget
{
    Q_OBJECT
public:
    HomePage(QWidget *parent = nullptr);
protected:
    void showEvent(QShowEvent *event) override;
private:
    NewsService *service;
    QFrame* getAttendance();
    ClickableWidget* createNewsRow(Newsletter news);
signals:
    void goToStatpage();
    void goToNewspage(Newsletter news);
};

#endif // HOMEPAGE_H
