#ifndef STATPAGE_H
#define STATPAGE_H
#include <QWidget>
#include <QString>
#include "stat.h"
#include "statservice.h"
#include "employee.h"

class StatPage : public QWidget
{
    Q_OBJECT
public:
    StatPage(QWidget *parent = nullptr);

    void setAuthorizedEmployee(const Employee &authorizedEmp) {authorizedEmployee = authorizedEmp; }
protected:
    void showEvent(QShowEvent *event) override;
private:
    Employee authorizedEmployee;

    QWidget* CreateStatus(Stat stat);
    StatService* service;
signals:
    void goToHomePage();
};

#endif // STATPAGE_H
