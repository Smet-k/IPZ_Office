#ifndef EMPLOYEESERVICE_H
#define EMPLOYEESERVICE_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include "employee.h"
#define EMPLOYEE_API QStringLiteral("http://localhost:8080/api/employee")
class EmployeeService : public QObject
{
    Q_OBJECT
public:
    explicit EmployeeService(QObject * parent = nullptr);

    void fetchEmployees();
    void editEmployee(const Employee &employee);
    void authEmployee(const QString login, const QString password);
signals:
    void employeesReady(const QList<Employee>& list);
    void employeeEdited(const int status);
    void employeeAuthorized(Employee employee);

private:
    QNetworkAccessManager *manager;
};

#endif // EMPLOYEESERVICE_H
