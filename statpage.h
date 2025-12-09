#ifndef STATPAGE_H
#define STATPAGE_H
#include <QWidget>
#include <QString>
#include "stat.h"
#include "statservice.h"
#include "employee.h"
#include <QLabel>
class StatPage : public QWidget
{
    Q_OBJECT
public:
    StatPage(QWidget *parent = nullptr);

    void setAuthorizedEmployee(const Employee &authorizedEmp) {authorizedEmployee = authorizedEmp; updateDisplayData();}
protected:
    void showEvent(QShowEvent *event) override;
private:
    void updateDisplayData();
    Employee authorizedEmployee;

    QWidget* CreateStatus(Stat stat);
    StatService* service;
    QLabel *position;
    QLabel *hireDate;
    QLabel *text;
signals:
    void goToHomePage();
};

#endif // STATPAGE_H
