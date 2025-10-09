#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QFrame>
#include "newsletter.h"

class HomePage : public QWidget
{
    Q_OBJECT
public:
    HomePage(QWidget *parent = nullptr);
private:
    QFrame* getAttendance();
    QWidget* createNewsRow(Newsletter news);
signals:
    void goToStatpage();
};

#endif // HOMEPAGE_H
