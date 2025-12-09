#ifndef EDITEMPLOYEEPAGE_H
#define EDITEMPLOYEEPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QDateEdit>
#include "employee.h"
#include "employeeservice.h"
class EditEmployeePage : public QWidget
{
    Q_OBJECT
public:
    EditEmployeePage();


    void setEmployee (const Employee employee) {m_employee = employee; }
    void updatePage();
    void clearPage();
private:
    void submitForm(Employee formData);

    EmployeeService *service;

    Employee m_employee;

    QLineEdit *employeeLoginField;
    QLineEdit *employeeNameField;
    QLineEdit *employeeSurnameField;
    QLineEdit *employeePositionField;
    QDateEdit *employeeEmploymentDateField;
    QLineEdit *employeePasswordField;
signals:
    void formClosed();
};

#endif // EDITEMPLOYEEPAGE_H
