#ifndef LOGINMODAL_H
#define LOGINMODAL_H

#include <QDialog>
#include <QLineEdit>
#include "employeeservice.h"
#include "employee.h"
class LoginModal : public QDialog
{
    Q_OBJECT
public:
    LoginModal(QWidget *parent = nullptr);
    QString login() const;
    QString password() const;
private:
    QLineEdit *loginField;
    QLineEdit *passwordField;
    EmployeeService *service;
signals:
    void authorizationSuccessful(Employee employee);
};

#endif // LOGINMODAL_H
