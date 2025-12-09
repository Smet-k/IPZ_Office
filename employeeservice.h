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

    void fetchEmployees(int page=1, int pagesize=10);
    void editEmployee(const Employee &employee);
    void authEmployee(const QString login, const QString password);
    void deleteEmployee(const int id);
signals:
    void employeesReady(const QList<Employee>& list, const int totalCount);
    void employeeEdited(const int status);
    void employeeAuthorized(Employee employee);
    void employeeDeleted(const int status);
private:
    QNetworkAccessManager *manager;
};

#endif // EMPLOYEESERVICE_H
