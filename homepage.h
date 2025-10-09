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
    QWidget* createNewsRow(QString title);
signals:
    void goToStatpage();
};

#endif // HOMEPAGE_H
