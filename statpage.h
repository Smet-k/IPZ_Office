#ifndef STATPAGE_H
#define STATPAGE_H
#include <QWidget>
#include <QString>

class StatPage : public QWidget
{
    Q_OBJECT
public:
    StatPage(QWidget *parent = nullptr);
private:
    QWidget* CreateStatus(QString date, int hours, int timeSeconds, bool positive);
signals:
    void goToHomePage();
};

#endif // STATPAGE_H
