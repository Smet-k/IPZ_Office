#ifndef STATPAGE_H
#define STATPAGE_H
#include <QWidget>
#include <QString>
#include "stat.h"
class StatPage : public QWidget
{
    Q_OBJECT
public:
    StatPage(QWidget *parent = nullptr);
private:
    QWidget* CreateStatus(Stat stat);
signals:
    void goToHomePage();
};

#endif // STATPAGE_H
