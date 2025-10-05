#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QFrame>
class HomePage : public QWidget
{
    Q_OBJECT
public:
    HomePage(QWidget *parent = nullptr);
private:
    QFrame* getAttendance();
signals:
    void goToStatpage();
};

#endif // HOMEPAGE_H
